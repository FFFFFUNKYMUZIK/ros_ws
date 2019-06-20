#include <ros/ros.h>
#include <actionlib/server/simple_action_server.h>
#include <action/Action1Action.h>

class Action1Action
{

 protected:

ros::NodeHandle nh_;

actionlib::SimpleActionServer<action::Action1Action> as_;

std::string action_name_;

action::Action1Feedback feedback_;
action::Action1Result result_;

 public:

Action1Action(std::string name) :
 as_(nh_, name, boost::bind(&Action1Action::executeCB, this, _1), false),
 action_name_(name)
{
as_.start();
}

~Action1Action(){}

void executeCB(const action::Action1GoalConstPtr &goal){

ros::Rate r(50);
bool success = true;

feedback_.sequence.clear();
feedback_.sequence.push_back(0);
feedback_.sequence.push_back(1);

ROS_INFO("%s : Executing, creating fibonacci sequence of order %i with seeds %i, %i", action_name_.c_str(), goal->order, feedback_.sequence[0], feedback_.sequence[1]);

for(int i=1;i<=goal->order;i++){
if (as_.isPreemptRequested() || !ros::ok()){
 ROS_INFO("%s : Preempted", action_name_.c_str());
 as_.setPreempted();
 success = false;
 break;
}

feedback_.sequence.push_back(feedback_.sequence[i]+feedback_.sequence[i-1]);
as_.publishFeedback(feedback_);
r.sleep();
}


if (success){

 result_.sequence = feedback_.sequence;
 ROS_INFO("%s : Succeeded", action_name_.c_str());
 as_.setSucceeded(result_);
}

}

};

int main(int argc, char** argv){

ros::init(argc, argv, "action_server");
Action1Action testaction("testaction");
ros::spin();
return 0;

}
