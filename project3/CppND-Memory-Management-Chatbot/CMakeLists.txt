cmake_minimum_required(VERSION 3.11.3)

set(CMAKE_CXX_STANDARD 17)

# Set the build type to Debug if not already set
if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE Debug CACHE STRING "Choose the type of build (Debug, Release, RelWithDebInfo, MinSizeRel)" FORCE)
endif()

# Add debugging flags for all configurations
set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -g")

project(Membot)

find_package(wxWidgets REQUIRED COMPONENTS core base)
include(${wxWidgets_USE_FILE})

file(GLOB project_SRCS src/*.cpp)

add_executable(membot ${project_SRCS})
target_link_libraries(membot ${wxWidgets_LIBRARIES})
target_include_directories(membot PRIVATE ${wxWidgets_INCLUDE_DIRS})
