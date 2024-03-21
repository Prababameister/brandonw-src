#!/usr/bin/env bash

sudo docker run -it -v "./ros2_ws":/ros2_ws --net=ros --device=/dev/ttyACM0 robot-arm bash
