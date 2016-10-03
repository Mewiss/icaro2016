cmake_minimum_required(VERSION 2.8)
project( test )

set(raspicam_DIR "/usr/local/lib/cmake" )

find_package( raspicam REQUIRED )
find_package( OpenCV )
find_package( WiringPi REQUIRED )
find_package( Threads REQUIRED )

include_directories(${WIRINGPI_INCLUDE_DIRS})

IF (OpenCV_FOUND AND raspicam_CV_FOUND)
MESSAGE(STATUS "COMPILING OPENCV TESTS")
add_executable( sensor test.cpp )
target_link_libraries( sensor ${raspicam_CV_LIBS} )
target_link_libraries( sensor ${WIRINGPI_LIBRARIES} )
target_link_libraries( sensor ${CMAKE_THREAD_LIBS_INIT} )
ELSE()
MESSAGE(FATAL_ERROR "OPENCV NOT FOUND IN YOUT SYSTEM")
ENDIF()
