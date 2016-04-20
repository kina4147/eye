cmake_minimum_required(VERSION 2.8.3)
project(eye)

find_package(catkin REQUIRED COMPONENTS
	  roscpp
	  std_msgs
	  message_generation
	  sensor_msgs
	  cv_bridge
	  image_transport
)

add_message_files(
   FILES
)


 generate_messages(
  	DEPENDENCIES
  	std_msgs
	sensor_msgs
 )



link_directories(
	${OpenCV_LIBRARIES}
)

catkin_package(
  INCLUDE_DIRS include 
  CATKIN_DEPENDS roscpp std_msgs image_transport
)

include_directories(
	include
	see/include
	glass/include
 	${catkin_INCLUDE_DIRS}
	${OpenCV_INCLUDE_DIRS}
)

# glass
add_executable(glass 
	glass/src/glass_node.cpp
	glass/src/calibration.cpp glass/include/calibration.hpp	
)
target_link_libraries(glass
   ${catkin_LIBRARIES}
   ${OpenCV_LIBRARIES} 
)

# see
add_executable(see 
	see/src/see_node.cpp
	see/src/camera.cpp see/include/camera.hpp	
)
target_link_libraries(see
   ${catkin_LIBRARIES}
   ${OpenCV_LIBRARIES} 
)

set(CMAKE_BUILD_TYPE Release)
