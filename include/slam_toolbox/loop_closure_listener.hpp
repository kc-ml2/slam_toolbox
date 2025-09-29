#pragma once

#include <memory>
#include <functional>
#include <string>

#include <rclcpp/rclcpp.hpp>
#include <rclcpp_lifecycle/lifecycle_publisher.hpp>

#include "slam_toolbox/msg/loop_closure_event.hpp"

#include "karto_sdk/Mapper.h"

namespace slam_toolbox {


class LoopClosureListener final : public karto::MapperLoopClosureListener {
public:
  LoopClosureListener(
      std::weak_ptr<rclcpp_lifecycle::LifecyclePublisher<slam_toolbox::msg::LoopClosureEvent>> pub,
      std::weak_ptr<rclcpp::Clock> clock,
      std::function<void()> republish_graph);

  void EndLoopClosure(const std::string & rInfo) override;

private:
  std::weak_ptr<rclcpp_lifecycle::LifecyclePublisher<slam_toolbox::msg::LoopClosureEvent>> pub_;
  std::weak_ptr<rclcpp::Clock> clock_;
  std::function<void()> republish_graph_;
};

} // namespace slam_toolbox
