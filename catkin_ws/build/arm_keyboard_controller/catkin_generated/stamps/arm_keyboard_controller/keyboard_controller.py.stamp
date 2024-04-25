#!/usr/bin/env python3
import rospy
from std_msgs.msg import Float64
from sensor_msgs.msg import JointState

from joint_state_service.srv import *

import sys
from select import select

if sys.platform == 'win32':
    import msvcrt
else:
    import termios
    import tty

control_keys = [ ['q', 'a'],
                 ['w', 's'],
                 ['e', 'd'],
                 ['r', 'f'],
                 ['t', 'g'],
                 ['y', 'h'] ]

quit_key = '/'

axis_pub = []

def saveTerminalSettings():
    if sys.platform == 'win32':
        return None
    return termios.tcgetattr(sys.stdin)

settings = saveTerminalSettings()

def getKey(settings, timeout):
    if sys.platform == 'win32':
        # getwch() returns a string on Windows
        key = msvcrt.getwch()
    else:
        tty.setraw(sys.stdin.fileno())
        # sys.stdin.read() returns a string on Linux
        rlist, _, _ = select([sys.stdin], [], [], timeout)
        if rlist:
            key = sys.stdin.read(1)
        else:
            key = ''
        termios.tcsetattr(sys.stdin, termios.TCSADRAIN, settings)

    return key

def joint_state_service_client():
    print("Go fuck yourself")
    rospy.wait_for_service('joint_state_request')
    print("Go fuck yourself 2")
    try:
        joint_state = rospy.ServiceProxy('joint_state_request', JointState)
        js = joint_state()
        return js.position
    except rospy.ServiceException as e:
        print("Service call failed: %s"%e)

def keyboard_controller():
    print("hi")
    rospy.init_node('keyboard_controller', anonymous=True)

    print("konichiwhatsup")

    rate = rospy.Rate(10)

    while not rospy.is_shutdown():
        print("namaste")
        gposition = joint_state_service_client()

        k = getKey()

        for x in range(6):
            cur = position[x]
            change = 0.0
            if k == control_keys[x][0]:
                change = 0.2
            elif k == control_keys[x][1]:
                change = -0.2

            new_pos = cur + change
            axis_pub[x].publish(new_pos)

        rate.sleep()

if __name__ == '__main__':
    # Create the publishers for each axis
    axis_pub.append(rospy.Publisher('/arm_axis_1_controller/command', Float64, queue_size=1))
    axis_pub.append(rospy.Publisher('/arm_axis_2_controller/command', Float64, queue_size=1))
    axis_pub.append(rospy.Publisher('/arm_axis_3_controller/command', Float64, queue_size=1))
    axis_pub.append(rospy.Publisher('/arm_axis_4_controller/command', Float64, queue_size=1))
    axis_pub.append(rospy.Publisher('/arm_axis_5_controller/command', Float64, queue_size=1))
    axis_pub.append(rospy.Publisher('/arm_axis_6_controller/command', Float64, queue_size=1))

    print("bonjour")

    keyboard_controller()
