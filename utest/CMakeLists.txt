function(add_gtest test_name test_link_lib )
  add_executable(${test_name} ${test_name}.cpp)
  target_include_directories(${test_name} PRIVATE ${GTEST_INCLUDE_DIRS})
  target_link_libraries(${test_name} ${test_link_lib} ${GTEST_BOTH_LIBRARIES} gmock pthread gcov )
  
  GTEST_ADD_TESTS(${test_name} "${test_name}" ${test_name}.cpp)
endfunction()

if( CMAKE_BUILD_TYPE STREQUAL "Testing" OR CMAKE_BUILD_TYPE STREQUAL "Debug" )
  cmake_policy( SET CMP0057 NEW )
  find_package(GTest REQUIRED)
  include_directories(${GTEST_INCLUDE_DIRS})

  include(CTest)
  enable_testing()
  set( CMAKE_CXX_FLAGS_TESTING "-g -ggdb -gcov -Wall" PARENT_SCOPE )
  add_custom_target( coverage ${CMAKE_CURRENT_SOURCE_DIR}/dolcov.sh . )
  add_custom_target( utest ctest WORKING_DIRECTORY ${CMAKE_BINARY_DIR}/utest )

  include_directories( ${CMAKE_HOME_DIRECTORY}/src )
  include_directories( ${CMAKE_CURRENT_SOURCE_DIR} )
  add_subdirectory( states )
  add_subdirectory( io )
	
  add_gtest( test_ltvar "ltvar" )
endif()

