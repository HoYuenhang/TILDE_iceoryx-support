# TILDE_iceoryx-support (testing)
---
## demo起動手順
２つのターミナルを起動する
TILDEをビルド(source)する
```
cd TILDE_iceoryx-support/TILDE
colcon build
source install/setup.bash
```
iceoryx demoをビルド(source)する
```
cd TILDE_iceoryx-support/iceoryx_can_handle_huge_data
colcon build
source install/setup.bash
```
一番目のターミナルにRouDi daemonを起動する
```
cd TILDE_iceoryx-support/iceoryx_can_handle_huge_data
iox-roudi -c roudi_config.toml
```
二番目のターミナルにノードを起動する
```
cd TILDE_iceoryx-support/iceoryx_can_handle_huge_data
CYCLONEDDS_URI=file://$PWD/cyclonedds.xml ros2 run cpp_pubsub iox_talker_loaned
CYCLONEDDS_URI=file://$PWD/cyclonedds.xml ros2 run cpp_pubsub iox_listener
```
