#pragma once

#include <smacc/smacc.h>
namespace sm_moveit_wine_serve
{
    // STATE DECLARATION
    struct StBringBottleBackNavigateSourceTable : smacc::SmaccState<StBringBottleBackNavigateSourceTable, SmMoveitWineFetch>
    {
        using SmaccState::SmaccState;

        // TRANSITION TABLE
        typedef mpl::list<
            Transition<EvActionSucceeded<ClMoveBaseZ, OrNavigation>, StPlaceBottleBack, SUCCESS>
            //Transition<EvCbSuccess<CbNavigateBackwards, OrNavigation>, StNavigateToDestinyTable, SUCCESS>
            >
            reactions;

        // STATE FUNCTIONS
        static void staticConfigure()
        {
            configure_orthogonal<OrNavigation, CbNavigateGlobalPosition>();
        }

        void runtimeConfigure()
        {
            auto *navigateGlobalPosition = this->getOrthogonal<OrNavigation>()->getClientBehavior<CbNavigateGlobalPosition>();

            ClPerceptionSystem *perceptionSystem;
            navigateGlobalPosition->requiresClient(perceptionSystem);
            perceptionSystem->nextObject();

            auto tablePose = perceptionSystem->getMainTablePose().pose;
            tablePose.position.x -= 0.85;
            navigateGlobalPosition->setGoal(tablePose);
        }

        void onExit()
        {
            ros::Duration(1.0).sleep();
        }
    };
} // namespace sm_moveit_wine_serve