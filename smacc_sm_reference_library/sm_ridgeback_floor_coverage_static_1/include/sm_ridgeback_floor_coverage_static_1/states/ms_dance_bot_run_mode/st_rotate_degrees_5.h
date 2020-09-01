#include <smacc/smacc.h>
namespace sm_ridgeback_floor_coverage_static_1
{
  // STATE DECLARATION
  struct StRotateDegrees5 : smacc::SmaccState<StRotateDegrees5, MsDanceBotRunMode>
  {
    using SmaccState::SmaccState;

    // TRANSITION TABLE
    typedef mpl::list<

        Transition<EvCbSuccess<CbRotate, OrNavigation>, StNavigateToWaypointsX>,
        Transition<EvCbFailure<CbRotate, OrNavigation>, StNavigateToWaypointsX>

        >
        reactions;

    // STATE FUNCTIONS
    static void staticConfigure()
    {
      configure_orthogonal<OrNavigation, CbRotate>(/*30*/ -180);
      configure_orthogonal<OrLED, CbLEDOff>();
      configure_orthogonal<OrObstaclePerception, CbLidarSensor>();
    }
  };
} // namespace sm_ridgeback_floor_coverage_static_1