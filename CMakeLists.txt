# Specify the minimum version for CMake
cmake_minimum_required(VERSION 2.8)

# Project's name
project(RO_Library)

# Specifing c++11 compiler
if (CMAKE_VERSION VERSION_LESS "3.1")
	if (CMAKE_CXX_COMPILER_ID STREQUAL "GNU")
		set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=gnu++11")
	endif ()
else ()
	set (CMAKE_CXX_STANDARD 11)
endif ()

# Set the output folder where your program will be created
set(CMAKE_BINARY_DIR ${CMAKE_SOURCE_DIR}/bin)
set(EXECUTABLE_OUTPUT_PATH ${CMAKE_BINARY_DIR})
set(LIBRARY_OUTPUT_PATH ${CMAKE_SOURCE_DIR}/lib)

#The file(GLOB...) allows for wildcard additions: So all files listed .cpp under src/ will be used to create an object file
file(GLOB SOURCES "src/*.cpp")

# Adding header file directories
include_directories(include)

# find and include CURL automatically
find_package(CURL REQUIRED)
include_directories(${CURL_INCLUDE_DIR})
 

###------------------------------------------------------###

#Generate a shared or static library from the source files
	add_library(GM_Handler SHARED ${SOURCES})

# Linking your executable to external libraries occurs here
	add_executable(gm ${SOURCES})
target_link_libraries(gm ${CURL_LIBRARIES} )
