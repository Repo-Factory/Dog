cmake_minimum_required(VERSION 2.8.3)
project(dice_go)

add_compile_options(-std=c++14)
message("-- CMAKE_SYSTEM_PROCESSOR: ${CMAKE_SYSTEM_PROCESSOR}")
if("${CMAKE_SYSTEM_PROCESSOR}" MATCHES "x86_64.*")
set(ARCH amd64)
endif()
if("${CMAKE_SYSTEM_PROCESSOR}" MATCHES "aarch64.*")
set(ARCH arm64)
endif()

include_directories(hdr)
link_directories(lib/cpp/${ARCH})
set(EXTRA_LIBS -pthread libunitree_legged_sdk.so)
set(CMAKE_CXX_FLAGS "-O3 -fPIC")

add_executable(walk src/components/walk.cpp)
target_link_libraries(walk ${EXTRA_LIBS})

install(TARGETS
  walk
  DESTINATION bin/unitree)
install(DIRECTORY lib/cpp/${ARCH}/
  DESTINATION lib/unitree
  USE_SOURCE_PERMISSIONS)
