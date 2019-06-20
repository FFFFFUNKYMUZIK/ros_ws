#include "ros/ros.h"
#include "service/Service1.h"

#define PLUS	1
#define MINUS	2
#define MULT	3
#define DIVS	4

int g_operator = PLUS;


bool Servercb(service::Service1::Request& req,
		service::Service1::Response& res){


	switch(g_operator)
	{
	default:
	case PLUS:
	res.result = req.a + req.b;
	break;
	case MINUS:
	res.result = req.a - req.b;
	break;
	case MULT:
	res.result = req.a * req.b;
	break;
	case DIVS:
	if(req.b == 0){
	res.result = 0;
	}
	else{
	res.result = req.a/req.b;
	}
	break;
	}
		
	ROS_INFO("request: x = %ld, y = %ld", (long int)req.a, (long int)req.b);
	ROS_INFO("result : f(x,y) = %ld", (long int)res.result);
	return true;
}


int main(int argc, char** argv){

	ros::init(argc, argv, "service_server_name");
	ros::NodeHandle nh;

	ros::Rate r(10);

	nh.setParam("cal_method", PLUS);

	ros::ServiceServer service_server = nh.advertiseService("service_topic_name", Servercb);

	ROS_INFO("ready service server!");

	while(1){
	nh.getParam("cal_method", g_operator);	
	ros::spinOnce();
	r.sleep();

	}
	return 0;
}
