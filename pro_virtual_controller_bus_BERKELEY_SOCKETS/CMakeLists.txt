cmake_minimum_required (VERSION 2.6)

project (pro_virtual_controller_bus_BERKELEY_SOCKETS)
include (CTest)
include (CheckFunctionExists)

# The version number
set (Tutorial_VERSION_MAJOR 1)
set (Tutorial_VERSION_MINOR 0)

include_directories("${PROJECT_BINARY_DIR}" "../mod_unified_sockets_BERKELEY_SOCKETS" "../mod_queue/")

add_executable (${CMAKE_PROJECT_NAME} ${CMAKE_PROJECT_NAME}.c)
target_link_libraries (${CMAKE_PROJECT_NAME} 


