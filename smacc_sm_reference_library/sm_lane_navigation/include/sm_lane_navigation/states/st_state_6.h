#include <smacc/smacc.h>

namespace sm_lane_navigation
{
// STATE DECLARATION
struct State6 : smacc::SmaccState<State6, SmLaneNavigation>
{
    using SmaccState::SmaccState;

// TRANSITION TABLE
    typedef mpl::list<
    
    Transition<EvTimer<CbTimerCountdownOnce, OrTimer>, StateEnd, ENDLOOP>
    
    >reactions;

    
// STATE FUNCTIONS   
    static void staticConfigure()
    {
        configure_orthogonal<OrTimer, CbTimerCountdownOnce>(30);// EvTimer triggers once at 10 client ticks
        configure_orthogonal<OrLED, CbLEDKill>();
        configure_orthogonal<OrNavigation, CbNavigationKill>();
    }

    void runtimeConfigure()
    {
        ROS_INFO("Entering State6");
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