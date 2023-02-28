#include <functional>
#include <memory>
#include "rclcpp/rclcpp.hpp"
#include "rclcpp/qos.hpp"

// tildeを導入
#include "tilde/tilde_node.hpp"
#include "tilde/tilde_publisher.hpp"

#include <sys/time.h>

#include "interfaces/msg/static_size_array.hpp"

using std::placeholders::_1;

class MinimalSubscriber : public tilde::TildeNode {
public:
  MinimalSubscriber() : TildeNode("minimal_subscriber") {
    subscription_ = this->create_tilde_subscription<interfaces::msg::StaticSizeArray>(
      "topic", 1, std::bind(&MinimalSubscriber::topic_callback, this, _1));
  }

private:
  void topic_callback(const interfaces::msg::StaticSizeArray::SharedPtr msg) const {
    struct timeval tv;
    gettimeofday(&tv, NULL);
    uint64_t latency = tv.tv_sec * 1000 * 1000 + tv.tv_usec - msg->timestamp;

    RCLCPP_INFO(this->get_logger(), "(iceoryx_tilde)I heard message ID: '%ld', latency = %ld us", msg->id, latency);
  }

  rclcpp::Subscription<interfaces::msg::StaticSizeArray>::SharedPtr subscription_;
};

int main(int argc, char * argv[])
{
  rclcpp::init(argc, argv);
  rclcpp::spin(std::make_shared<MinimalSubscriber>());
  rclcpp::shutdown();
  return 0;
}
