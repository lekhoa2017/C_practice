#include "ros/ros.h"
#include "sensor_msgs/Joy.h"
#include "std_msgs/Float32MultiArray.h"
#include "ex1/lib1.h"

int main(int argc, char** argv)
{
   	ros::init(argc, argv, "testin_lib1");     
	ros::NodeHandle n;	
	lib1 myObj(&n);
	ros::Subscriber joySub = n.subscribe<sensor_msgs::Joy>("joy", 10, &lib1::callBack, &myObj);
	ros::spin();


}	
