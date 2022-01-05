#include <sm_lane_navigation/sm_lane_navigation.h>

//--------------------------------------------------------------------
int main(int argc, char **argv)
{
    ros::init(argc, argv, "sm_lane_navigation");
    ros::NodeHandle nh;

    smacc::run<sm_lane_navigation::SmLaneNavigation>();
}