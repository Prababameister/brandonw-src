#!/usr/bin/env python3
import rospy
from std_msgs.msg import Float64
from arm_gamepad_controller.msg import Gamepad

sensitivity = 10

axis_pub = []

def callback(data):
    rospy.loginfo(rospy.get_caller_id() + "I heard %s", data.j1_vrx);

    vel = (data.j1_vrx - 506) / 506;
    vel *= sensitivity;

    axis_pub[5].publish(vel);

def gamepad_controller_init():
    rospy.init_node('gamepad_controller', anonymous=True)

    rospy.Subscriber("/gamepad_state", Gamepad, callback)

    rospy.spin()

if __name__ == '__main__':
    # Create the publishers for each axis
    axis_pub.append(rospy.Publisher('/arm_axis_1_controller/command', Float64, queue_size=1))
    axis_pub.append(rospy.Publisher('/arm_axis_2_controller/command', Float64, queue_size=1))
    axis_pub.append(rospy.Publisher('/arm_axis_3_controller/command', Float64, queue_size=1))
    axis_pub.append(rospy.Publisher('/arm_axis_4_controller/command', Float64, queue_size=1))
    axis_pub.append(rospy.Publisher('/arm_axis_5_controller/command', Float64, queue_size=1))
    axis_pub.append(rospy.Publisher('/arm_axis_6_controller/command', Float64, queue_size=1))

    gamepad_controller_init()
