#include <smacc/smacc.h>
namespace sm_moveit_4
{
    // STATE DECLARATION
    struct StNavigateToSourceTable : smacc::SmaccState<StNavigateToSourceTable, SmMoveIt4>
    {
        using SmaccState::SmaccState;

        // TRANSITION TABLE
        typedef mpl::list<

            // Transition<EvActionSucceeded<ClMoveBaseZ, OrNavigation>, StRotate180, SUCCESS>
            Transition<EvActionSucceeded<ClMoveBaseZ, OrNavigation>, SS1::SsPickObject, SUCCESS>,
            Transition<EvActionAborted<ClMoveBaseZ, OrNavigation>, StNavigateToSourceTable, ABORT>>
            reactions;

        // STATE FUNCTIONS
        static void staticConfigure()
        {
            configure_orthogonal_runtime<OrNavigation, CbNavigateGlobalPosition>
                                                            (
                                                                [](auto& navigateGlobalPosition)
                                                                {
                                                                    ClPerceptionSystem* perceptionSystem;
                                                                    navigateGlobalPosition.requiresClient(perceptionSystem);
                                                                    
                                                                    auto mainTablePose = perceptionSystem->getMainTablePose().pose;
                                                                    mainTablePose.position.x -= 0.85;

                                                                    geometry_msgs::PoseStamped nextCubePose;
                                                                    if(perceptionSystem->decidePickCubePose(nextCubePose))
                                                                    {
                                                                        // align with the cube in the y axis
                                                                        mainTablePose.position.y = nextCubePose.pose.position.y;



                                                                        navigateGlobalPosition.setGoal(mainTablePose);
                                                                    }
                                                                    else
                                                                    {
                                                                        ROS_WARN("[DEMO COMPLETED! All cubes are on their tables!]");
                                                                        ros::spin();
                                                                    }
                                                                }
                                                            );
        }

        void runtimeConfigure()
        {
            ROS_INFO("runtime");
        }

        void OnEntry()
        {
            ROS_INFO("state on entry");
        }
    };
} // namespace sm_moveit_4