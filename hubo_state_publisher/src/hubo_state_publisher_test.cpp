//ros-based header files
#include <ros/ros.h>
#include <sensor_msgs/JointState.h>
#include <tf/transform_broadcaster.h>

//Network based header files. 
//Please do not change this order of loading the header  files.
#include <stdio.h>      
#include <stdlib.h>
#include <sys/types.h>
#include <netinet/in.h>
#include<sys/socket.h>
#include<arpa/inet.h> 
#include<iostream>
#include<string>
#include <unistd.h>
#include<iomanip>
#include <sys/ioctl.h>
#include <sstream>

//THE DEFAULT PORT TO RECEIVE THE ENCODER VALUES
#define SERVER_PORT     8088

using namespace std;

//declaring the global variables

float a=0.0;
float b=0.0;



//define a non-blocking socket,hence not waiting to recieve data.
unsigned long nonblocking=1;

//declare objects for publishing.

ros::Publisher joint_pub;
sensor_msgs::JointState joint_state;

#define LSR 0
#define LSY 1
#define LEP 2
#define LWY 3
#define LWP 4
#define LAP 5
#define LAR 6
#define LHP 7
#define LHR 8
#define LHY 9
#define LKP 10
#define LWR 11
#define NKY 12
#define RAP 13
#define RAR 14
#define REP 15
#define RHP 16
#define RHR 17
#define RHY 18
#define RKP 19
#define RSP 20
#define RSR 21
#define RSY 22
#define RWP 23
#define RWR 24
#define RWY 25
#define LF32 26
#define NK1 27
#define NK2 28
#define RF13 29
#define RF12 30
#define TSY 31
#define RF31 32
#define RF32 33
#define RF2 34
#define RF1 35
#define RF22 36
#define RF23 37
#define RF21 38
#define RF42 39
#define RF43 40
#define LF21 41
#define LF22 42
#define LF23 43
#define LF1 44
#define LF31 45
#define LF12 46
#define LF33 47
#define LF11 48
#define LF13 49
#define RF33 50
#define LSP 51
#define turret_pan 52
#define turret_tilt 53
#define lidar_tilt 54
#define lidar_optical_link 55
#define camera_l 56
#define camera_c 57
#define camera_r 58
#define ps_lower_base 59



void hubo_callback()
{

joint_state.header.stamp = ros::Time::now();
a=0;

//Assign the encoder variable of the actual robot to the virtual model's joint value.
//Assign the encoder variable of the actual robot to the virtual model's joint value.
joint_state.name[LSR] ="LSR";
joint_state.position[LSR]=a;

joint_state.name[LSY] ="LSY";
joint_state.position[LSY]=a;

joint_state.name[LEP] ="LEP";
joint_state.position[LEP]=a;

joint_state.name[LWY] ="LWY";
joint_state.position[LWY]=a;

joint_state.name[LWP] ="LWP";
joint_state.position[LWP]=a;


joint_state.name[LAP] ="LAP";
joint_state.position[LAP]=a;


joint_state.name[LAR] ="LAR";
joint_state.position[LAR]=a;


joint_state.name[LHP] ="LHP";
joint_state.position[LHP]=a;

joint_state.name[LHR] ="LHR";
joint_state.position[LHR]=a;

joint_state.name[LHY] ="LHY";
joint_state.position[LHY]=a;

joint_state.name[LKP] ="LKP";
joint_state.position[LKP]=a;

joint_state.name[LWR] ="LWR";
joint_state.position[LWR]=a;

joint_state.name[NKY] ="NKY";
joint_state.position[NKY]=0.0;

joint_state.name[RAP] ="RAP";
joint_state.position[RAP]=a;


joint_state.name[RAR] ="RAR";
joint_state.position[RAR]=a;

joint_state.name[REP] ="REP";
joint_state.position[REP]=a;

joint_state.name[RHP] ="RHP";
joint_state.position[RHP]=a;

joint_state.name[RHR] ="RHR";
joint_state.position[RHR]=a;

joint_state.name[RHY] ="RHY";
joint_state.position[RHY]=a;

joint_state.name[RKP] ="RKP";
joint_state.position[RKP]=a;

joint_state.name[RSP] ="RSP";
joint_state.position[RSP]=a;

joint_state.name[RSR] ="RSR";
joint_state.position[RSR]=a;

joint_state.name[RSY] ="RSY";
joint_state.position[RSY]=a;

joint_state.name[RWP] ="RWP";
joint_state.position[RWP]=a;

joint_state.name[RWR] ="RWR";
joint_state.position[RWR]=a;

joint_state.name[RWY] ="RWY";
joint_state.position[RWY]=a;


joint_state.name[LF32] ="LF32";
joint_state.position[LF32]=a;

joint_state.name[NK1] ="NK1";
joint_state.position[NK1]=a;

joint_state.name[NK2] ="NK2";
joint_state.position[NK2]=a;

joint_state.name[RF13] ="RF13";
joint_state.position[RF13]=a;

joint_state.name[RF12] ="RF12";
joint_state.position[RF12]=a;

joint_state.name[TSY] ="TSY";
joint_state.position[TSY]=a;

joint_state.name[RF31] ="RF31";
joint_state.position[RF31]=a;


joint_state.name[RF32] ="RF32";
joint_state.position[RF32]=a;

joint_state.name[RF2] ="RF2";
joint_state.position[RF2]=a;

joint_state.name[RF1] ="RF1";
joint_state.position[RF1]=a;

joint_state.name[RF22] ="RF22";
joint_state.position[RF22]=a;

joint_state.name[RF23] ="RF23";
joint_state.position[RF23]=a;

joint_state.name[RF21] ="RF21";
joint_state.position[RF21]=a;


joint_state.name[RF42] ="RF42";
joint_state.position[RF42]=a;

joint_state.name[RF43] ="RF43";
joint_state.position[RF43]=a;

joint_state.name[LF21] ="LF21";
joint_state.position[LF21]=a;

joint_state.name[LF22] ="LF22";
joint_state.position[LF22]=a;

joint_state.name[LF23] ="LF23";
joint_state.position[LF23]=a;

joint_state.name[LF1] ="LF1";
joint_state.position[LF1]=a;

joint_state.name[LF31] ="LF31";
joint_state.position[LF31]=a;

joint_state.name[LF12] ="LF12";
joint_state.position[LF12]=a;


joint_state.name[LF33] ="LF33";
joint_state.position[LF33]=a;

joint_state.name[LF11] ="LF11";
joint_state.position[LF11]=a;


joint_state.name[LF13] ="LF13";
joint_state.position[LF13]=a;

joint_state.name[RF33] ="RF33";
joint_state.position[RF33]=a;

joint_state.name[LSP] ="LSP";
joint_state.position[LSP]=a;

joint_state.name[turret_pan]="turret_pan";
joint_state.position[turret_pan]=a;

joint_state.name[turret_tilt]="turret_tilt";
joint_state.position[turret_tilt]=a;


joint_state.name[lidar_tilt]="lidar_tilt";
joint_state.position[lidar_tilt]=a;


joint_state.name[lidar_optical_link]="lidar_optical_link";
joint_state.position[lidar_optical_link]=a;


joint_state.name[camera_l]="camera_l";
joint_state.position[camera_l]=a;

joint_state.name[camera_c]="camera_c";
joint_state.position[camera_c]=a;

joint_state.name[camera_r]="camera_r";
joint_state.position[camera_r]=a;

joint_state.name[ps_lower_base]="ps_lower_base";
joint_state.position[ps_lower_base]=a;

joint_pub.publish(joint_state);



}



int main(int argc, char** argv) {

//define your ros node,publisher,subscriber etc.
ros::init(argc, argv, "hubo_state_publisher");
ros::NodeHandle n;
joint_pub = n.advertise<sensor_msgs::JointState>("joint_states", 1);
tf::TransformBroadcaster broadcaster;
ros::Rate loop_rate(100);



//constructing a transform between a comon frame "odom" and the planar joint "Hubo_base(created in the urdf)". 
geometry_msgs::TransformStamped odom_trans;
odom_trans.header.frame_id = "odom";
odom_trans.child_frame_id = "hubo_base";
joint_state.name.resize(60);
joint_state.position.resize(60);
   


    while (ros::ok()) {

b=b+0.001;


//update the position
odom_trans.header.stamp=ros::Time::now();
odom_trans.transform.translation.x=0.0;
odom_trans.transform.translation.y=-1.6;
odom_trans.transform.translation.z=0;
odom_trans.transform.rotation = tf::createQuaternionMsgFromYaw(0);
broadcaster.sendTransform(odom_trans);
hubo_callback();
    
ros::spinOnce();
loop_rate.sleep();
}


    return 0;
}
