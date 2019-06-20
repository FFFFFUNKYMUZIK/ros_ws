#include "ros/ros.h"
#include "service/Service1.h"

int main(int argc, char** argv){

	ros::init(argc, argv, "service_client_name");
	
	if (argc!=3){

	ROS_INFO("Usage : rosrun service service_client arg1 arg2");
	ROS_INFO("The node will request server to sum the two 8 byte integers");
	return 1;
	}

	ros::NodeHandle nh;

	ros::ServiceClient client = nh.serviceClient<service::Service1>("service_topic_name");

	service::Service1 srv;

	srv.request.a = atoll(argv[1]);
	srv.request.b = atoll(argv[2]);

	ros::Time start = ros::Time::now();

	if (client.call(srv)){
	
	ros::Time end = ros::Time::now();

		ROS_INFO("send srv{ int64 a = %ld, int64 b = %ld}", (long int)srv.request.a, (long int)srv.request.b);
		ROS_INFO("receive srv, srv.Response.result : %ld", (long int)srv.response.result);

		ROS_INFO("latency : %lf ms", ((double)end.sec - start.sec)*1000 + ((double)end.nsec - start.nsec)/1000000);
	}
	else{
		ROS_ERROR("Failed to call service");
		return 1;
	}
	return 0;

}
