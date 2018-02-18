set( LTYPE_LIB_SRCS
  iterator.cpp
  ltype.cpp
)

set( LTYPE_LIB_HDRS
  iterator.h
  ltype.h
)

set( CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fPIC" )
include_directories( ${CMAKE_CURRENT_SOURCE_DIR} )

add_subdirectory( states )
add_subdirectory( io )

add_library( ltype-static STATIC  ${LTYPE_LIB_SRCS} ${LTYPE_LIB_HDRS} $<TARGET_OBJECTS:states> $<TARGET_OBJECTS:iojson> $<TARGET_OBJECTS:iobin> )
set_target_properties(ltype-static PROPERTIES OUTPUT_NAME ltype )

add_library( ltype SHARED  ${LTYPE_LIB_SRCS} ${LTYPE_LIB_HDRS} $<TARGET_OBJECTS:states> $<TARGET_OBJECTS:iojson> $<TARGET_OBJECTS:iobin> )
set_target_properties(ltype PROPERTIES SOVERSION "0.1" )

install( FILES ltype.h DESTINATION ${CMAKE_INSTALL_PREFIX}/include )
install( FILES iterator.h DESTINATION ${CMAKE_INSTALL_PREFIX}/include/ltype )

INSTALL( TARGETS ltype ltype-static DESTINATION ${CMAKE_INSTALL_PREFIX}/${CMAKE_INSTALL_LIBDIR} )
