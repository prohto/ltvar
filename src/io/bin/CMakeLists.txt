set( IOBIN_LIB_SRCS
  ibin.cpp
  obin.cpp
)


set( IOBIN_LIB_HDRS
  ibin.h
  obin.h
)

add_library( iobin SHARED  ${IOBIN_LIB_SRCS} ${IOBIN_LIB_HDRS} )
set_target_properties( iobin PROPERTIES COMPILE_FLAGS "-I${CMAKE_HOME_DIRECTORY}/src")
set_target_properties( iobin PROPERTIES SOVERSION "${LIB_VERSION}" )
install( FILES ${IOBIN_LIB_HDRS} DESTINATION ${CMAKE_INSTALL_PREFIX}/include/ltvar )
install( TARGETS iobin DESTINATION ${CMAKE_INSTALL_PREFIX}/${CMAKE_INSTALL_LIBDIR} )
