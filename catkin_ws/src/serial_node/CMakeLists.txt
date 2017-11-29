cmake_minimum_required(VERSION 2.8.3)
project(serial_node)

find_package(catkin REQUIRED COMPONENTS
  roscpp
  rospy

  std_msgs
  message_generation
)

add_message_files(
  DIRECTORY
  msg
  FILES
  Serial.msg
)

generate_messages(
  DEPENDENCIES
  std_msgs

)

catkin_package(
  CATKIN_DEPENDS message_runtime
)


include_directories(
  ${catkin_INCLUDE_DIRS}
)

add_executable(serial_write src/serial_write.cpp)
target_link_libraries(serial_write ${catkin_LIBRARIES})
add_dependencies(serial_write serial_node_generate_messages_cpp)


