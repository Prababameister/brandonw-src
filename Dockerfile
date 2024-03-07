ARG ROS_DISTRO=humble

FROM osrf/ros:${ROS_DISTRO}-desktop-full
ENV ROS_DISTRO=${ROS_DISTRO}
SHELL ["/bin/bash", "-c"]

ENV DISPLAY=novnc:0.0

RUN apt-get update && apt-get install -y git wget python3-pip vim
RUN pip3 install setuptools==58.2.0

ADD ros2_ws /ros2_ws

ENV DISPLAY=novnc:0.0
