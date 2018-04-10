#ifndef LIB1_H_INCLUDED
#define LIB1_H_INCLUDED

#include "ros/ros.h"
#include "sensor_msgs/Joy.h"
#include "std_msgs/Float32MultiArray.h"

class lib1
{
	public:
		lib1(ros::NodeHandle *);
		void callBack(const sensor_msgs::Joy::ConstPtr& msg);
		ros::NodeHandle n_;
	
	private:
		ros::Publisher dataPub;



};
#endif 
