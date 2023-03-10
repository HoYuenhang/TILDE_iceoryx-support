#include <chrono>
#include <functional>
#include <memory>
#include <vector>
#include "rclcpp/rclcpp.hpp"
#include "rclcpp/qos.hpp"

#include "tilde/tilde_node.hpp"
#include "tilde/tilde_publisher.hpp"

#include <sys/time.h>

#include "interfaces/msg/static_size_array.hpp"

using namespace std::chrono_literals;

class MinimalPublisher : public tilde::TildeNode {
public:
  MinimalPublisher() : TildeNode("publisher"), count_(0) {
    //auto qos = rclcpp::QoS(1).best_effort().durability_volatile().keep_last(1);
    publisher_ = this->create_tilde_publisher<interfaces::msg::StaticSizeArray>("iceoryx_test", 1);
    timer_ = this->create_wall_timer(3000ms, std::bind(&MinimalPublisher::timer_callback, this));
  }

private:
  void timer_callback() {
    auto message = publisher_->borrow_loaned_message();
    message.get().id = count_++;

    RCLCPP_INFO(this->get_logger(), "(tilde_iceoryx-support) Publishing Message ID: '%ld'", message.get().id);

    struct timeval tv;
    gettimeofday(&tv, NULL);
    message.get().timestamp = tv.tv_sec * 1000 * 1000 + tv.tv_usec;

    publisher_->publish(std::move(message));
  }

  rclcpp::TimerBase::SharedPtr timer_;
  tilde::TildePublisher<interfaces::msg::StaticSizeArray>::SharedPtr publisher_;
  size_t count_;
};

int main(int argc, char * argv[]) {
  rclcpp::init(argc, argv);
  rclcpp::spin(std::make_shared<MinimalPublisher>());
  rclcpp::shutdown();
  return 0;
}
