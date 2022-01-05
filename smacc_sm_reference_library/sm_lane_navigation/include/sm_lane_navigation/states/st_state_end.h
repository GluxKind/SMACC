#include <smacc/smacc.h>

namespace sm_lane_navigation
{
// STATE DECLARATION
struct StateEnd : smacc::SmaccState<StateEnd, SmLaneNavigation>
{
    using SmaccState::SmaccState;


    
// STATE FUNCTIONS   
    static void staticConfigure()
    {
    }

    void runtimeConfigure()
    {
        ROS_INFO("Entering StateEnd");
    }
       
    void onEntry()
    {
        ROS_INFO("On Entry!");
    }

    void onExit()
    {
        ROS_INFO("On Exit!");
    }
  
};
}