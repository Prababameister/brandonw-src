#!/usr/bin/env python3

import rospy

from joint_state_service.srv import JointPosition, JointPositionResponse
from sensor_msgs.msg import JointState

position = [0.0, 0.0, 0.0, 0.0, 0.0, 0.0]

def callback(data):
    global position
    position = data.position

def handle_joint_state_request(req):
    print(position)
    return JointPositionResponse(position[0], position[1], position[2], position[3], position[4], position[5])

def joint_state_server():
    rospy.init_node("joint_state_server")

    joint_state_subscriber = rospy.Subscriber('/joint_states', JointState, callback)
    joint_state_service = rospy.Service('joint_state_request', JointPosition, handle_joint_state_request)

    rospy.spin()

if __name__ == "__main__":
    joint_state_server()
