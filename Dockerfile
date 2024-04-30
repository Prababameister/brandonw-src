ARG ROS_DISTRO=noetic

FROM osrf/ros:${ROS_DISTRO}-desktop-full
ENV ROS_DISTRO=${ROS_DISTRO}
SHELL ["/bin/bash", "-c"]

ENV DISPLAY=novnc:0.0

RUN apt-get update && apt-get install -y git wget python3-pip vim ros-${ROS_DISTRO}-rosserial-arduino ros-${ROS_DISTRO}-rosserial ros-${ROS_DISTRO}-ros-ign ros-${ROS_DISTRO}-xacro ros-${ROS_DISTRO}-velocity-controllers ros-${ROS_DISTRO}-robot-state-controller libeigen3-dev
RUN pip3 install setuptools==58.2.0 keyboard
