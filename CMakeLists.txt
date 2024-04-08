cmake_minimum_required(VERSION 2.8.3)
project(dice_go)

include_directories(include)

add_compile_options(-std=c++14)

# check arch and os
message("-- CMAKE_SYSTEM_PROCESSOR: ${CMAKE_SYSTEM_PROCESSOR}")
if("${CMAKE_SYSTEM_PROCESSOR}" MATCHES "x86_64.*")
  set(ARCH amd64)
endif()
if("${CMAKE_SYSTEM_PROCESSOR}" MATCHES "aarch64.*")
  set(ARCH arm64)
endif()

link_directories(lib/cpp/${ARCH})
set(EXTRA_LIBS -pthread libunitree_legged_sdk.so)

set(CMAKE_CXX_FLAGS "-O3 -fPIC")

add_executable(walk_service src/walk_service.cpp)
target_link_libraries(walk_service ${EXTRA_LIBS})

# install
install(TARGETS
  example_position example_velocity example_torque example_walk example_joystick
  DESTINATION bin/unitree)
install(DIRECTORY lib/cpp/${ARCH}/
  DESTINATION lib/unitree
  USE_SOURCE_PERMISSIONS)
