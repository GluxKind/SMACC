#include <smacc/smacc.h>

namespace sm_lane_navigation
{
// STATE DECLARATION
struct State5 : smacc::SmaccState<State5, SmLaneNavigation>
{
    using SmaccState::SmaccState;

// TRANSITION TABLE
    typedef mpl::list<
    
    Transition<EvTimer<CbTimerCountdownOnce, OrTimer>, State6, SUCCESS>
    
    >reactions;

    
// STATE FUNCTIONS   
    static void staticConfigure()
    {
        configure_orthogonal<OrTimer, CbTimerCountdownOnce>(60);// EvTimer triggers once at 10 client ticks
        configure_orthogonal<OrLED, CbLEDCV>();
        configure_orthogonal<OrNavigation, CbNavigationCV>();
    }

    void runtimeConfigure()
    {
        ROS_INFO("Entering State5");
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