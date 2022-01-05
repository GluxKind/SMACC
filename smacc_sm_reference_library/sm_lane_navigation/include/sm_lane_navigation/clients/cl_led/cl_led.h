#pragma once

#include <smacc/client_bases/smacc_action_client_base.h>
#include <sm_lane_navigation/LEDControlAction.h>

namespace sm_lane_navigation
{
namespace cl_led
{
class ClLED : public smacc::client_bases::SmaccActionClientBase<sm_lane_navigation::LEDControlAction>
{
public:
    SMACC_ACTION_CLIENT_DEFINITION(sm_lane_navigation::LEDControlAction);

    ClLED(std::string actionServerName);
    virtual std::string getName() const override;
    virtual ~ClLED();
};
} // namespace cl_led
}