#include "ros/ros.h"
#include "ik_solver/IKSolve.h"
#include <sensor_msgs/JointState.h>

#include <Eigen/Dense>

#include <string>
#include <cmath>

float position[6] = {};

struct dh_parameter_group {
  float theta;
  float d;
  float a;
  float alpha;
};

dh_parameter_group transform_parameters[6];

void populate_dh_matrix (Eigen::Matrix4f& joint_transform, dh_parameter_group& tdhp) {
  joint_transform = {
    { std::cos(tdhp.theta), -std::sin(tdhp.theta) * std::cos(tdhp.alpha),  std::sin(tdhp.theta) * std::sin(tdhp.alpha), tdhp.a * std::cos(tdhp.theta) },
    { std::sin(tdhp.theta),  std::cos(tdhp.theta) * std::cos(tdhp.alpha), -std::cos(tdhp.theta) * std::sin(tdhp.alpha), tdhp.a * std::cos(tdhp.theta) },
    { std::cos(tdhp.theta),                         std::sin(tdhp.alpha),                         std::cos(tdhp.alpha),                        tdhp.d },
    {                    0,                                            0,                                            0,                             1 },
  };
}

void create_jacobian (Eigen::Matrix6f& jacobian) {
  Eigen::Matrix4f joint_transforms[6];

  for (int i = 0; i < 6; ++i)
    populate_dh_matrix (joint_transforms[i], transform_parameters[i]);

  Eigen::Matrix<float, 3, 6> jv, jw;

  Eigen::Matrix4f fk_matrix;

  for (int i = 0; i < 6; ++i) {
  }

}

bool calculate_joint_velocities (ik_solver::IKSolve &req, ik_solver::IKSolve &res) {


  return 0;
}

void update_joint_state (const std_msgs::JointState::ConstPtr& msg) {
  for (int i = 0; i < 6; ++i)
    position[i] = msg->data.position()[i];
}

int main(int argc, char **argv) {
  ros::init(argc, argv, "ik_solver_server");
  ros::NodeHandle n;

  ros::ServiceServer service = n.advertiseService("calculate_joint_velocities", calculate_joint_velocities);
  ROS_INFO("Ready to solve");

  ros::Subscriber joint_state_sub = n.subscribe("/joint_state", 1, update_joint_state);

  ros::spin();

  return 0;
}
