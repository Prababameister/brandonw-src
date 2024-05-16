#!/usr/bin/env bash
# For commit

sudo docker run -it -v "./catkin_ws":/catkin_ws --net=ros --device=/dev/ttyACM0 robot-arm bash
