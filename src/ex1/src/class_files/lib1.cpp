#include "ex1/lib1.h"


lib1::lib1(ros::NodeHandle *n,ros::NodeHandle *nh)
{
	n_ = *n;
	nh_= *nh;
	data= 0;
	nh_.getParam("data1/value",data);
	dataPub=n_.advertise<std_msgs::Float32MultiArray>("output_data", 10);
	data1Pub=n_.advertise<std_msgs::Float32MultiArray>("new_data", 10);
	helloPub=n_.advertise<std_msgs::String>("Say_s", 10);
	count=0;

}


lib1::~lib1()
{
//	nh_.setParam("data1/value",data);
//	  ofstream myfile;
	  std::fstream myfile;
	  myfile.open ("/home/khoa/C_practice/src/ex1/launch/data.yaml");
	  myfile << "data1:\n";
	  myfile << " value: ";
	  myfile << data;
	  myfile.close();
	
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

void lib1::cb_timer(const ros::TimerEvent& event)
{
 	std_msgs::String msg;
	std_msgs::Float32MultiArray data_out;
	data_out.data.resize(1);
	data_out.data[0]=++data;
 	int count1 = 0;	
 	std::stringstream ss;
     	ss << "hello world " << count1;
  	msg.data = ss.str();
  	helloPub.publish(msg);
	data1Pub.publish(data_out);
	count++;
	ROS_INFO_STREAM("count " << count);
	
}
