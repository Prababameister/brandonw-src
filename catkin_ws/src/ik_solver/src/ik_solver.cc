#include "ros/ros.h"
#include "ik_solver/IKSolve.h"
#include <sensor_msgs/JointState.h>

#include <Eigen/Dense>

#include <jsoncpp/json/json.h>

#include <fstream>
#include <string>
#include <cmath>

struct dh_parameter_group {
  float theta;
  float d;
  float a;
  float alpha;
};

dh_parameter_group transform_parameters[6];
float joint_position[6] = {};

Eigen::Matrix<float, 6, 6> jacobian, jacobian_pinv;

Eigen::Matrix4f joint_transforms[6];
Eigen::Matrix4f temp;

Eigen::Matrix<float, 3, 6> jv, jw;
Eigen::Matrix4f fk_matrix, comp_fk_matrix;

Eigen::Matrix<float, 6, 1> ee_vel{6}, joint_vel{6};

std::fstream file;

void populate_dh_matrix (Eigen::Matrix4f& joint_transform, dh_parameter_group& tdhp, float joint_pos) {
  double cos_theta_joint = std::cos(tdhp.theta + joint_pos);
  double sin_theta_joint = std::sin(tdhp.theta + joint_pos);
  double cos_alpha = std::cos(tdhp.alpha);
  double sin_alpha = std::sin(tdhp.alpha);

  joint_transform <<
    cos_theta_joint, -sin_theta_joint * cos_alpha,  sin_theta_joint * sin_alpha, tdhp.a * cos_theta_joint,
    sin_theta_joint,  cos_theta_joint * cos_alpha, -cos_theta_joint * sin_alpha, tdhp.a * sin_theta_joint,
    0.0,                      sin_alpha,                      cos_alpha,                      tdhp.d,
    0.0,                           0.0,                           0.0,                           1.0;
}

void create_changed_fk_matrix (Eigen::Matrix4f& fk, int offset_index) {
  for (int i = 0; i < 6; ++i) {
    populate_dh_matrix (temp, transform_parameters[i], joint_position[i] + (offset_index == i) * 0.1);
    fk *= temp;
  }
}

void create_jacobian () {
  for (int i = 0; i < 6; ++i)
    populate_dh_matrix (joint_transforms[i], transform_parameters[i], joint_position[i]);

  fk_matrix = Eigen::Matrix4f::Identity();
  for (int i = 0; i < 6; ++i) {
    fk_matrix *= joint_transforms[i];
    jw.col(i) = fk_matrix.block<3, 1>(0, 2);
  }

  for (int i = 0; i < 6; ++i) {
    create_changed_fk_matrix(comp_fk_matrix, i);
    jv.col(i) = (comp_fk_matrix - fk_matrix).block<3, 1>(0, 3);
  }
  jv /= 0.1;

  jacobian.block<3, 6>(0, 0) = jv;
  jacobian.block<3, 6>(3, 0) = jw;
}

bool calculate_joint_velocities (ik_solver::IKSolve::Request &req,
                                 ik_solver::IKSolve::Response &res) {
  create_jacobian();
  jacobian_pinv = jacobian.completeOrthogonalDecomposition().pseudoInverse();

  ee_vel <<
    req.x_vel,
    req.y_vel,
    req.z_vel,
    req.roll_vel,
    req.pitch_vel,
    req.yaw_vel;

  joint_vel = jacobian_pinv * ee_vel;

  res.a1_vel = joint_vel.coeff(0);
  res.a2_vel = joint_vel.coeff(1);
  res.a3_vel = joint_vel.coeff(2);
  res.a4_vel = joint_vel.coeff(3);
  res.a5_vel = joint_vel.coeff(4);
  res.a6_vel = joint_vel.coeff(5);

  return 0;
}

void update_joint_state (const sensor_msgs::JointState::ConstPtr& msg) {
  for (int i = 0; i < 6; ++i)
    joint_position[i] = msg->position[i];
}

void get_dh_parameters () {
  float parameters[6][4] =
  {
    {0, 0.069829, 0.067114, 1.570796327},
    {1.570796327, 0.070162, 0.209508, 3.141592654},
    {1.570796327, 0.067599, 0.18, 3.141592654},
    {0, 0.082409, 0, -1.570796327},
    {1.570796327, 0.0831, 0, 1.570796327},
  };

  for (int i = 0; i < 6; ++i) {
    transform_parameters[i].theta = parameters[i][0];
    transform_parameters[i].d = parameters[i][1];
    transform_parameters[i].a = parameters[i][2];
    transform_parameters[i].alpha = parameters[i][3];
  }
}

int main(int argc, char **argv) {
  ros::init(argc, argv, "ik_solver_server");
  ros::NodeHandle n;

  get_dh_parameters();

  ros::ServiceServer service = n.advertiseService("calculate_joint_velocities", calculate_joint_velocities);
  ROS_INFO("Ready to solve");

  ros::Subscriber joint_state_sub = n.subscribe("/joint_state", 1, update_joint_state);

  ros::spin();

  return 0;
}
