cmake_minimum_required(VERSION 3.17)
project(geo1004.hw03)

add_executable(hw03 
  src/main.cpp
        )
set_target_properties(hw03 PROPERTIES 
  CXX_STANDARD 17
)
find_package(CGAL)
include(${CGAL_USE_FILE})

# Make the executable a default target to build & run in Visual Studio
set_property(DIRECTORY ${PROJECT_SOURCE_DIR} PROPERTY VS_STARTUP_PROJECT hw03)

