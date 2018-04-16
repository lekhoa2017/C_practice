#include "ros/ros.h"
#include "sensor_msgs/Joy.h"
#include "std_msgs/Float32MultiArray.h"
#include "ex1/lib1.h"
#include "unistd.h"



int main(int argc, char** argv)
{
   	ros::init(argc, argv, "testin_lib1");     
	ros::NodeHandle n;
	ros::NodeHandle nh ("~");	
	lib1 myObj(&n, &nh);
	ros::Subscriber joySub = n.subscribe<sensor_msgs::Joy>("joy", 10, &lib1::callBack, &myObj);
	myObj.timer1 = myObj.n_.createTimer(ros::Duration(0.1), &lib1::cb_timer,&myObj);

	while (ros::ok())
	{
		ros::spinOnce();
//		loop_rate.sleep();
		if (myObj.count>200)
		{

			break;
		}

	}



}	
