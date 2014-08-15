#Get together the sources
file(GLOB module_sources *.cxx)
file(GLOB module_headers *.h)

#Make the library
add_library(ProtiumLinearAlgebra SHARED ${module_sources} ${module_headers})
set_target_properties(ProtiumLinearAlgebra PROPERTIES LINKER_LANGUAGE CXX )
target_link_libraries(ProtiumLinearAlgebra ProtiumAllocation ProtiumThreads ProtiumSingleton)

install(TARGETS ProtiumLinearAlgebra DESTINATION lib EXPORT ProtiumConfig)

#Install Headers
install(FILES ${module_headers} DESTINATION include/Protium/LinearAlgebra)

