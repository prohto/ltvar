lcov --directory . --zerocounters
destinationdir=$1
shift
ctest $*
cd $destinationdir
lcov --directory .. --capture --output-file app.info
lcov --remove app.info '*utest*'  '*ThirdParty*' '/usr/*' '*/json_bison.cpp' '*/json_flex.cpp' --output-file  unitTest
genhtml --demangle-cpp unitTest
