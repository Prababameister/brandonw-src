import rospy

import pygame
import sys

pygame.init()

display = pygame.display.set_mode((300, 300))

def input_relay():
    rospy.init_node('keyboard_input_relay', anonymous=True)

    rate = rospy.Rate(1)

    while not rospy.is_shutdown():
        events = pygame.event.get()
        print(events)

if __name__ == '__main__':
    input_relay()
