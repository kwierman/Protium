#Get together the sources
file(GLOB module_sources *.cc)
file(GLOB module_headers *.hh)

#Install Headers
install(FILES ${module_headers} DESTINATION include)

