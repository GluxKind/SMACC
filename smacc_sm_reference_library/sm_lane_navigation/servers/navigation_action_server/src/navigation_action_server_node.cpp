/*****************************************************************************************************************
 * ReelRobotix Inc. - Software License Agreement      Copyright (c) 2018
 * 	 Authors: Pablo Inigo Blasco, Brett Aldrich
 *
 ******************************************************************************************************************/
#include <actionlib/server/simple_action_server.h>
#include <std_msgs/UInt8.h>
#include <functional>
#include <dynamic_reconfigure/DoubleParameter.h>
#include <dynamic_reconfigure/Reconfigure.h>
#include <dynamic_reconfigure/Config.h>
#include <sm_lane_navigation/NavigationControlAction.h>
#include <sm_lane_navigation/NavigationControlActionResult.h>
#include <sm_lane_navigation/NavigationControlResult.h>
#include <memory>
#include <visualization_msgs/MarkerArray.h>
#include <std_msgs/Int8.h>
#include <sm_lane_navigation/RosLaunch.h>


typedef actionlib::SimpleActionServer<sm_lane_navigation::NavigationControlAction> Server;



// This class describes a preemptable-on/off tool action server to be used from smacc
// shows in rviz a sphere whoose color describe the current state (unknown, running, idle)
class NavigationActionServer
{
public:
  std::shared_ptr<Server> as_ ;

  // ros::Publisher stateMarkerPublisher_;

  ros::ServiceClient stateNavigationClient_;

  sm_lane_navigation::NavigationControlGoal cmd;

  uint8_t currentState_;

  uint8_t previousState_;

/**
******************************************************************************************************************
* constructor()
******************************************************************************************************************
*/
  NavigationActionServer()
  {
    currentState_ =  sm_lane_navigation::NavigationControlResult::STATE_UNKNOWN;
  }

/**
******************************************************************************************************************
* publishFeedback()
******************************************************************************************************************
*/
void publishFeedback()  // Note: "Action" is not appended to DoDishes here
{
    sm_lane_navigation::NavigationControlFeedback feedback_msg;
    
    as_->publishFeedback(feedback_msg);
}

/**
******************************************************************************************************************
* execute()
******************************************************************************************************************
*/
void execute(const sm_lane_navigation::NavigationControlGoalConstPtr& goal)  // Note: "Action" is not appended to DoDishes here
{
  ROS_INFO_STREAM("Tool action server request: "<< *goal);
  cmd = *goal;

  if(goal->command == sm_lane_navigation::NavigationControlGoal::CMD_ROSCORE)
  {
    currentState_ =  sm_lane_navigation::NavigationControlResult::STATE_INIT;
  }
  else  if (goal->command == sm_lane_navigation::NavigationControlGoal::CMD_ZED)
  {
    currentState_ =  sm_lane_navigation::NavigationControlResult::STATE_CAM;
  }
  else if (goal->command == sm_lane_navigation::NavigationControlGoal::CMD_MOVE_BASE)
  {
    currentState_ =  sm_lane_navigation::NavigationControlResult::STATE_MOVE;
  }
  else if (goal->command == sm_lane_navigation::NavigationControlGoal::CMD_CV)
  {
    currentState_ =  sm_lane_navigation::NavigationControlResult::STATE_GOAL;
  }
  else if (goal->command == sm_lane_navigation::NavigationControlGoal::CMD_KILL)
  {
    currentState_ =  sm_lane_navigation::NavigationControlResult::STATE_OFF;
  }

  // 10Hz internal loop
  ros::Rate rate(1);

  while(ros::ok())
  {
    if(as_->isPreemptRequested())
    {
       // a new request is being executed, we will stop this one
       ROS_WARN("NavigationActionServer request preempted. Forgetting older request.");
       as_->setPreempted(); 
       return;
    }
    
    publishFeedback();
    // publishStateMarker();
    sm_lane_navigation::RosLaunch srv;
    if (currentState_ == previousState_) {
      previousState_ = currentState_;
      continue;
    } 
    if(currentState_ == sm_lane_navigation::NavigationControlResult::STATE_INIT)
    { 
      previousState_ = sm_lane_navigation::NavigationControlResult::STATE_INIT;
      srv.request.launchStack = 0;
      if(stateNavigationClient_.call(srv)){
        ROS_INFO("%s", srv.response.message);
      } else{
        ROS_ERROR("Failed to call service");
      }
      
    }
    else if (currentState_ == sm_lane_navigation::NavigationControlResult::STATE_CAM)
    {
      previousState_ = sm_lane_navigation::NavigationControlResult::STATE_CAM;
      srv.request.launchStack = 1;
      if(stateNavigationClient_.call(srv)){
        ROS_INFO("%s", srv.response.message);
      } else{
        ROS_ERROR("Failed to call service");
      }
    }
    else if (currentState_ == sm_lane_navigation::NavigationControlResult::STATE_MOVE)
    {
      previousState_ = sm_lane_navigation::NavigationControlResult::STATE_MOVE;
      srv.request.launchStack = 2;
      if(stateNavigationClient_.call(srv)){
        ROS_INFO("%s", srv.response.message);
      } else{
        ROS_ERROR("Failed to call service");
      }    }
    else if (currentState_ == sm_lane_navigation::NavigationControlResult::STATE_GOAL)
    {
      previousState_ = sm_lane_navigation::NavigationControlResult::STATE_GOAL;
      srv.request.launchStack = 3;
      if(stateNavigationClient_.call(srv)){
        ROS_INFO("%s", srv.response.message);
      } else{
        ROS_ERROR("Failed to call service");
      }    }

    else if (currentState_ == sm_lane_navigation::NavigationControlResult::STATE_OFF)
    {
      previousState_ = sm_lane_navigation::NavigationControlResult::STATE_OFF;
      srv.request.launchStack = -1;
      if(stateNavigationClient_.call(srv)){
        ROS_INFO("%s", srv.response.message);
      } else{
        ROS_ERROR("Failed to call service");
      }
    }

    else
    {
      previousState_ = sm_lane_navigation::NavigationControlResult::STATE_UNKNOWN;
      srv.request.launchStack = -2;
      if(stateNavigationClient_.call(srv)){
        ROS_INFO("%s", srv.response.message);
      } else{
        ROS_ERROR("Failed to call service");
      }    }


    rate.sleep();
  }

   // never reach succeded because were are interested in keeping the feedback alive
   as_->setSucceeded();
}

/**
******************************************************************************************************************
* run()
******************************************************************************************************************
*/
void run()
{
  ros::NodeHandle n;
  ROS_INFO("Creating tool action server");

  as_ = std::make_shared<Server>(n, "navigation_action_server", boost::bind(&NavigationActionServer::execute, this,  _1), false);
  ROS_INFO("Starting Tool Action Server");

  // stateNavigationClient_ = n.serviceClient<sm_lane_navigation::RosLaunch>("roslaunch_server");

  stateNavigationClient_ = n.serviceClient<sm_lane_navigation::RosLaunch>("handle_launch");


  as_->start();

  ros::spin();
}

};
/**
******************************************************************************************************************
* main()
******************************************************************************************************************
*/
int main(int argc, char** argv)
{
  ros::init(argc, argv, "navigation_action_server_node");
  NavigationActionServer NavigationActionServer;
  NavigationActionServer.run();

  return 0;
}

