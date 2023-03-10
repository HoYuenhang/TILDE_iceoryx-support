cmake_minimum_required(VERSION 3.8)
project(cpp_pubsub)

if(CMAKE_COMPILER_IS_GNUCXX OR CMAKE_CXX_COMPILER_ID MATCHES "Clang")
  add_compile_options(-Wall -Wextra -Wpedantic)
endif()

# find dependencies
find_package(ament_cmake REQUIRED)
find_package(rclcpp REQUIRED)
find_package(std_msgs REQUIRED)

find_package(tilde_cmake REQUIRED)
tilde_package()
find_package(tilde REQUIRED)

find_package(interfaces REQUIRED)

if(BUILD_TESTING)
  find_package(ament_lint_auto REQUIRED)
  # the following line skips the linter which checks for copyrights
  # uncomment the line when a copyright and license is not present in all source files
  #set(ament_cmake_copyright_FOUND TRUE)
  # the following line skips cpplint (only works in a git repo)
  # uncomment the line when this package is not in a git repo
  #set(ament_cmake_cpplint_FOUND TRUE)
  ament_lint_auto_find_test_dependencies()
endif()

add_executable(iox_listener src/iceoryx_subscriber.cpp)
ament_target_dependencies(iox_listener rclcpp interfaces tilde)

add_executable(iox_talker_loaned src/iceoryx_publisher_loaned.cpp)
ament_target_dependencies(iox_talker_loaned rclcpp interfaces tilde)

install(TARGETS iox_listener iox_talker_loaned
  DESTINATION lib/${PROJECT_NAME})

ament_package()