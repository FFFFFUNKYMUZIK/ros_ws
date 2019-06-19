#include "ros/ros.h"
#include "ros_tutorials_topic/Msg1.h"

void msgCallback(const ros_tutorials_topic::Msg1::ConstPtr& msg){

ROS_INFO("receive msg = %d", msg->stamp.sec);
ROS_INFO("receive msg = %d", msg->stamp.nsec);
ROS_INFO("receive msg = %d", msg->data);

}

int main(int argc, char** argv){

ros::init(argc, argv, "subscriber_node");

ros::NodeHandle nh;

ros::Subscriber sub = nh.subscribe("testmsg", 100, msgCallback);

ros::spin();

return 0;

}
