cmake_minimum_required(VERSION 3.17)
project(geo1004.hw03)

add_executable(hw03 
  src/main.cpp
)
set_target_properties(hw03 PROPERTIES 
  CXX_STANDARD 17
)
target_link_libraries(hw03 PRIVATE
  CGAL::CGAL CGAL::CGAL_Core
)
find_package(CGAL QUIET COMPONENTS Core REQUIRED)
include(${CGAL_USE_FILE})
include_directories( ${CMAKE_SOURCE_DIR}/include/ )

# Make the executable a default target to build & run in Visual Studio
set_property(DIRECTORY ${PROJECT_SOURCE_DIR} PROPERTY VS_STARTUP_PROJECT hw03)

