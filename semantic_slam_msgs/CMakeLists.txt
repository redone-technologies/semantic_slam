cmake_minimum_required(VERSION 2.8.3)
project(semantic_slam_msgs)

## Find catkin macros and libraries
find_package(catkin REQUIRED COMPONENTS
  diagnostic_msgs
  genmsg
  geometry_msgs
  message_generation
  roscpp
  rospy
  std_msgs
  message_runtime
  actionlib_msgs
)

# Generate messages in the 'msg' folder
add_message_files(
  FILES
  object.msg
  objects.msg
#   position.msg
  place.msg
  places.msg
  door.msg
  doors.msg
)

## Generate services in the 'srv' folder
# add_service_files(
#   FILES
#   Service1.srv
#   Service2.srv
# )

# Generate actions in the 'action' folder
add_action_files(
  FILES
  goto_checkpoint.action
  goto.action
  elevator.action
)

## Generate added messages and services with any dependencies listed here
generate_messages(
  DEPENDENCIES
  geometry_msgs
  diagnostic_msgs
  std_msgs
  actionlib_msgs
)

################################################
## Declare ROS dynamic reconfigure parameters ##
################################################

## To declare and build dynamic reconfigure parameters within this
## package, follow these steps:
## * In the file package.xml:
##   * add a build_depend and a exec_depend tag for "dynamic_reconfigure"
## * In this file (CMakeLists.txt):
##   * add "dynamic_reconfigure" to
##     find_package(catkin REQUIRED COMPONENTS ...)
##   * uncomment the "generate_dynamic_reconfigure_options" section below
##     and list every .cfg file to be processed



catkin_package(
  CATKIN_DEPENDS message_generation message_runtime diagnostic_msgs geometry_msgs roscpp rospy std_msgs genmsg actionlib_msgs
)

###########
## Build ##
###########

include_directories(
  ${catkin_INCLUDE_DIRS}
)