cmake_minimum_required(VERSION 2.8.3)
project(test)
find_package(catkin REQUIRED COMPONENTS roscpp std_msgs)
catkin_package(CATKIN_DEPENDS roscpp std_msgs)
include_directories(${catkin_INCLUDE_DIRS})
add_executable(test_node src/test_node.cpp)
target_link_libraries(test_node ${catkin_LIBRARIES})
