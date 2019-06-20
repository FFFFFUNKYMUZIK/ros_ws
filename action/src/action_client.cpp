#include <ros/ros.h>
#include <actionlib/client/simple_action_client.h>
#include <actionlib/client/terminal_state.h>
#include <action/Action1Action.h>
#include <action/Action1Result.h>


int main(int argc, char** argv){

ros::init(argc, argv, "action_client");

actionlib::SimpleActionClient<action::Action1Action> ac("testaction", true);

ROS_INFO("Waiting for action server to start");
ac.waitForServer();


ROS_INFO("Action server started, sending goal");
action::Action1Goal goal;
goal.order = 30;
ac.sendGoal(goal);

//50Hz, goal 30 : 4 sec
bool finished_before_timeout  = ac.waitForResult(ros::Duration(5.0));

if (finished_before_timeout)
{
 actionlib::SimpleClientGoalState state = ac.getState();
 ROS_INFO("Action finished : %s", state.toString().c_str());
 action::Action1ResultConstPtr result = ac.getResult();
ROS_INFO("result sequence of array with size %d :", (int)goal.order);
for (int i=0;i<goal.order;i++){
 ROS_INFO("%d", (int)result->sequence[i]);
}

}
else{
ROS_INFO("Action did not finish before the time out");
}

return 0;
}
