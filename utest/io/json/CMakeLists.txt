find_package( FLEX )
find_package( BISON )

if( FLEX_FOUND AND BISON_FOUND )
    add_gtest( test_ijson "ltype" )
    add_gtest( test_ojson "ltype" )
endif()
