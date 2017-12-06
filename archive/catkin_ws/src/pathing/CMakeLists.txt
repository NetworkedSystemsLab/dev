cmake_minimum_required(VERSION 2.8.3)
project(pathing)

find_package(catkin REQUIRED COMPONENTS
  roscpp
  rospy
  nav_msgs
  serial_node
  message_generation
)


catkin_package(
  CATKIN_DEPENDS message_runtime
)


include_directories(
  ${catkin_INCLUDE_DIRS}
)

add_executable(pathing src/pathing.cpp)
target_link_libraries(pathing ${catkin_LIBRARIES})
add_dependencies(pathing serial_node_generate_messages_cpp)


