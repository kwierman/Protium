# Kevin Wierman <kwierman@email.unc.edu>
#----------------------------------------------------------------------------
cmake_minimum_required(VERSION 2.6 FATAL_ERROR)
project(Protium)
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
add_subdirectory(Math)


#----------------------------------------------------------------------------
# Locate Executables, and link against all libraries
file(GLOB applications ${PROJECT_SOURCE_DIR}/Applications/*.cxx)
foreach(_app ${applications})
	get_filename_component (name_without_extension ${_app} NAME_WE)
	add_executable(${name_without_extension} ${_app} )
	target_link_libraries(${name_without_extension} ProtiumMath)
	install(TARGETS ${name_without_extension} DESTINATION bin)
endforeach()
#----------------------------------------------------------------------------
#Add in Documentation
#add_subdirectory(Documentation)
#----------------------------------------------------------------------------


# uninstall target
configure_file(
    "${CMAKE_CURRENT_SOURCE_DIR}/cmake_uninstall.cmake.in"
    "${CMAKE_CURRENT_BINARY_DIR}/cmake_uninstall.cmake"
    IMMEDIATE @ONLY)

add_custom_target(uninstall
    COMMAND ${CMAKE_COMMAND} -P ${CMAKE_CURRENT_BINARY_DIR}/cmake_uninstall.cmake)
