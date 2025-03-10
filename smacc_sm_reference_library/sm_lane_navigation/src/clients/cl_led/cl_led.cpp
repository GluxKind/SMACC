/*****************************************************************************************************************
 * ReelRobotix Inc. - Software License Agreement      Copyright (c) 2018
 * 	 Authors: Pablo Inigo Blasco, Brett Aldrich
 *
 ******************************************************************************************************************/
#include <sm_lane_navigation/clients/cl_led/cl_led.h>
//#include <pluginlib/class_list_macros.h>

namespace sm_lane_navigation
{
namespace cl_led
{

ClLED::ClLED(std::string actionServerName) : Base(actionServerName)
{
}

std::string ClLED::getName() const
{
    return "TOOL ACTION CLIENT";
}

ClLED::~ClLED()
{
}
} // namespace cl_led

//PLUGINLIB_EXPORT_CLASS(cl_led::ClLED, smacc::ISmaccComponent)
}