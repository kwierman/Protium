#Get together the sources
file(GLOB module_sources *.cxx)
file(GLOB module_headers *.h)

#Make the library
add_library(ProtiumUtilities SHARED ${module_sources} ${module_headers})
target_link_libraries(ProtiumUtilities  ProtiumSingleton)
set_target_properties(ProtiumUtilities PROPERTIES LINKER_LANGUAGE CXX)
install(TARGETS ProtiumUtilities DESTINATION lib)

#Install Headers
install(FILES ${module_headers} DESTINATION include/Protium/Allocation)

