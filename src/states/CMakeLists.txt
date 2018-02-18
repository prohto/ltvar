set( STATES_LIB_SRCS
  array.cpp
  bool.cpp
  double.cpp
  hash.cpp
  integer.cpp
  string.cpp
  void.cpp
)


set( STATES_LIB_HDRS
  array.h
  bool.h
  double.h
  hash.h
  integer.h
  string.h
  void.h
)

add_library( states OBJECT  ${STATES_LIB_SRCS} ${STATES_LIB_HDRS} )
install( FILES ${STATES_LIB_HDRS} DESTINATION ${CMAKE_INSTALL_PREFIX}/include/ltype )
