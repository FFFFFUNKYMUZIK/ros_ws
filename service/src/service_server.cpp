#include "ros/ros.h"
#include "service/Service1.h"

bool Servercb(service::Service1::Request& req,
		service::Service1::Response& res){
	res.result = req.a + req.b;
	ROS_INFO("request: x = %ld, y = %ld", (long int)req.a, (long int)req.b);
	ROS_INFO("result : x+y = %ld", (long int)res.result);
	return true;
}


int main(int argc, char** argv){

	ros::init(argc, argv, "service_server_name");
	ros::NodeHandle nh;

	ros::ServiceServer service_server = nh.advertiseService("service_topic_name", Servercb);

	ROS_INFO("ready service server!");

	ros::spin();

	return 0;
}
