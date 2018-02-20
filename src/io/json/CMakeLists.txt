find_package( FLEX )
find_package( BISON )

if( FLEX_FOUND AND BISON_FOUND )
  add_custom_command( OUTPUT json_bison.cpp json_bison.hpp
      COMMAND bison --report=all -p json_ -d -o json_bison.cpp ${CMAKE_CURRENT_SOURCE_DIR}/json.y
      DEPENDS json.y )
  
  add_custom_command( OUTPUT json_flex.cpp
      COMMAND flex -R -P json_ -d -o json_flex.cpp ${CMAKE_CURRENT_SOURCE_DIR}/json.l
      DEPENDS json.l )
  
  set( IOJSON_LIB_SRCS
    ijson.cpp
    ojson.cpp
    ${CMAKE_CURRENT_BINARY_DIR}/json_bison.cpp
    ${CMAKE_CURRENT_BINARY_DIR}/json_flex.cpp
  )
  
  
  set( IOJSON_LIB_HDRS
    ijson.h
    ojson.h
    json.h
    ${CMAKE_CURRENT_BINARY_DIR}/json_bison.hpp
  )
  
  include_directories( ${CMAKE_CURRENT_SOURCE_DIR} )
  add_library( iojson OBJECT  ${IOJSON_LIB_SRCS} ${IOJSON_LIB_HDRS} json.y json.l )
  set_target_properties( iojson PROPERTIES COMPILE_FLAGS "-I${CMAKE_HOME_DIRECTORY}/src")
	install( FILES ${IOJSON_LIB_HDRS} DESTINATION ${CMAKE_INSTALL_PREFIX}/include/ltvar )
ENDIF()
