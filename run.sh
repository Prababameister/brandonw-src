#!/usr/bin/env bash

sudo docker run -it -v "./catkin_ws":/catkin_ws --net=ros --device=/dev/ttyACM0 robot-arm bash
