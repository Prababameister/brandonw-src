#!/usr/bin/env python3
import rospy
from std_msgs.msg import Float64, Bool
from arm_gamepad_controller.msg import Gamepad

sensitivity = 20

axis_pub = []
electromag_pub = rospy.Publisher('/arm_electromagnet/command', Bool, queue_size=1)

def get_velocity(raw_value):
    return sensitivity * (raw_value) / 512

def callback(data):
    rospy.loginfo(rospy.get_caller_id() + "Gampad State %s", data)

    vel1 = get_velocity(data.j1_vrx)
    vel2 = get_velocity(data.j1_vry)
    vel3 = get_velocity(data.j2_vrx)
    vel4 = get_velocity(data.j2_vry)
    vel5 = get_velocity(data.j3_vrx)
    vel6 = get_velocity(data.j3_vry)

    axis_pub[0].publish(vel1);
    axis_pub[1].publish(vel2);
    axis_pub[2].publish(vel3);
    axis_pub[3].publish(vel4);
    axis_pub[4].publish(vel5);
    axis_pub[5].publish(vel6);

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
