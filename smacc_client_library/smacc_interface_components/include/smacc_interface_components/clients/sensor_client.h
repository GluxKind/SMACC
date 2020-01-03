#pragma once

#include <smacc/client_bases/smacc_subscriber_client.h>
#include <boost/statechart/event.hpp>

#include <ros/ros.h>
#include <ros/duration.h>
#include <boost/signals2.hpp>
#include <boost/optional/optional_io.hpp>

namespace smacc
{

template <typename TSource, typename TObjectTag>
struct EvTopicMessageTimeout : sc::event<EvTopicMessageTimeout<TSource, TObjectTag>>
{
  ros::TimerEvent timerData;
};

using namespace smacc::client_bases;

//---------------------------------------------------------------
template <typename MessageType>
class SensorClient : public smacc::client_bases::SmaccSubscriberClient<MessageType>
{
public:
  typedef MessageType TMessageType;
  SmaccSignal<void(const ros::TimerEvent &)> onMessageTimeout_;

  SensorClient()
      : smacc::client_bases::SmaccSubscriberClient<MessageType>()
  {
    ROS_INFO("CbLidarSensor constructor");
    initialized_ = false;
  }

  template <typename T>
  boost::signals2::connection onMessageTimeout(void (T::*callback)(const ros::TimerEvent &), T *object)
  {
    return this->stateMachine_->createSignalConnection(onMessageTimeout_, callback, object);
  }

  std::function<void(const ros::TimerEvent &ev)> postTimeoutMessageEvent;

  template <typename TObjectTag, typename TDerived>
  void configureEventSourceTypes()
  {
    SmaccSubscriberClient<MessageType>::template configureEventSourceTypes<TObjectTag, TDerived>();

    this->postTimeoutMessageEvent = [=](auto &timerdata) {
      onMessageTimeout_(timerdata);

      auto event = new EvTopicMessageTimeout<TDerived, TObjectTag>();
      event->timerData = timerdata;
      this->postEvent(event);
    };
  }

  virtual void initialize() override
  {
    if (!initialized_)
    {
      SmaccSubscriberClient<MessageType>::initialize();

      this->onMessageReceived(&SensorClient<MessageType>::resetTimer, this);

      if (timeout_)
      {
        timeoutTimer_ = this->nh_.createTimer(*timeout_, boost::bind(&SensorClient<MessageType>::timeoutCallback, this, _1));
        timeoutTimer_.start();
      }
      else
      {
        ROS_WARN("Timeout sensor client not set, skipping timeout watchdog funcionality");
      }

      initialized_ = true;
    }
  }

  boost::optional<ros::Duration> timeout_;

protected:
  void resetTimer(const MessageType &msg)
  {
    //reseting the timer
    this->timeoutTimer_.stop();
    this->timeoutTimer_.start();
  }

private:
  ros::Timer timeoutTimer_;
  bool initialized_;

  void timeoutCallback(const ros::TimerEvent &timerdata)
  {
    postTimeoutMessageEvent(timerdata);
  }
};
} // namespace smacc