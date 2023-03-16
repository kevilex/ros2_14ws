#include <chrono>
#include <memory>

#include "rclcpp/rclcpp.hpp"
#include "crane_interface/msg/crane_reference.hpp"                                            // CHANGE

using namespace std::chrono_literals;

class MinimalPublisher : public rclcpp::Node
{
public:
  MinimalPublisher()
  : Node("Crane_publisher"), count_(0)
  {
    publisher_ = this->create_publisher<crane_interface::msg::CraneReference>("crane_topic", 10);  // CHANGE
    timer_ = this->create_wall_timer(
      500ms, std::bind(&MinimalPublisher::timer_callback, this));
  }

private:
  void timer_callback()
  {
    auto message = crane_interface::msg::CraneReference();                                   // CHANGE
    message.crane_cylinder_velocity_reference = this->count_++;                                                     // CHANGE
    RCLCPP_INFO_STREAM(this->get_logger(), "Publishing: '" << message.crane_cylinder_velocity_reference << "'");    // CHANGE
    publisher_->publish(message);
  }
  rclcpp::TimerBase::SharedPtr timer_;
  rclcpp::Publisher<crane_interface::msg::CraneReference>::SharedPtr publisher_;             // CHANGE
  size_t count_;
};

int main(int argc, char * argv[])
{
  rclcpp::init(argc, argv);
  rclcpp::spin(std::make_shared<MinimalPublisher>());
  rclcpp::shutdown();
  return 0;
}