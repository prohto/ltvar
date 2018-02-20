include_directories( ${CMAKE_CURRENT_SOURCE_DIR} )
add_subdirectory( bin )
add_subdirectory( json )
INSTALL( FILES encoder.h decoder.h DESTINATION ${CMAKE_INSTALL_PREFIX}/include/ltvar/io )

