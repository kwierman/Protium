# Kevin Wierman <kwierman@email.unc.edu>
#----------------------------------------------------------------------------
cmake_minimum_required(VERSION 2.6 FATAL_ERROR)
project(Protium)
set(Protium_MAJOR_VERSION 0)
set(Protium_MINOR_VERSION 1)
set(Protium_PATCH_VERSION 0)
set(Protium_VERSION
  ${Protium_MAJOR_VERSION}.${Protium_MINOR_VERSION}.${Protium_PATCH_VERSION})

set(INSTALL_LIB_DIR lib CACHE PATH "Installation directory for libraries")
set(INSTALL_BIN_DIR bin CACHE PATH "Installation directory for executables")
set(INSTALL_INCLUDE_DIR include CACHE PATH "Installation directory for header files")
set(INSTALL_CMAKE_DIR ${DEF_INSTALL_CMAKE_DIR} CACHE PATH "Installation directory for CMake files")
#----------------------------------------------------------------------------
if(${CMAKE_SOURCE_DIR} STREQUAL ${CMAKE_BINARY_DIR})
    message(STATUS ${PROJECT_NAME} " requires an out-of-source build.")
    message(STATUS "Please remove these files from ${CMAKE_BINARY_DIR} first:")
    message(STATUS "CMakeCache.txt")
    message(STATUS "CMakeFiles")
    message(STATUS "Once these files are removed, create a separate directory")
    message(STATUS "and run CMake from there")
    message(FATAL_ERROR "in-source build detected")
endif()
#----------------------------------------------------------------------------
if(CMAKE_INSTALL_PREFIX_INITIALIZED_TO_DEFAULT)
    set(CMAKE_INSTALL_PREFIX "${CMAKE_BINARY_DIR}/install" CACHE PATH "Install path prefix, prepended onto install directories." FORCE)
endif()
#----------------------------------------------------------------------------
# Locate sources and headers for this project
include_directories(${PROJECT_SOURCE_DIR}/..)
add_subdirectory(Design)
add_subdirectory(Threads)
add_subdirectory(Singleton)
add_subdirectory(Allocation)
add_subdirectory(Time)
add_subdirectory(Utilities)
add_subdirectory(Math)
add_subdirectory(LinearAlgebra)
add_subdirectory(Containers)
add_subdirectory(Applications)
###############THIS ONE ALWAYS COMES LAST################
add_subdirectory(Include)
#----------------------------------------------------------------------------
#Add in Documentation
add_subdirectory(Documentation)
#----------------------------------------------------------------------------
# uninstall target
configure_file(
    "${CMAKE_CURRENT_SOURCE_DIR}/cmake_uninstall.cmake.in"
    "${CMAKE_CURRENT_BINARY_DIR}/cmake_uninstall.cmake"
    IMMEDIATE @ONLY)

add_custom_target(uninstall 
    COMMAND ${CMAKE_COMMAND} -P ${CMAKE_CURRENT_BINARY_DIR}/cmake_uninstall.cmake)
#----------------------------------------------------------------------------
#Export everything just made
install(EXPORT ProtiumConfig DESTINATION lib/Protium)