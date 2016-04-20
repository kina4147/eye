/*
 * calibration.hpp
 *
 *  Created on: Apr 20, 2016
 *      Author: user
 */

#ifndef CALIBRATION_HPP_
#define CALIBRATION_HPP_

#include <vector>
#include <ros/ros.h>
#include <opencv2/opencv.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <cv_bridge/cv_bridge.h>#include <image_transport/image_transport.h>
#include <image_transport/image_transport.h>
#include <sensor_msgs/image_encodings.h>
namespace eye
{
	namespace glass
	{
		class calibration
		{
		public:
//			camera(){};
			calibration(ros::NodeHandle _nh) : frame_name(" "), node_handler(_nh), period(30) {};
			~calibration(){};
			void init();
			void reset();
			void run();
			void findCheckboard();
		private:
			std::string frame_name;
			ros::Rate period;
			ros::NodeHandle node_handler;
			double time_diff;
			ros::Time curr_time, prev_time;
			ros::Publisher calibrated_img_pub, checkboard_img_pub, input_img_pub;
			ros::Subscriber input_img_sub;
			cv::Mat input_img, checkboard_img, calibrated_img;
			void subscribeImage(const sensor_msgs::ImageConstPtr& _msg_ptr);

		};
	}
}

#endif /* CALIBRATION_HPP_ */
