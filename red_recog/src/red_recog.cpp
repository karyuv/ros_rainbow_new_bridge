#include <ros/ros.h>
#include <image_transport/image_transport.h>
#include <cv_bridge/cv_bridge.h>
#include <sensor_msgs/image_encodings.h>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <std_msgs/Float32MultiArray.h>
#include <std_msgs/Int32.h>
#include "std_msgs/String.h"
#include "std_msgs/MultiArrayLayout.h"
#include "std_msgs/MultiArrayDimension.h"

namespace enc = sensor_msgs::image_encodings;
float i,j;
float x_y[2];
static const char WINDOW[] = "Image window";
int intensity;
int c=0;
std_msgs::Float32MultiArray xy;
int confidence_stop=0;
int confidence_not_stop=0;
std_msgs::Int32 s;
ros::Publisher xy_pub;
ros::Publisher stop_pub;
class ImageConverter
{
  ros::NodeHandle nh_;
  image_transport::ImageTransport it_;
  image_transport::Subscriber image_sub_;
 

public:
  ImageConverter()
    : it_(nh_)
  {
xy_pub = nh_.advertise<std_msgs::Float32MultiArray>("xy_red", 1000);
stop_pub=nh_.advertise<std_msgs::Int32>("stop_sign", 1000);
 image_sub_ = it_.subscribe("/camera/rgb/image_raw", 1, &ImageConverter::imageCb, this);
   

cv::namedWindow(WINDOW, CV_WINDOW_NORMAL);

  }

  ~ImageConverter()
  {
    cv::destroyWindow(WINDOW);
  }

  void imageCb(const sensor_msgs::ImageConstPtr& msg)
  {

    cv_bridge::CvImagePtr cv_ptr;
    cv_ptr = cv_bridge::toCvCopy(msg,enc::BGR8);
    cv::Mat frame= cv_ptr->image;
cv::Mat c1;
cv::Mat c2;
cv::Mat c3;
std::vector<cv::Mat> rgb(3);
cv::split(frame, rgb);
c1=rgb[2]-rgb[1];
c2=c1-rgb[0];
cv::inRange(c2,90,255,c3);
//std::cout<<"\n"<<c3.rows<<"\t"<<c3.cols;
c=0;
x_y[0]=0;
x_y[1]=0;
for(i=0;i<c3.cols;i++)
{
for(j=0;j<c3.rows;j++)
{

cv::Scalar intensity = c3.at<uchar>(i, j);
//std::cout<<"\n"<<intensity.val[0];
if(intensity.val[0]>230)
{
c=c+1;
x_y[0]=x_y[0]+i;
x_y[1]=x_y[1]+j;
}

} 
 
}
 x_y[0]=x_y[0]/c;//x-coordinate
 x_y[1]=x_y[1]/c;//y-coordinate
std::cout<<"\ncount:"<<c;
//publish the coordinates

s.data=0;
if(c>550)//polling for feasbility of an red object
{
confidence_stop=confidence_stop+1;
if(confidence_stop>20)
{
std::cout<<"STOP SIGN DETECTED::::\n";
s.data=1;
stop_pub.publish(s);
xy.data.clear();
xy.data.push_back(x_y[0]);//x-coordinate
xy.data.push_back(x_y[1]);//y-coordinate
xy_pub.publish(xy);
confidence_stop=0;
}

}
else
{
confidence_not_stop=confidence_not_stop+1;
if(confidence_not_stop>20)
{
s.data=0;
stop_pub.publish(s);
xy.data.clear();
xy.data.push_back(0);//x-coordinate
xy.data.push_back(0);//y-coordinate
xy_pub.publish(xy);
confidence_not_stop=0;
}

}
  }
};

int main(int argc, char** argv)
{
  ros::init(argc, argv, "pixel_filter");
  ImageConverter ic;
  ros::spin();
  return 0;
}
