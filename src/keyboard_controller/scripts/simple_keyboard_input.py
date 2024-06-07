import rospy
from std_msgs.msg import String

import sys
from select import select

if sys.platform == 'win32':
    import msvcrt
else:
    import termios
    import tty

# Config
quit_key = "/"

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

def keyboard_input():
    rospy.init_node('keyboard_input', anonymous=True)

    kb_pub = rospy.Publisher('/simple_kb_input', String, queue_size=1)

    rate = rospy.Rate(5)

    while not rospy.is_shutdown():
        k = getKey(settings, 0.5);

        if k == quit_key:
            break

        kb_pub.publish(k)

if __name__ == '__main__':
    keyboard_input()
