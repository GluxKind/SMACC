#pragma once

#include <smacc/smacc.h>
namespace sm_moveit_wine_serve
{
    struct StNavigationPosture : smacc::SmaccState<StNavigationPosture, SmMoveitWineFetch>
    {
        using SmaccState::SmaccState;

        // TRANSITION TABLE
        typedef mpl::list<
            Transition<EvActionSucceeded<ClMoveBaseZ, OrNavigation>, StNavigateToSourceTable, SUCCESS>
            /*Transition<EvCbSuccess<CbMoveKnownState, OrArm>, StNavigateToSourceTable>*/
            /*Transition<EvCbFailure<CbMoveKnownState, OrArm>, StNavigationPosture, ABORT>*/
            >
            reactions;

        // STATE FUNCTIONS
        static void staticConfigure()
        {
            //configure_orthogonal<OrArm, CbMoveKnownState>("sm_moveit_wine_serve", "config/manipulation/known_states/nav_posture.yaml");
            configure_orthogonal<OrArm, CbUndoLastTrajectory>(1);
            configure_orthogonal<OrNavigation, CbNavigateBackwards>(0.4);
        }

        void runtimeConfigure()
        {
            ros::WallDuration(2).sleep();
        }

        void onExit()
        {
            ClPerceptionSystem *perceptionSystem;
            this->requiresClient(perceptionSystem);
            perceptionSystem->nextObject();
        }
    };
} // namespace sm_moveit_wine_serve