#!/bin/sh
xterm -e " roslaunch turtlebot_gazebo turtlebot_world.launch world_file:=/home/workspace/catkin_ws/src/map/azzam_world.world " &
sleep 5
xterm -e " roslaunch turtlebot_gazebo amcl_demo.launch map_file:=/home/workspace/catkin_ws/src/map/map.yaml " &
sleep 5
xterm -e " roslaunch rvizconfig view_navigation.launch " &
sleep 10
xterm -e " roslaunch add_markers add_markers.launch " &
sleep 10
xterm -e " roslaunch pick_objects pick_objects.launch "
