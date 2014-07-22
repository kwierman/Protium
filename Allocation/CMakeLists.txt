#Get together the sources
file(GLOB module_sources *.cxx)
file(GLOB module_headers *.h)

#Make the library
add_library(ProtiumAllocation SHARED ${module_sources} ${module_headers})
set_target_properties(ProtiumAllocation PROPERTIES LINKER_LANGUAGE CXX)
install(TARGETS ProtiumAllocation DESTINATION lib)

#Install Headers
install(FILES ${module_headers} DESTINATION include/Protium/Allocation)

