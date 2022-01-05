/*****************************************************************************************************************
 * ReelRobotix Inc. - Software License Agreement      Copyright (c) 2018
 * 	 Authors: Pablo Inigo Blasco, Brett Aldrich
 *
 ******************************************************************************************************************/
#include <sm_lane_navigation/clients/cl_navigation/cl_navigation.h>
//#include <pluginlib/class_list_macros.h>

namespace sm_lane_navigation
{
namespace cl_navigation
{

ClNavigation::ClNavigation(std::string actionServerName) : Base(actionServerName)
{
}

std::string ClNavigation::getName() const
{
    return "TOOL ACTION CLIENT";
}

ClNavigation::~ClNavigation()
{
}
} // namespace cl_navigation

//PLUGINLIB_EXPORT_CLASS(cl_navigation::ClNavigation, smacc::ISmaccComponent)
}