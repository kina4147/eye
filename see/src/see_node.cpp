/*
 * see_node.cpp
 *
 *  Created on: Mar 12, 2016
 *      Author: marco
 */

#include "camera.hpp"

int main(int argc, char **argv)
{
    ros::init(argc, argv, "see");
    ros::NodeHandle nh;

    eye::see::camera cam(0, nh);
    cam.init();

    while(ros::ok() && nh.ok())
		cam.run();

    return 0;
}
