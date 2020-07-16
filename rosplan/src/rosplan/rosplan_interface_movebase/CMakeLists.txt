cmake_minimum_required(VERSION 2.8.3)
project(rosplan_interface_movebase)

add_compile_options(-std=c++11)

## Find catkin macros and libraries
find_package(catkin REQUIRED COMPONENTS
  roscpp
  rospy
  std_msgs
  std_srvs
  diagnostic_msgs
  geometry_msgs
  move_base_msgs
  rosplan_dispatch_msgs
  rosplan_knowledge_msgs
  rosplan_planning_system
  actionlib
  mongodb_store
)

find_package(Boost REQUIRED COMPONENTS
  filesystem
)

add_definitions(-Wno-deprecated-declarations) # Disable deprecated declarations warning (about std::auto_ptr)


###################################
## catkin specific configuration ##
###################################

## Declare things to be passed to dependent projects
catkin_package(
  LIBRARIES ${PROJECT_NAME}
  CATKIN_DEPENDS roscpp rospy std_msgs std_srvs actionlib rosplan_dispatch_msgs rosplan_knowledge_msgs mongodb_store diagnostic_msgs rosplan_planning_system
  DEPENDS
)

###########
## Build ##
###########

## include_directories(include)
include_directories(
  ${catkin_INCLUDE_DIRS}
  include
)

## Declare cpp executables
add_executable(rpmovebase src/RPMoveBase.cpp)
add_dependencies(rpmovebase ${catkin_EXPORTED_TARGETS})

## Specify libraries against which to link a library or executable target
target_link_libraries(rpmovebase ${catkin_LIBRARIES} ${Boost_LIBRARIES})


add_executable(rpmovebasedetect src/RPMoveBaseDetect.cpp)
add_dependencies(rpmovebasedetect ${catkin_EXPORTED_TARGETS})
target_link_libraries(rpmovebasedetect ${catkin_LIBRARIES} ${Boost_LIBRARIES})



add_executable(rpgotocheckpoint src/RPGotoCheckpoint.cpp)
add_dependencies(rpgotocheckpoint ${catkin_EXPORTED_TARGETS})
target_link_libraries(rpgotocheckpoint ${catkin_LIBRARIES} ${Boost_LIBRARIES})





add_executable(rp_goto src/goto.cpp)
add_dependencies(rp_goto ${catkin_EXPORTED_TARGETS})
target_link_libraries(rp_goto ${catkin_LIBRARIES} ${Boost_LIBRARIES})


add_executable(rp_enterev src/enterev.cpp)
add_dependencies(rp_enterev ${catkin_EXPORTED_TARGETS})
target_link_libraries(rp_enterev ${catkin_LIBRARIES} ${Boost_LIBRARIES})


add_executable(rp_leaveev src/leaveev.cpp)
add_dependencies(rp_leaveev ${catkin_EXPORTED_TARGETS})
target_link_libraries(rp_leaveev ${catkin_LIBRARIES} ${Boost_LIBRARIES})


add_executable(rp_movefloor src/movefloor.cpp)
add_dependencies(rp_movefloor ${catkin_EXPORTED_TARGETS})
target_link_libraries(rp_movefloor ${catkin_LIBRARIES} ${Boost_LIBRARIES})


#############
## Install ##
#############

install(TARGETS rpmovebase
  ARCHIVE DESTINATION ${CATKIN_PACKAGE_LIB_DESTINATION}
  LIBRARY DESTINATION ${CATKIN_PACKAGE_LIB_DESTINATION}
  RUNTIME DESTINATION ${CATKIN_PACKAGE_BIN_DESTINATION}
)
