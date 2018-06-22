find_package( FLEX )
find_package( BISON )

#if( FLEX_FOUND AND BISON_FOUND )
if( TARGET iojson )
    add_gtest( test_ijson "ltvar;iojson" )
    add_gtest( test_ojson "ltvar;iojson" )
endif()
