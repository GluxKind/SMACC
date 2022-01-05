#pragma once

#include <smacc/smacc.h>
#include <sm_lane_navigation/clients/cl_navigation/cl_navigation.h>

namespace sm_lane_navigation
{
namespace cl_navigation
{
class CbNavigationCV : public smacc::SmaccClientBehavior
{
public:
  cl_navigation::ClNavigation *NavigationActionClient_;

  virtual void onEntry() override
  {
    this->requiresClient(NavigationActionClient_);

    cl_navigation::ClNavigation::Goal goal;
    goal.command = cl_navigation::ClNavigation::Goal::CMD_CV;
    NavigationActionClient_->sendGoal(goal);
  }

  virtual void onExit() override
  {
    //ROS_INFO("Entering ToolClientBehavior");
  }
};
} // namespace cl_navigation
} // namespace sm_lane_navigation
