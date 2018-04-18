#ifndef LIB1_H_INCLUDED
#define LIB1_H_INCLUDED

#include "ros/ros.h"
#include "sensor_msgs/Joy.h"
#include "std_msgs/Float32MultiArray.h"
#include "std_msgs/String.h"
#include <sstream>
#include <fstream>
#include <iostream>
#include <Eigen/Dense>

class lib1
{
	public:
		lib1(ros::NodeHandle *,ros::NodeHandle *); // Constructor
		~lib1(); // Destructor
		ros::NodeHandle n_;
		ros::NodeHandle nh_;

		void callBack(const sensor_msgs::Joy::ConstPtr& msg);
		void cb_timer(const ros::TimerEvent& event);
		ros::Timer timer1;
		double count;
		double data;
	
	private:
		ros::Publisher dataPub;
		ros::Publisher helloPub;
		ros::Publisher data1Pub;



};
#endif 
