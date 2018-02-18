set( IOBIN_LIB_SRCS
  ibin.cpp
  obin.cpp
)


set( IOBIN_LIB_HDRS
  ibin.h
  obin.h
)

add_library( iobin OBJECT  ${IOBIN_LIB_SRCS} ${IOBIN_LIB_HDRS} )
set_target_properties( iobin PROPERTIES COMPILE_FLAGS "-I${CMAKE_HOME_DIRECTORY}/src")
install( FILES ${IOBIN_LIB_HDRS} DESTINATION ${CMAKE_INSTALL_PREFIX}/include/ltype )
