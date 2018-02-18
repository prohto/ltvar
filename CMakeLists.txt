project(LType)
cmake_minimum_required(VERSION 2.8.11)

set( CMAKE_CXX_FLAGS "-std=c++14" )
set( CMAKE_CXX_FLAGS_DEBUG "-O0 -g -ggdb -std=c++14 -Wall" )
set( CMAKE_CXX_FLAGS_TESTING "-O0 -g -ggdb --coverage -Wall -std=c++14" )
set( CMAKE_CXX_LINKER_FLAGS_TESTING "--coverage" )

include( GNUInstallDirs )

add_subdirectory(src)
add_subdirectory(utest)

CONFIGURE_FILE("ltype.pc.in" "ltype.pc" @ONLY)
INSTALL( FILES ${CMAKE_CURRENT_BINARY_DIR}/ltype.pc DESTINATION ${CMAKE_INSTALL_PREFIX}/${CMAKE_INSTALL_LIBDIR}/pkgconfig )
