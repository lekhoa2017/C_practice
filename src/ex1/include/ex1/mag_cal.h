#ifndef MAG_CAL_H_INCLUDED
#define MAG_CAL_H_INCLUDED

#include "ros/ros.h"
#include "sensor_msgs/Joy.h"
#include "std_msgs/Float32MultiArray.h"
#include "std_msgs/String.h"
#include <sensor_msgs/Imu.h>
#include <sensor_msgs/MagneticField.h>
#include <geometry_msgs/Vector3.h>
#include <std_msgs/Int32.h>
#include <sstream>
#include <fstream>
#include <iostream>


class imuCal
{
	public:
		imuCal(ros::NodeHandle *,ros::NodeHandle *); // Constructor
		~imuCal(); // Destructor
		ros::NodeHandle n_;
		ros::NodeHandle nh_;

		void cb_Heading(const std_msgs::Float32MultiArray::ConstPtr& msg);
		void cb_mag(const sensor_msgs::MagneticField::ConstPtr& msg);
		void cb_timer(const ros::TimerEvent& event);
		ros::Timer timer1;
		float maxX, minX, maxY, minY;
		float Heading, magX, magY,initial_heading;
		double count;
		int stage; // 0 initial, 1 CW; 2 CCW; 3 finish
		int enable;
		double yaw_command;

	private:
		ros::Publisher enable_Pub;
		ros::Publisher command_Pub;




};


#endif
