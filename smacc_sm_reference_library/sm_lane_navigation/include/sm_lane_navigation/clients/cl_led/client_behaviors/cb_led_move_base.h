#pragma once

#include <smacc/smacc.h>
#include <sm_lane_navigation/clients/cl_led/cl_led.h>

namespace sm_lane_navigation
{
namespace cl_led
{
class CbLEDMoveBase : public smacc::SmaccClientBehavior
{
public:
  cl_led::ClLED *ledActionClient_;

  virtual void onEntry() override
  {
    this->requiresClient(ledActionClient_);

    cl_led::ClLED::Goal goal;
    goal.command = cl_led::ClLED::Goal::CMD_MOVE_BASE;
    ledActionClient_->sendGoal(goal);
  }

  virtual void onExit() override
  {
    //ROS_INFO("Entering ToolClientBehavior");
  }
};
} // namespace cl_led
} // namespace sm_lane_navigation
