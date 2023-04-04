cmake_minimum_required(VERSION 3.16)
project(plazza)
set(CMAKE_CXX_STANDARD 20)

# set default build with debug mod
set(CMAKE_BUILD_TYPE Debug)
set(CMAKE_CXX_FLAGS_DEBUG   "$ENV{CXXFLAGS} -O0 -g -g3 -ggdb -Wall -W -std=c++2a")
set(CMAKE_CXX_FLAGS_RELEASE "$ENV{CXXFLAGS} -DNODEBUG -O3 -Wall")

# move EXECUTABSLE file to root dir of this project
set(EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR})

include_directories(inc)
include_directories(inc/Encapsulation)
include_directories(inc/Errors)
include_directories(inc/Orders)
include_directories(inc/Kitchen)
include_directories(inc/KitchenManager)
include_directories(inc/Reception)
include_directories(inc/Pizza)

add_subdirectory("src/")
get_directory_property(SOURCES DIRECTORY src DEFINITION SOURCES)

add_executable(plazza ${SOURCES})
TARGET_LINK_LIBRARIES(plazza PRIVATE pthread)