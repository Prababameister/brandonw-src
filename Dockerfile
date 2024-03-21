ARG ROS_DISTRO=noetic

FROM osrf/ros:${ROS_DISTRO}-desktop-full
ENV ROS_DISTRO=${ROS_DISTRO}
SHELL ["/bin/bash", "-c"]

ENV DISPLAY=novnc:0.0

RUN apt-get update && apt-get install -y git wget python3-pip vim ros-${ROS_DISTRO}-rosserial-arduino ros-${ROS_DISTRO}-rosserial
RUN pip3 install setuptools==58.2.0
