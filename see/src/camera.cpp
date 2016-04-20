/*
 * camera.cpp
 *
 *  Created on: Mar 12, 2016
 *      Author: marco
 */


#include "camera.hpp"


void eye::see::camera::init()
{
	image_pub = image_transport.advertise("camera/image", 1);
	loadCamera();
}
void eye::see::camera::reset()
{

}
void eye::see::camera::run()
{
	period.reset();
	loadImage();
	period.sleep();
}
void eye::see::camera::loadImage()
{
	cv::Mat frame;
	sensor_msgs::ImagePtr msg;
	capture >> frame;
	// Check if grabbed frame is actually full with some content
	if(!frame.empty())
	{
		msg = cv_bridge::CvImage(std_msgs::Header(), "bgr8", frame).toImageMsg();
		image_pub.publish(msg);
		cv::waitKey(1);
	}
}
void eye::see::camera::loadCamera()
{
	if(!capture.isOpened())
	{
		ROS_ERROR("Camera is not opened.");
		return ;
	}
	else
		ROS_INFO("Camera is opened.");
}
