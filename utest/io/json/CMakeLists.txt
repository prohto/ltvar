find_package( FLEX )
find_package( BISON )

if( FLEX_FOUND AND BISON_FOUND )
    add_gtest( test_ijson "ltvar" )
    add_gtest( test_ojson "ltvar" )
endif()
