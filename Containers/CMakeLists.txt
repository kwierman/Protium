#Get together the sources
file(GLOB module_sources *.cxx)
file(GLOB module_headers *.h)

#Make the library
add_library(ProtiumContainers SHARED ${module_sources} ${module_headers})
set_target_properties(ProtiumContainers PROPERTIES LINKER_LANGUAGE CXX )

install(TARGETS ProtiumContainers DESTINATION lib EXPORT ProtiumConfig)

#Install Headers
install(FILES ${module_headers} DESTINATION include/Protium/Collections)

