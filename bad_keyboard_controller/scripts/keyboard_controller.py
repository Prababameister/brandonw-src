#!/usr/bin/env python3
import rospy
from std_msgs.msg import Float64, Bool

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

sensitivity = 20

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

electromag_pub = rospy.Publisher('/arm_electromagnet/command', Bool, queue_size=1)

def keyboard_controller():
    rospy.init_node('keyboard_controller', anonymous=True)

    rate = rospy.Rate(5)

    while not rospy.is_shutdown():
        k = getKey(settings, 0.5)

        if k == quit_key:
            break

        for x in range(6):
            vel = 0.0
            if k == control_keys[x][0]:
                vel = sensitivity
            elif k == control_keys[x][1]:
                vel = -sensitivity

            axis_pub[x].publish(vel)

        if k == 'p':
            electromag_pub.publish(1)

        rate.sleep()

if __name__ == '__main__':
    # Create the publishers for each axis
    axis_pub.append(rospy.Publisher('/arm_axis_1_controller/command', Float64, queue_size=1))
    axis_pub.append(rospy.Publisher('/arm_axis_2_controller/command', Float64, queue_size=1))
    axis_pub.append(rospy.Publisher('/arm_axis_3_controller/command', Float64, queue_size=1))
    axis_pub.append(rospy.Publisher('/arm_axis_4_controller/command', Float64, queue_size=1))
    axis_pub.append(rospy.Publisher('/arm_axis_5_controller/command', Float64, queue_size=1))
    axis_pub.append(rospy.Publisher('/arm_axis_6_controller/command', Float64, queue_size=1))

    keyboard_controller()
