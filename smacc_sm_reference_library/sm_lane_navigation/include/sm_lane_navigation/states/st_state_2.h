#include <smacc/smacc.h>

namespace sm_lane_navigation
{
// STATE DECLARATION
struct State2 : smacc::SmaccState<State2, SmLaneNavigation>
{
    using SmaccState::SmaccState;

// TRANSITION TABLE
    typedef mpl::list<
    
    Transition<EvTimer<CbTimerCountdownOnce, OrTimer>, State3, SUCCESS>
    
    >reactions;

    
// STATE FUNCTIONS   
    static void staticConfigure()
    {
        configure_orthogonal<OrTimer, CbTimerCountdownOnce>(3);// EvTimer triggers once at 10 client ticks
        configure_orthogonal<OrLED, CbLEDRoscore>();
        configure_orthogonal<OrNavigation, CbNavigationRoscore>();
 
    }

    void runtimeConfigure()
    {
        ROS_INFO("Entering State2");
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