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
#include <std_msgs/Float32MultiArray.h>
#include "std_msgs/MultiArrayLayout.h"
#include "std_msgs/MultiArrayDimension.h"
//THE DEFAULT PORT TO RECEIVE THE ENCODER VALUES
#define SERVER_PORT     8088

using namespace std;

//declaring the global variables
stringstream ss;
int sd,rc,i;
float joint_values[39];
float a=0.0;
float b=0.0;
char buffer[850];
string encoder,encoder_1;
int s;
std_msgs::Float32MultiArray ft;
ros::Publisher ft_pub;
//define a non-blocking socket,hence not waiting to recieve data.
unsigned long nonblocking=1;

//declare objects for publishing.
std::string enco_read;
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

#define lfft_x 27
#define lfft_y 28
#define lfft_z 29

#define rfft_x 30
#define rfft_y 31
#define rfft_z 32

#define lhwnd_x 33
#define lhwnd_y 34
#define lhwnd_z 35

#define rhwnd_x 36
#define rhwnd_y 37
#define rhwnd_z 38




void ft_callback()
{

ft.data.clear();
ft.data.push_back(joint_values[lfft_x]);
ft.data.push_back(joint_values[lfft_y]);
ft.data.push_back(joint_values[lfft_z]);
ft.data.push_back(joint_values[rfft_x]);
ft.data.push_back(joint_values[rfft_y]);
ft.data.push_back(joint_values[rfft_z]);
ft.data.push_back(joint_values[lhwnd_x]);
ft.data.push_back(joint_values[lhwnd_y]);
ft.data.push_back(joint_values[lhwnd_z]);
ft.data.push_back(joint_values[rhwnd_x]);
ft.data.push_back(joint_values[rhwnd_y]);
ft.data.push_back(joint_values[rhwnd_z]);
ft_pub.publish(ft);


}

void hubo_callback()
{

joint_state.header.stamp = ros::Time::now();
a=0;

//Assign the encoder variable of the actual robot to the virtual model's joint value.
joint_state.name[LSR] ="LSR";
joint_state.position[LSR]=joint_values[8];

joint_state.name[LSY] ="LSY";
joint_state.position[LSY]=joint_values[9];

joint_state.name[LEP] ="LEP";
joint_state.position[LEP]=joint_values[10];

joint_state.name[LWY] ="LWY";
joint_state.position[LWY]=joint_values[11];

joint_state.name[LWP] ="LWP";
joint_state.position[LWP]=joint_values[12];


joint_state.name[LAP] ="LAP";
joint_state.position[LAP]=joint_values[22];


joint_state.name[LAR] ="LAR";
joint_state.position[LAR]=joint_values[23];


joint_state.name[LHP] ="LHP";
joint_state.position[LHP]=joint_values[14];

joint_state.name[LHR] ="LHR";
joint_state.position[LHR]=joint_values[15];

joint_state.name[LHY] ="LHY";
joint_state.position[LHY]=joint_values[18];

joint_state.name[LKP] ="LKP";
joint_state.position[LKP]=joint_values[21];

joint_state.name[LWR] ="LWR";
joint_state.position[LWR]=a;



joint_state.name[RAP] ="RAP";
joint_state.position[RAP]=joint_values[24];


joint_state.name[RAR] ="RAR";
joint_state.position[RAR]=joint_values[25];

joint_state.name[REP] ="REP";
joint_state.position[REP]=joint_values[3];

joint_state.name[RHP] ="RHP";
joint_state.position[RHP]=joint_values[16];

joint_state.name[RHR] ="RHR";
joint_state.position[RHR]=joint_values[17];

joint_state.name[RHY] ="RHY";
joint_state.position[RHY]=joint_values[19];

joint_state.name[RKP] ="RKP";
joint_state.position[RKP]=joint_values[20];

joint_state.name[RSP] ="RSP";
joint_state.position[RSP]=joint_values[0];

joint_state.name[RSR] ="RSR";
joint_state.position[RSR]=joint_values[1];

joint_state.name[RSY] ="RSY";
joint_state.position[RSY]=joint_values[2];

joint_state.name[RWP] ="RWP";
joint_state.position[RWP]=joint_values[5];

joint_state.name[RWR] ="RWR";
joint_state.position[RWR]=a;

joint_state.name[RWY] ="RWY";
joint_state.position[RWY]=joint_values[4];


joint_state.name[LF32] ="LF32";
joint_state.position[LF32]=a;



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
joint_state.position[LSP]=joint_values[7];





joint_pub.publish(joint_state);



}



int main(int argc, char** argv) {

//define your ros node,publisher,subscriber etc.
ros::init(argc, argv, "hubo_state_publisher");
ros::NodeHandle n;
joint_pub = n.advertise<sensor_msgs::JointState>("joint_states", 1);
ft_pub = n.advertise<std_msgs::Float32MultiArray>("ft_hand_leg", 1000);
tf::TransformBroadcaster broadcaster;
ros::Rate loop_rate(100);

//define your socket related objects
struct sockaddr_in serveraddr;
serveraddr.sin_family      = AF_INET;
serveraddr.sin_port        = htons(SERVER_PORT);
serveraddr.sin_addr.s_addr = htonl(INADDR_ANY); //make sure to provide this rather than a particular ip-address(which never works).
int n_0=0,n_1=0;
int size=sizeof(serveraddr);   

//define the base link of the robot
geometry_msgs::TransformStamped odom_trans;
odom_trans.header.frame_id = "odom";
odom_trans.child_frame_id = "hubo_base";

//define your socket
sd = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
ioctl(sd,FIONBIO,&nonblocking);
rc = bind(sd, (struct sockaddr *)&serveraddr, size);
socklen_t serveraddrlen =sizeof(serveraddr);


// message declarations
joint_state.name.resize(52);
joint_state.position.resize(52);
string sub;
int init=1;
int diff;

    while (ros::ok()) {



//recieve the UDP packets from the hubo computer
rc = recvfrom(sd, buffer, sizeof(buffer), 0,
                    (struct sockaddr *)&serveraddr, 
                    &serveraddrlen);
encoder=(string)buffer;
init=1;
n_0=0;
n_1=0;

//check if they are empty packets
if(encoder.length()!=0)
{
//Parse the recieved encoder data.
for(i=0;i<39;i++)
{
n_1=encoder.find('*',n_0);
diff=n_1-init;
encoder_1=encoder.substr(init,diff);
init=n_1+1;
joint_values[i]=std::atof(encoder_1.c_str());
n_0=n_1+1;
encoder_1=" ";
 }
//update the position
std::cout<<"\n encoder:"<<encoder;
odom_trans.header.stamp=ros::Time::now();
odom_trans.transform.translation.x=0.0;
odom_trans.transform.translation.y=-1.6;
odom_trans.transform.translation.z=0;
odom_trans.transform.rotation = tf::createQuaternionMsgFromYaw(0);
broadcaster.sendTransform(odom_trans);
hubo_callback(); 
ft_callback(); 

encoder=" ";
}
   
ros::spinOnce();
loop_rate.sleep();
}


    return 0;
}
