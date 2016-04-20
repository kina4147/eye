/*
 * visual_slam_node.cpp
 *
 *  Created on: Mar 18, 2016
 *      Author: marco
 */





#include "visual_slam.hpp"

int main(int argc, char **argv)
{
    ros::init(argc, argv, "visual_slam_node");
    ros::NodeHandle node_handler;

    eye::visual_slam vs(node_handler);
    vs.init();

    while(ros::ok() && node_handler.ok())
    	vs.run();

    return 0;
}
