#ifndef TEST_DATA_H
#define TEST_DATA_H

#include "ltvar.h"

#define STRINGIFY_(X) #X
#define STRINGIFY(X) STRINGIFY_(X)

#define TEST_VALUE_CONSTCHAR "anything"
#define TEST_VALUE_TEXT std::string("anything")
#define TEST_VALUE_BOOL_TRUE true
#define TEST_VALUE_BOOL_FALSE false
#define TEST_VALUE_DOUBLE 123.456
#define TEST_VALUE_INTEGER 123

LTVarHash test_hash = {
    std::make_pair("bool", LTVar(TEST_VALUE_BOOL_TRUE)),
    std::make_pair("double", LTVar(TEST_VALUE_DOUBLE)),
    std::make_pair("int", LTVar(TEST_VALUE_INTEGER)),
    std::make_pair("string", LTVar(TEST_VALUE_TEXT)),
    std::make_pair("void", LTVar()),
};

LTVarArray test_array = {
    LTVar(TEST_VALUE_BOOL_TRUE), LTVar(TEST_VALUE_DOUBLE),
    LTVar(TEST_VALUE_INTEGER), LTVar(TEST_VALUE_TEXT),
    LTVar()};

#endif  // TEST_DATA_H
