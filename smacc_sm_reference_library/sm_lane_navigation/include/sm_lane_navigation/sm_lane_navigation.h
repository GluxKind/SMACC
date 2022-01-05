#include <smacc/smacc.h>

// CLIENTS
#include <ros_timer_client/cl_ros_timer.h>

// ORTHOGONALS
#include <sm_lane_navigation/orthogonals/or_timer.h>
#include <sm_lane_navigation/orthogonals/or_led.h>
#include <sm_lane_navigation/orthogonals/or_navigation.h>

//CLIENT BEHAVIORS
#include <ros_timer_client/client_behaviors/cb_timer_countdown_loop.h>
#include <ros_timer_client/client_behaviors/cb_timer_countdown_once.h>

#include <sm_lane_navigation/clients/cl_led/client_behaviors/cb_led_roscore.h>
#include <sm_lane_navigation/clients/cl_led/client_behaviors/cb_led_cv.h>
#include <sm_lane_navigation/clients/cl_led/client_behaviors/cb_led_move_base.h>
#include <sm_lane_navigation/clients/cl_led/client_behaviors/cb_led_zed.h>
#include <sm_lane_navigation/clients/cl_led/client_behaviors/cb_led_kill.h>


#include <sm_lane_navigation/clients/cl_navigation/client_behaviors/cb_navigation_roscore.h>
#include <sm_lane_navigation/clients/cl_navigation/client_behaviors/cb_navigation_cv.h>
#include <sm_lane_navigation/clients/cl_navigation/client_behaviors/cb_navigation_move_base.h>
#include <sm_lane_navigation/clients/cl_navigation/client_behaviors/cb_navigation_zed.h>
#include <sm_lane_navigation/clients/cl_navigation/client_behaviors/cb_navigation_kill.h>


using namespace boost;
using namespace smacc;
using namespace sm_lane_navigation::cl_led;
using namespace sm_lane_navigation::cl_navigation;

namespace sm_lane_navigation
{

//STATE
class State1;
class State2;
class State3;
class State4;
class State5;
class State6;
class StateEnd;


//--------------------------------------------------------------------
//STATE_MACHINE
struct SmLaneNavigation
    : public smacc::SmaccStateMachineBase<SmLaneNavigation, State1>
{
    using SmaccStateMachineBase::SmaccStateMachineBase;

    virtual void onInitialize() override
    {
        this->createOrthogonal<OrTimer>();
        this->createOrthogonal<OrLED>();
        this->createOrthogonal<OrNavigation>();
    }
};

} // namespace sm_lane_navigation

#include <sm_lane_navigation/states/st_state_1.h>
#include <sm_lane_navigation/states/st_state_2.h>
#include <sm_lane_navigation/states/st_state_3.h>
#include <sm_lane_navigation/states/st_state_4.h>
#include <sm_lane_navigation/states/st_state_5.h>
#include <sm_lane_navigation/states/st_state_6.h>
#include <sm_lane_navigation/states/st_state_end.h>