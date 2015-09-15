cmake_minimum_required(VERSION 2.6)

project(simsigdec)

include(CheckCXXCompilerFlag)
CHECK_CXX_COMPILER_FLAG("-std=c++11" COMPILER_SUPPORTS_CXX11)
CHECK_CXX_COMPILER_FLAG("-std=c++0x" COMPILER_SUPPORTS_CXX0X)

if(COMPILER_SUPPORTS_CXX11)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")
elseif(COMPILER_SUPPORTS_CXX0X)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++0x")
else()
    message(STATUS "The compiler ${CMAKE_CXX_COMPILER} has no C++11 support. Please use a different C++ compiler.")
endif()

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -m64 -pipe -O2 -Wall -W -D_REENTRANT -fPIE -DQT_NO_DEBUG -DQT_GUI_LIB -DQT_CORE_LIB")

include_directories(lib/gtest)
include_directories(lib/gtest/include)

set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_AUTOMOC ON)

find_package(Qt5Core)
find_package(Qt5Widgets)
find_package(Qt5Network)

include_directories(${Qt5Core_INCLUDE_DIRS})
include_directories(${Qt5Widgets_INCLUDE_DIRS})
include_directories(${Qt5Network_INCLUDE_DIRS})

add_library(gtest
    lib/gtest/src/gtest_main.cc 
    lib/gtest/src/gtest-all.cc)

include_directories(.)
add_subdirectory(core)
add_subdirectory(gui)
add_subdirectory(server)
add_subdirectory(core/tests)
