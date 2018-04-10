#include "ex1/lib1.h"


lib1::lib1(ros::NodeHandle *n)
{
	n_ = *n;
	dataPub=n_.advertise<std_msgs::Float32MultiArray>("output_data", 10);


}


void lib1::callBack(const sensor_msgs::Joy::ConstPtr& msg)
{
	double data1;
	double data2;
	std_msgs::Float32MultiArray data_out;
	
	data_out.data.resize(2);

	data1= msg->axes[4] + msg->axes[0];
	data2= msg->axes[1] + msg->axes[3];
	
	data_out.data[0]=data1;
	data_out.data[1]=data2;
	dataPub.publish(data_out);
	




}
