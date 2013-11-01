//ros-based header files
#include <ros/ros.h>
#include <sensor_msgs/JointState.h>
#include <tf/transform_broadcaster.h>

//Network based header files. 
//Please do not change this order of loading the header  files.
#include <stdio.h>      
#include <stdlib.h>
#include <sys/types.h> 
#include<iostream>
#include<string>
#include <unistd.h>
#include<iomanip>

#include <sstream>



using namespace std;

//declaring the global variables

float a=0.0;
float b=0.0;




//declare objects for publishing.

ros::Publisher joint_pub;
sensor_msgs::JointState joint_state;







int main(int argc, char** argv) {

//define your ros node,publisher,subscriber etc.
ros::init(argc, argv, "hubo_state_publisher");
ros::NodeHandle n;
joint_pub = n.advertise<sensor_msgs::JointState>("joint_states", 1);
tf::TransformBroadcaster broadcaster;
ros::Rate loop_rate(100);



// message declarations
geometry_msgs::TransformStamped odom_trans;
odom_trans.header.frame_id = "odom";
odom_trans.child_frame_id = "vehicle_base";
joint_state.name.resize(2);
joint_state.position.resize(2);
   


    while (ros::ok()) {

b=b+0.0001;


//update the position
odom_trans.header.stamp=ros::Time::now();
odom_trans.transform.translation.x=0;
odom_trans.transform.translation.y=0;
odom_trans.transform.translation.z=-1;
odom_trans.transform.rotation = tf::createQuaternionMsgFromYaw(0);
broadcaster.sendTransform(odom_trans);

joint_state.header.stamp = ros::Time::now();
a=0;
//Assign the encoder variable of the actual robot to the virtual model's joint value.
joint_state.name[0] ="vehicle_move";
joint_state.position[0]=a;
joint_state.name[1] ="STW";
joint_state.position[1]=a;

joint_pub.publish(joint_state);
    
ros::spinOnce();
loop_rate.sleep();
}


    return 0;
}
