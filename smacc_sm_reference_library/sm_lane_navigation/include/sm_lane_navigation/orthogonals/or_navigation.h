#pragma once
#include <smacc/smacc_orthogonal.h>
#include <sm_lane_navigation/clients/cl_navigation/cl_navigation.h>

namespace sm_lane_navigation
{
class OrNavigation : public smacc::Orthogonal<OrNavigation>
{
public:
    virtual void onInitialize() override
    {
        auto actionclient = this->createClient<cl_navigation::ClNavigation>("navigation_action_server");
        actionclient->initialize();
    }
};
} // namespace sm_lane_navigation