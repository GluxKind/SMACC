#pragma once

#include <smacc/client_bases/smacc_action_client_base.h>
#include <sm_lane_navigation/NavigationControlAction.h>

namespace sm_lane_navigation
{
namespace cl_navigation
{
class ClNavigation : public smacc::client_bases::SmaccActionClientBase<sm_lane_navigation::NavigationControlAction>
{
public:
    SMACC_ACTION_CLIENT_DEFINITION(sm_lane_navigation::NavigationControlAction);

    ClNavigation(std::string actionServerName);
    virtual std::string getName() const override;
    virtual ~ClNavigation();
};
} // namespace cl_navigation
}