cmake_minimum_required(VERSION 2.8)
project( object_tracking )
find_package( OpenCV REQUIRED )
include_directories( ${OpenCV_INCLUDE_DIRS} )
add_executable( out track.cpp )
target_link_libraries( out ${OpenCV_LIBS})

# Locate libraries and headers
find_package(WiringPi REQUIRED)
find_package(Threads REQUIRED) 

# Include headers
include_directories(${WIRINGPI_INCLUDE_DIRS}) 

# Link against libraries
target_link_libraries(out ${WIRINGPI_LIBRARIES}) 
target_link_libraries(out ${CMAKE_THREAD_LIBS_INIT}) 
