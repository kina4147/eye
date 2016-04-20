/*
 * calibration.cpp
 *
 *  Created on: Apr 20, 2016
 *      Author: user
 */

#include "calibration.hpp"


void eye::glass::calibration::init()
{
	input_img_pub = node_handler.advertise<sensor_msgs::Image>("/eye/glass/input_image", 1);
	input_img_sub = node_handler.subscribe("/eye/see/image", 1, &eye::glass::calibration::subscribeImage, this);
}
void eye::glass::calibration::reset()
{
	curr_time = ros::Time::now();
	time_diff = (double)((curr_time - prev_time).nsec) * (1e-9);
	prev_time = curr_time;
}
void eye::glass::calibration::run()
{
	period.reset();
	reset();
	ros::spinOnce();
	if(input_img.rows == 0 || input_img.cols == 0)
		return;

	findCheckboard();

	cv_bridge::CvImagePtr bridge(new cv_bridge::CvImage());
//	bridge->header.frame_id = this->frame_id.c_str();
	bridge->header.stamp = curr_time;
	bridge->encoding = sensor_msgs::image_encodings::BGR8;
	bridge->image = input_img;
	input_img_pub.publish(bridge->toImageMsg());

	period.sleep();
}

void eye::glass::calibration::subscribeImage(const sensor_msgs::ImageConstPtr& _msg_ptr)
{
	cv_bridge::CvImagePtr cv_ptr;
	try
	{
		cv_ptr = cv_bridge::toCvCopy(_msg_ptr, sensor_msgs::image_encodings::BGR8);
		input_img = cv_ptr->image;
	}
	catch (cv_bridge::Exception& e)
	{
		ROS_ERROR("cv_bridge exception: %s", e.what());
		return;
	}
}
void eye::glass::calibration::findCheckboard()
{
	std::vector<std::vector<cv::Point3f> > object_points;
	std::vector<std::vector<cv::Point2f> > image_points;
	int board_w, board_h;
	int n_boards;
	float measure = 24;

	cv::Size image_size = cv::Size(input_img.cols, input_img.rows);

	board_w = 6;
	board_h = 8;
	n_boards = 1;

	checkboard_img = input_img;
	char str[100];
	for(int i = 0; i< n_boards; ++i)
	{
		cv::Mat gray_img;
		cvtColor(input_img, gray_img, CV_BGR2GRAY);
		std::vector< cv::Point2f> corners;

		//find chessboard corners
		bool found_flag = cv::findChessboardCorners(gray_img, cv::Size(board_w, board_h), corners);

		//if find corner success, then
		if(found_flag)
		{
			//corner point refine
			cv::cornerSubPix(gray_img, corners, cv::Size(11,11), cv::Size(-1,-1), cv::TermCriteria(CV_TERMCRIT_EPS+CV_TERMCRIT_ITER, 30, 0.1));
			//draw corner
			cv::drawChessboardCorners(input_img, cv::Size(board_w, board_h), corners, found_flag);
			if(corners.size() == board_w*board_h)
			{
				std::vector<cv::Point2f> image_points_;
				std::vector<cv::Point3f> object_points_;
				//save 2d coordenate and world coordinate
				for(int j=0; j< corners.size(); ++j)
				{
					cv::Point2f image_point;
					cv::Point3f object_point;

					image_point.x = corners[j].x;
					image_point.y = corners[j].y;

					object_point.x = j%board_w*measure;
					object_point.y = j/board_w*measure;
					object_point.z = 0;

					image_points_.push_back(image_point);
					object_points_.push_back(object_point);
				}
				image_points.push_back(image_points_);
				object_points.push_back(object_points_);
			}
			ROS_INFO("checkboard is found.");
			//calibration part
			std::vector<cv::Mat> rotation_vecs, translation_vecs;
			cv::Mat intrinsic_mtx(3,3, CV_64F);
			cv::Mat distortion_coeffs(8,1, CV_64F);
			cv::calibrateCamera(object_points, image_points, image_size, intrinsic_mtx, distortion_coeffs, rotation_vecs, translation_vecs);

			cv::undistort(input_img, calibrated_img, intrinsic_mtx, distortion_coeffs);
		}
		else
			ROS_ERROR("no checkboard is found.");
	}


}


