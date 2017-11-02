cmake_minimum_required(VERSION 2.6)
project(ENGINE)

include_directories(sdl/include)
link_directories(${CMAKE_SOURCE_DIR}/sdl/lib)

add_executable(retain
  main.cpp
)

target_link_libraries(retain SDL)