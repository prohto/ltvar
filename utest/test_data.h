#ifndef TEST_DATA_H
#define TEST_DATA_H

#include "ltype.h"

#define STRINGIFY_(X) #X
#define STRINGIFY(X) STRINGIFY_(X)

#define TEST_VALUE_CONSTCHAR "anything"
#define TEST_VALUE_TEXT std::string("anything")
#define TEST_VALUE_BOOL_TRUE true
#define TEST_VALUE_BOOL_FALSE false
#define TEST_VALUE_DOUBLE 123.456
#define TEST_VALUE_INTEGER 123

Harmonix::LTypeHash test_hash = {
    std::make_pair("bool", Harmonix::LType(TEST_VALUE_BOOL_TRUE)),
    std::make_pair("double", Harmonix::LType(TEST_VALUE_DOUBLE)),
    std::make_pair("int", Harmonix::LType(TEST_VALUE_INTEGER)),
    std::make_pair("string", Harmonix::LType(TEST_VALUE_TEXT)),
    std::make_pair("void", Harmonix::LType()),
};

Harmonix::LTypeArray test_array = {
    Harmonix::LType(TEST_VALUE_BOOL_TRUE), Harmonix::LType(TEST_VALUE_DOUBLE),
    Harmonix::LType(TEST_VALUE_INTEGER), Harmonix::LType(TEST_VALUE_TEXT),
    Harmonix::LType()};

#endif  // TEST_DATA_H
