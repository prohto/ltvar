set( LTVAR_LIB_SRCS
  iterator.cpp
  ltvar.cpp
)

set( LTVAR_LIB_HDRS
  iterator.h
  ltvar.h
)

set( CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fPIC" )
include_directories( ${CMAKE_CURRENT_SOURCE_DIR} )

add_subdirectory( states )
add_subdirectory( io )

add_library( ltvar-static STATIC  ${LTVAR_LIB_SRCS} ${LTVAR_LIB_HDRS} $<TARGET_OBJECTS:states> $<TARGET_OBJECTS:iojson> $<TARGET_OBJECTS:iobin> )
set_target_properties(ltvar-static PROPERTIES OUTPUT_NAME ltvar )

add_library( ltvar SHARED  ${LTVAR_LIB_SRCS} ${LTVAR_LIB_HDRS} $<TARGET_OBJECTS:states> $<TARGET_OBJECTS:iojson> $<TARGET_OBJECTS:iobin> )
set_target_properties(ltvar PROPERTIES SOVERSION "0.1" )

install( FILES ltvar.h DESTINATION ${CMAKE_INSTALL_PREFIX}/include )
install( FILES iterator.h DESTINATION ${CMAKE_INSTALL_PREFIX}/include/ltvar )

INSTALL( TARGETS ltvar ltvar-static DESTINATION ${CMAKE_INSTALL_PREFIX}/${CMAKE_INSTALL_LIBDIR} )
