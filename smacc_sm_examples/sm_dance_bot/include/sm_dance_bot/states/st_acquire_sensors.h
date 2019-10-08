using namespace smacc;

struct StAcquireSensors : smacc::SmaccState<StAcquireSensors, SmDanceBot>
{
   using SmaccState::SmaccState;

   typedef mpl::list<

       // Expected event
       sc::transition<EvStateFinish<StAcquireSensors>, StNavigateToWaypointsX>,

       // Keyboard event
       sc::transition<EvKeyPressN<SbKeyboard>, StNavigateToWaypointsX>,

       // Sensor events
       sc::custom_reaction<EvTopicMessage<LidarSensor>>,
       sc::custom_reaction<EvTopicMessage<smacc::SensorTopic<sensor_msgs::Temperature>>>>
       reactions;

   AllEventAggregator allSensorsReady;

   static void onDefinition()
   {
      static_configure<ObstaclePerceptionOrthogonal, LidarSensor>();
      static_configure<KeyboardOrthogonal, SbKeyboard>();
      static_configure<PublisherOrthogonal, SbStringPublisher>("Hello World!");
      static_configure<SensorOrthogonal, SbConditionTemperatureSensor>();
      static_configure<Service3Orthogonal, Service3Behavior>(Service3Command::SERVICE3_ON);
   }

   void onInitialize()
   {
      allSensorsReady.setTriggerEventTypesCount(2);
   }

   sc::result react(const EvTopicMessage<LidarSensor> &ev)
   {
      ROS_INFO_ONCE("Lidar sensor is ready");

      if (allSensorsReady.notify(ev))
         this->throwFinishEvent();

      return discard_event();
   }

   sc::result react(const EvTopicMessage<smacc::SensorTopic<sensor_msgs::Temperature>> &ev)
   {
      ROS_INFO_ONCE("Temperature sensor is ready");
      if (allSensorsReady.notify(ev))
         this->throwFinishEvent();

      return discard_event();
   }
};
