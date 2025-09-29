#include "slam_toolbox/loop_closure_listener.hpp"

namespace slam_toolbox {

LoopClosureListener::LoopClosureListener(
    std::weak_ptr<rclcpp_lifecycle::LifecyclePublisher<slam_toolbox::msg::LoopClosureEvent>> pub,
    std::weak_ptr<rclcpp::Clock> clock,
    std::function<void()> republish_graph)
: pub_(std::move(pub)), clock_(std::move(clock)), republish_graph_(std::move(republish_graph)) {}

void LoopClosureListener::EndLoopClosure(const std::string & /*rInfo*/) {
  auto spub = pub_.lock();
  auto sclk = clock_.lock();
  if (!spub || !sclk) {
    return; 
  }

  slam_toolbox::msg::LoopClosureEvent ev;
  ev.stamp = sclk->now();    
  spub->publish(ev);

  if (republish_graph_) {
    republish_graph_();
  }
}

} // namespace slam_toolbox
