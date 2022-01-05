cmake_minimum_required(VERSION 2.8.3)
project(sm_lane_navigation)

## Find catkin macros and libraries
find_package(catkin REQUIRED smacc roscpp move_base_z_client_plugin multirole_sensor_client tf sr_all_events_go sr_event_countdown ros_timer_client sr_conditional ros_publisher_client actionlib actionlib_msgs angles)


add_action_files(
   DIRECTORY
   servers/navigation_action_server/action/
   
   FILES
   LEDControl.action
   NavigationControl.action
)


add_service_files(
  DIRECTORY
  servers/navigation_action_server/srv/

  FILES 
  AddTwoInts.srv
  RosLaunch.srv
)


generate_messages(
   DEPENDENCIES
   actionlib_msgs
 )


###################################
## catkin specific configuration ##
###################################
catkin_package()


###########
## Build ##
###########
set(CMAKE_CXX_STANDARD 14)
add_compile_options(-std=c++11) #workaround for ubuntu 16.04, to extinguish

## Specify additional locations of header files
## Your package locations should be listed before other locations
include_directories(
  include
  ${catkin_INCLUDE_DIRS}
)

## Declare a C++ executable
add_executable(${PROJECT_NAME}_node 
src/sm_lane_navigation_node.cpp
src/clients/cl_led/cl_led.cpp
src/clients/cl_navigation/cl_navigation.cpp
)


## Specify libraries to link a library or executable target against
target_link_libraries(${PROJECT_NAME}_node
  ${catkin_LIBRARIES}
)

## LED action server-----------------------------------------------------------------------------------------------------------------


add_executable(led_action_server_node_smdbsb_${PROJECT_NAME} servers/navigation_action_server/src/led_action_server_node.cpp)
set_target_properties(led_action_server_node_smdbsb_${PROJECT_NAME} PROPERTIES OUTPUT_NAME "led_action_server_node")

target_link_libraries(
  led_action_server_node_smdbsb_${PROJECT_NAME}
  ${catkin_LIBRARIES}
)

add_dependencies(led_action_server_node_smdbsb_${PROJECT_NAME} ${${PROJECT_NAME}_EXPORTED_TARGETS} ${catkin_EXPORTED_TARGETS} ${PROJECT_NAME}_generate_messages_cpp)

## Navigation action server-----------------------------------------------------------------------------------------------------------------

add_executable(navigation_action_server_node_smdbsb_${PROJECT_NAME} servers/navigation_action_server/src/navigation_action_server_node.cpp)
set_target_properties(navigation_action_server_node_smdbsb_${PROJECT_NAME} PROPERTIES OUTPUT_NAME "navigation_action_server_node")

target_link_libraries(
  navigation_action_server_node_smdbsb_${PROJECT_NAME}
  ${catkin_LIBRARIES}
)

add_dependencies(navigation_action_server_node_smdbsb_${PROJECT_NAME} ${${PROJECT_NAME}_EXPORTED_TARGETS} ${catkin_EXPORTED_TARGETS} ${PROJECT_NAME}_generate_messages_cpp)

## Add int server----------------------------------------------------------------------------------------------------------------------------
add_executable(add_two_ints_server_smdbsb_${PROJECT_NAME} servers/navigation_action_server/src/add_two_ints_server.cpp)
set_target_properties(add_two_ints_server_smdbsb_${PROJECT_NAME} PROPERTIES OUTPUT_NAME "add_two_ints_server")
target_link_libraries(add_two_ints_server_smdbsb_${PROJECT_NAME} ${catkin_LIBRARIES})
add_dependencies(add_two_ints_server_smdbsb_${PROJECT_NAME} ${PROJECT_NAME}_gencpp)

#############
## Install ##
#############

## Mark executables for installation
install(TARGETS ${PROJECT_NAME}_node
  RUNTIME DESTINATION ${CATKIN_PACKAGE_BIN_DESTINATION}
)

## Mark other files for installation (e.g. launch and config files, etc.)
install(FILES
  launch/sm_lane_navigation.launch
  DESTINATION ${CATKIN_PACKAGE_SHARE_DESTINATION}/launch
)

install(DIRECTORY
  config/
  DESTINATION ${CATKIN_PACKAGE_SHARE_DESTINATION}/config
)
