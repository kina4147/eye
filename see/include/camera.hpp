/*
 * camera.hpp
 *
 *  Created on: Mar 12, 2016
 *      Author: marco
 */

#ifndef CAMERA_HPP_
#define CAMERA_HPP_
#include <string>
#include <ros/ros.h>
//#include <opencv2/opencv.hpp>
#include <opencv2/highgui/highgui.hpp>
//#include <opencv2/imgproc/imgproc.hpp>
//#include <opencv2/core/eigen.hpp>
//
#include <cv_bridge/cv_bridge.h>
//#include <sensor_msgs/image_encodings.h>
#include <image_transport/image_transport.h>

namespace eye
{
	namespace see
	{
		class camera
		{
		public:
//			camera(){};
			camera(int _video, ros::NodeHandle _nh) : capture(_video), frame_name(" "), image_transport(_nh), period(30) {};
			~camera(){};
			void init();
			void reset();
			void run();
			void loadImage();
			void loadCamera();
		private:
			image_transport::ImageTransport image_transport;
			image_transport::Publisher image_pub;
			cv::VideoCapture capture;
			std::string frame_name;
			ros::Rate period;
			ros::Time curr_time, prev_time;
			ros::NodeHandle node_handler;
			double time_diff;
		};
	}
}



#endif /* CAMERA_HPP_ */
