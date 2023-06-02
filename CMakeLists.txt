cmake_minimum_required(VERSION 2.8 FATAL_ERROR)

project(join_pcd)

add_compile_options(-std=c++14)

find_package(PCL 1.2 REQUIRED)

set(HEADERS
  ${CMAKE_CURRENT_SOURCE_DIR}/include/file_controller.h
  ${CMAKE_CURRENT_SOURCE_DIR}/include/merge_pcd.h
)

set(SOURCES
  ${CMAKE_CURRENT_SOURCE_DIR}/src/file_controller.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/src/merge_pcd.cpp
)


add_library(sub_join ${HEADERS} ${SOURCES})

include_directories(include ${PCL_INCLUDE_DIRS})
link_directories(${PCL_LIBRARY_DIRS})
add_definitions(${PCL_DEFINITIONS})

add_executable (join_pcd src/join_pcd.cpp ${SOURCES} ${HEADERS})
target_link_libraries (join_pcd ${PCL_LIBRARIES})
