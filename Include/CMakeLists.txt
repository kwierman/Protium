#Get together the sources
file(GLOB module_sources *.cxx)
file(GLOB module_headers *.h)

#Install Headers
install(FILES ${module_headers} DESTINATION include)

