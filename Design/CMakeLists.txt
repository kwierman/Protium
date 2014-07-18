#Get together the sources
file(GLOB module_sources *.cxx)
file(GLOB module_headers *.h)

#Make the library
add_library(ProtiumDesign SHARED ${module_sources} ${module_headers})
set_target_properties(ProtiumDesign PROPERTIES LINKER_LANGUAGE CXX)
install(TARGETS ProtiumDesign DESTINATION lib)

#Install Headers
install(FILES ${module_headers} DESTINATION include/Protium/Design)

