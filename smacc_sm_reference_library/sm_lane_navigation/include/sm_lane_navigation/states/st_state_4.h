#include <smacc/smacc.h>

namespace sm_lane_navigation
{
// STATE DECLARATION
struct State4 : smacc::SmaccState<State4, SmLaneNavigation>
{
    using SmaccState::SmaccState;

// TRANSITION TABLE
    typedef mpl::list<
    
    Transition<EvTimer<CbTimerCountdownOnce, OrTimer>, State5, SUCCESS>
    
    >reactions;

    
// STATE FUNCTIONS   
    static void staticConfigure()
    {
        configure_orthogonal<OrTimer, CbTimerCountdownOnce>(30);// EvTimer triggers once at 10 client ticks
        configure_orthogonal<OrLED, CbLEDMoveBase>();
        configure_orthogonal<OrNavigation, CbnavigationMoveBase>();

    }

    void runtimeConfigure()
    {
        ROS_INFO("Entering State4");
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