/*
 * visual_slam.hpp
 *
 *  Created on: Mar 18, 2016
 *      Author: marco
 */

#ifndef VISUAL_SLAM_HPP_
#define VISUAL_SLAM_HPP_



namespace eye
{
	class visual_slam
	{
	public:
		visual_slam(ros::NodeHandle _nh) : node_handler(_nh), period(30) {};
		~visual_slam(){};
		void init();
		void reset();
		void run();
	private:
		std::string frame_name;
		ros::Rate period;
		ros::Time curr_time, prev_time;
		ros::NodeHandle node_handler;
		double time_diff;
	};
}


#endif /* VISUAL_SLAM_HPP_ */
