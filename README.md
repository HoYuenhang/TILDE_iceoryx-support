# TILDE_iceoryx-support demo
The project is developed based on [TILDE](https://github.com/tier4/TILDE "TILDE") and [iceoryx_can_handle_huge_data](https://github.com/sykwer/iceoryx_can_handle_huge_data "iceoryx_can_handle_huge_data").
## Adjusting the size of the data
Modify the array size.
```
## path: TILDE_iceoryx-support/iceoryx_can_handle_huge_data/interfaces/msg/StaticSizeArray.msg
int64 id
int64 timestamp
uint8[21474] data  <--
```
## Build & Install
We assume ROS2 libraries are already installed and the distribution is newer or equal to galactic.
```
source /opt/ros/humble/setup.bash
```
## Demo startup
Launch four terminals, execute the following commands in each terminal.
```
## path: TILDE_iceoryx-support/TILDE
colcon build
source install/setup.bash

## path: TILDE_iceoryx-support/iceoryx_can_handle_huge_data
colcon build
source install/setup.bash
```
Launch RouDi daemon in the first terminal.
```
## path: TILDE_iceoryx-support/iceoryx_can_handle_huge_data
iox-roudi -c roudi_config.toml
```
Start the publisher and subscriber in the second and third terminal respectively.
```
## path: TILDE_iceoryx-support/iceoryx_can_handle_huge_data
CYCLONEDDS_URI=file://$PWD/cyclonedds.xml ros2 run cpp_pubsub iox_talker_loaned
CYCLONEDDS_URI=file://$PWD/cyclonedds.xml ros2 run cpp_pubsub iox_listener
```
![message_tracking_tag.png](https://i.328888.xyz/2023/03/07/58gHX.png)
See MessageTrackingTag by execute the following commands. (The `input_infos` in MessageTrackingTag is empty because it uses zero copy)
```
ros2 topic echo iceoryx_test/message_tracking_tag
```
An example of MessageTrackingTag.
```
header:
  stamp:
    sec: 1678195388
    nanosec: 723736268
  frame_id: ''
output_info:
  topic_name: /iceoryx_test
  node_fqn: ''
  seq: 6
  pub_time:
    sec: 1678195388
    nanosec: 723737306
  pub_time_steady:
    sec: 2114
    nanosec: 140639223
  has_header_stamp: true
  header_stamp:
    sec: 1678195388
    nanosec: 723733924
input_infos: [] 
---
```
