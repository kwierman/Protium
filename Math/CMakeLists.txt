#Get together the sources
file(GLOB module_sources *.cxx)
file(GLOB module_headers *.h)

#Make the library
add_library(ProtiumMath SHARED ${module_sources} ${module_headers})
install(TARGETS ProtiumMath DESTINATION lib)

#Install Headers
install(FILES ${module_headers} DESTINATION include/Protium/Math)

