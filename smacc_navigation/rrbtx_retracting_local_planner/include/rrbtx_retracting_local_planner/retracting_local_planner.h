/*****************************************************************************************************************
 * ReelRobotix Inc. - Software License Agreement      Copyright (c) 2018
 * 	 Authors: Pablo Inigo Blasco, Brett Aldrich
 *
 ******************************************************************************************************************/
#pragma once
#include <dynamic_reconfigure/server.h>
#include <geometry_msgs/PoseStamped.h>
#include <nav_core/base_local_planner.h>
#include <rrbtx_retracting_local_planner/RetractingLocalPlannerConfig.h>

typedef double meter;
typedef double rad;

namespace rrbtx_retracting_local_planner {
class RetractingLocalPlanner : public nav_core::BaseLocalPlanner {

public:
    RetractingLocalPlanner();

    virtual ~RetractingLocalPlanner();

    /**
   * @brief  Given the current position, orientation, and velocity of the robot: compute velocity commands to send to the robot mobile base
   * @param cmd_vel Will be filled with the velocity command to be passed to the robot base
   * @return True if a valid velocity command was found, false otherwise
   */
    virtual bool computeVelocityCommands(geometry_msgs::Twist& cmd_vel) override;

    /**
   * @brief  Check if the goal pose has been achieved by the local planner
   * @return True if achieved, false otherwise
   */
    virtual bool isGoalReached() override;

    /**
   * @brief  Set the plan that the local planner is following
   * @param plan The plan to pass to the local planner
   * @return True if the plan was updated successfully, false otherwise
   */
    virtual bool setPlan(const std::vector<geometry_msgs::PoseStamped>& plan) override;

    /**
   * @brief  Constructs the local planner
   * @param name The name to give this instance of the local planner
   * @param tf A pointer to a transform listener
   * @param costmap_ros The cost map to use for assigning costs to local plans
   */
    virtual void initialize(std::string name, tf::TransformListener* tf, costmap_2d::Costmap2DROS* costmapRos_) override;

private:
    void reconfigCB(rrbtx_retracting_local_planner::RetractingLocalPlannerConfig& config, uint32_t level);

    void publishGoalMarker(double x, double y, double phi);

    dynamic_reconfigure::Server<rrbtx_retracting_local_planner::RetractingLocalPlannerConfig> paramServer_;
    dynamic_reconfigure::Server<rrbtx_retracting_local_planner::RetractingLocalPlannerConfig>::CallbackType f;

    std::vector<geometry_msgs::PoseStamped> backwardsPlanPath_;
    costmap_2d::Costmap2DROS* costmapRos_;

    ros::Publisher goalMarkerPublisher_;

    double k_rho_;
    double k_alpha_;
    double k_betta_;

    bool goalReached_;

    double alpha_offset_;
    double betta_offset_;

    meter carrot_distance_;
    rad carrot_angular_distance_;

    // references the current point inside the backwardsPlanPath were the robot is located
    int currentPoseIndex_;
};
}
