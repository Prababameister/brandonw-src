#include <AccelStepper.h>
#include <ros.h>
#include <std_msgs/Float64.h>

ros::NodeHandle nh;

#define STEPPER_PIN_1 8
#define STEPPER_PIN_2 9
#define STEPPER_PIN_3 10
#define STEPPER_PIN_4 11

const int stepsPerRevolution = 200;  // change this to fit the number of steps per revolution

// initialize the stepper library on pins 8 through 11:
AccelStepper axis(AccelStepper:DRIVER, stepsPerRevolution, STEPPER_PIN_1, STEPPER_PIN_2, STEPPER_PIN_3, STEPPER_PIN_4);

void messageAxis(const std_msgs::Float64& control_msg) {
  float p = control_msg.data;

  Serial.println("Input: " + p);

  long step_pos = p / 2 * 3.1415 * stepsPerRevolution;

  axis.runSpeed(step_pos);
}

ros::Subscriber<std_msgs::Float64> sub("/arm_axis_1_controller/command", &messageAxis);

void setup() {
  // set the speed at 60 rpm:
  myStepper.setSpeed(60);
  // initialize the serial port:
  Serial.begin(9600);

  axis.setCurrentPosition();

  nh.initNode();
  nh.subscribe(sub);
}

void loop() {
  Serial.print("Before spin");
  // step one revolution  in one direction:
  nh.spinOnce();
  Serial.print("After spin");
  delay(1);
}
