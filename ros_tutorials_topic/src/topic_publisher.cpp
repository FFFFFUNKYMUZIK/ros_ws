#include "ros/ros.h"
#include "ros_tutorials_topic/Msg1.h"

int main(int argc, char** argv){
ros::init(argc, argv, "publisher_node");
ros::NodeHandle nh;

ros::Publisher pub = nh.advertise<ros_tutorials_topic::Msg1>("testmsg", 100);

ros::Rate loop_rate(10);

ros_tutorials_topic::Msg1 msg;
int cnt = 0;

while(ros::ok()){

msg.stamp = ros::Time::now();
msg.data = cnt;

ROS_INFO("send msg1 = %d", msg.stamp.sec);
ROS_INFO("send msg2 = %d", msg.stamp.nsec);
ROS_INFO("send msg3 = %d", msg.data);

pub.publish(msg);

loop_rate.sleep();

++cnt;

}
return 0;
}
