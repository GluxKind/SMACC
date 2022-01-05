#include <smacc/smacc.h>

namespace sm_lane_navigation
{
// STATE DECLARATION
struct State3 : smacc::SmaccState<State3, SmLaneNavigation>
{
    using SmaccState::SmaccState;

// TRANSITION TABLE
    typedef mpl::list<
    
    Transition<EvTimer<CbTimerCountdownOnce, OrTimer>, State4, SUCCESS>
    
    >reactions;

    
// STATE FUNCTIONS   
    static void staticConfigure()
    {
        configure_orthogonal<OrTimer, CbTimerCountdownOnce>(10);// EvTimer triggers once at 10 client ticks
        configure_orthogonal<OrLED, CbLEDZed>();
        configure_orthogonal<OrNavigation, CbNavigationZed>();
 
    }

    void runtimeConfigure()
    {
        ROS_INFO("Entering State3");
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