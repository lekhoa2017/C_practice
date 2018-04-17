#include "ex1/mag_cal.h"


imuCal::imuCal(ros::NodeHandle *n,ros::NodeHandle *nh)
{
	n_ = *n;
	nh_= *nh;

	// init value of max and min
	maxX =-10;
	minX = 10;
	maxY = -10;
	minY = 10;
	Heading = 90;
	magX = 0;
	magY = 0;
	count = 0;
	initial_heading = 90;
	stage = 0;
	enable = 0;
	yaw_command = 0;
	enable_Pub  = n_.advertise<std_msgs::Int32>("mode_sim", 10);
	command_Pub = n_.advertise<geometry_msgs::Vector3>("command_sim", 10);
//	usleep(1000000); // wait for heading estimation to settle down



}


imuCal::~imuCal()
{
	  // Store calibration data to yaml file
	  std::fstream myfile;
	  myfile.open ("/home/khoa/C_practice/src/ex1/launch/mag.yaml");
	  myfile << "IMU1:\n";

	  myfile << " maxX: ";
	  myfile << maxX;
	  myfile << "\n";

	  myfile << " minX: ";
	  myfile << minX;
	  myfile << "\n";

	  myfile << " maxY: ";
	  myfile << maxY;
	  myfile << "\n";

	  myfile << " minY: ";
	  myfile << minY;


	  myfile.close();

}

void imuCal::cb_Heading(const std_msgs::Float32MultiArray::ConstPtr& msg)
{
	Heading = msg->data[0]; // Heading from estimation

}

void imuCal::cb_mag(const sensor_msgs::MagneticField::ConstPtr& msg)
{
	magX = msg->magnetic_field.x;
	magY = msg->magnetic_field.y;

}


void imuCal::cb_timer(const ros::TimerEvent& event)
{

	if (count<=40) // wait for heading to settle down 40x0.05= 2s
	{
		count ++;
		initial_heading = Heading;
		if (count >=40) { stage = 1;} // jump to the first stage
	}
	else
	{
		// Get max and min value of magnetic field
		if (maxX < magX) { maxX= magX; }
		if (minX > magX) { minX= magX; }
		if (maxY < magY) { maxY= magY; }
		if (minY > magY) { minY= magY; }

		// State finite machine
		switch(stage) {
		    case 1 :  // CW yaw
		    	enable = 1;
		    	yaw_command = -20;
		    	if ((Heading - initial_heading) < -360)
		    	{
		    		stage = 2; // switch to next stage
		    	}
		        break;
		    case 2 :  // CCW yaw
		    	enable = 1;
		    	yaw_command = 20;
		    	if ((Heading - initial_heading) >0)
		    	{
		    		stage = 3; // switch to next stage
		    	}
		    	break;
		    case  3:  // complete motion
		    	enable = 0;
		    	yaw_command = 0;
		    	break;
		}

	}

	// publish command
	std_msgs::Int32 EN_out;
	geometry_msgs::Vector3 command_out;
	EN_out.data = enable;
	command_out.x= 0;
	command_out.y= 0;
	command_out.z =yaw_command;
	enable_Pub.publish(EN_out);
	command_Pub.publish(command_out);





}
