set( LTVAR_LIB_SRCS
  iterator.cpp
  ltvar.cpp
  tokenizer.cpp
)

set( LTVAR_LIB_HDRS
  iterator.h
  ltvar.h
  tokenizer.h
)

set( CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fPIC" )
include_directories( ${CMAKE_CURRENT_SOURCE_DIR} )

add_subdirectory( states )
add_subdirectory( io )

add_library( ltvar-obj OBJECT  ${LTVAR_LIB_SRCS} ${LTVAR_LIB_HDRS} )

add_library( ltvar-static STATIC  $<TARGET_OBJECTS:ltvar-obj> $<TARGET_OBJECTS:states> )
set_target_properties(ltvar-static PROPERTIES OUTPUT_NAME ltvar )

add_library( ltvar STATIC  $<TARGET_OBJECTS:ltvar-obj> $<TARGET_OBJECTS:states> )
set_target_properties( ltvar PROPERTIES SOVERSION "${LIB_VERSION}" )

install( FILES ltvar.h DESTINATION ${CMAKE_INSTALL_PREFIX}/include )
install( FILES iterator.h DESTINATION ${CMAKE_INSTALL_PREFIX}/include )

install( TARGETS ltvar ltvar-static DESTINATION ${CMAKE_INSTALL_PREFIX}/${CMAKE_INSTALL_LIBDIR} )
