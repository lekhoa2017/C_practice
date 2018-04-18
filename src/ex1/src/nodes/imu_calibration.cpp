#include "ros/ros.h"
#include "sensor_msgs/Joy.h"
#include "std_msgs/Float32MultiArray.h"
#include "std_msgs/String.h"
#include <sensor_msgs/Imu.h>
#include <sensor_msgs/MagneticField.h>
#include <geometry_msgs/Vector3.h>
#include <std_msgs/Int32.h>
#include "ex1/mag_cal.h"

int main(int argc, char** argv)
{
   	ros::init(argc, argv, "imu_calibration");
   	ros::NodeHandle n;
	ros::NodeHandle nh ("~");
	imuCal imuObj(&n, &nh);
	ros::Subscriber mag_Sub = n.subscribe<sensor_msgs::MagneticField>("imu/raw", 10, &imuCal::cb_mag, &imuObj);
	ros::Subscriber heading_Sub = n.subscribe<std_msgs::Float32MultiArray>("Heading_estimation", 10, &imuCal::cb_Heading, &imuObj);


	while (ros::ok())
	{
		ros::spinOnce();
//		loop_rate.sleep();
		if (imuObj.stage>=3)
		{

			break;
		}

	}



}
