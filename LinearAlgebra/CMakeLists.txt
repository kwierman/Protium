#Get together the sources
file(GLOB module_sources *.cxx)
file(GLOB module_headers *.h)

#Make the library
add_library(ProtiumLinearAlgebra SHARED ${module_sources} ${module_headers})
install(TARGETS ProtiumLinearAlgebra DESTINATION lib)

#Install Headers
install(FILES ${module_headers} DESTINATION include/Protium/LinearAlgebra)

