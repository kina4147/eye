/*
 * glass_node.cpp
 *
 *  Created on: Apr 20, 2016
 *      Author: user
 */






#include "calibration.hpp"

int main(int argc, char **argv)
{
    ros::init(argc, argv, "glass");
    ros::NodeHandle nh;
    eye::glass::calibration calibration(nh);
    calibration.init();

    while(ros::ok() && nh.ok())
    {
    	calibration.run();
    }
//		cam.run();

    return 0;
}
