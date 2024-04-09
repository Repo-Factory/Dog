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

################ MODULES #################
include_directories(
  src/utility/udp_handler
  src/utility/warning
  src/utility/app_init
)
add_library(udp_handler src/utility/udp_handler/udp_handler.cpp)
add_library(warning     src/utility/warning/warning.cpp)
set(MODULES udp_handler warning)
################ MODULES #################

add_executable(walk src/components/walk.cpp)
target_link_libraries(walk ${EXTRA_LIBS} ${MODULES})

install(TARGETS
  walk
  DESTINATION bin/unitree)
install(DIRECTORY lib/cpp/${ARCH}/
  DESTINATION lib/unitree
  USE_SOURCE_PERMISSIONS)
