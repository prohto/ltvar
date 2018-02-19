#include "gmock/gmock.h"
#include "gtest/gtest.h"

#include "io/json/ojson.h"
#include "ltvar.h"
#include "test_data.h"
#include "utest.h"

#include <fstream>
#include <sstream>


LTVarArray empty_array;
LTVarHash empty_hash;

LTVarHash test_hash_nested = {
    std::make_pair("bool", LTVar(TEST_VALUE_BOOL_TRUE)),
    std::make_pair("double", LTVar(TEST_VALUE_DOUBLE)),
};

LTVarHash test_hash_local = {
    std::make_pair("bool", LTVar(TEST_VALUE_BOOL_TRUE)),
    std::make_pair("double", LTVar(TEST_VALUE_DOUBLE)),
    std::make_pair("int", LTVar(TEST_VALUE_INTEGER)),
    std::make_pair("string", LTVar(TEST_VALUE_TEXT)),
    std::make_pair("void", LTVar()),
    std::make_pair("array", LTVar(test_array)),
    std::make_pair("hash", LTVar(test_hash_nested))};

TEST(OJson, empty_array) {
  std::ostringstream og_stream;
  LTVar og_value(LTVar::Type::kArray);
  OJson ojson(og_value);
  og_stream << ojson;
  ASSERT_EQ(og_stream.str(), "[]");
}

TEST(OJson, fill_array) {
  std::ostringstream og_stream;
  LTVar og_value(test_array);
  OJson ojson(og_value);
  og_stream << ojson;
  ASSERT_EQ("[true,123.456,123,\"anything\",null]", og_stream.str());
}

TEST(OJson, bool_true) {
  std::ostringstream og_stream;
  LTVar og_value(TEST_VALUE_BOOL_TRUE);
  OJson ojson(og_value);
  og_stream << ojson;
  ASSERT_EQ("true", og_stream.str());
}

TEST(OJson, bool_false) {
  std::ostringstream og_stream;
  LTVar og_value(TEST_VALUE_BOOL_FALSE);
  OJson ojson(og_value);
  og_stream << ojson;
  ASSERT_EQ("false", og_stream.str());
}

TEST(OJson, double) {
  std::ostringstream og_stream;
  LTVar og_value(TEST_VALUE_DOUBLE);
  OJson ojson(og_value);
  og_stream << ojson;
  ASSERT_EQ("123.456", og_stream.str());
}

TEST(OJson, empty_hash) {
  std::ostringstream og_stream;
  LTVar og_value(LTVar::Type::kHash);
  OJson ojson(og_value);
  og_stream << ojson;
  ASSERT_EQ(og_stream.str(), "{}");
}

TEST(OJson, fill_hash) {
  std::ostringstream og_stream;
  LTVar og_value(test_hash_local);
  OJson ojson(og_value);
  og_stream << ojson;
  ASSERT_EQ(
      og_stream.str(),
      "{\"array\":[true,123.456,123,\"anything\",null],\"bool\":true,"
      "\"double\":123."
      "456,\"hash\":{\"bool\":true,\"double\":123.456},\"int\":123,\"string\":"
      "\"anything\",\"void\":null}");
}

////  ASSERT_EQ(
////      "{\n"
////      "  \"array\": [\n"
////      "    true,\n"
////      "    123.456,\n"
////      "    123,\n"
////      "    \"anything\",\n"
////      "    null\n"
////      "  ],\n"
////      "  \"bool\": true,\n"
////      "  \"double\": 123.456,\n"
////      "  \"hash\": {\n"
////      "    \"bool\": true,\n"
////      "    \"double\": 123.456\n"
////      "  },\n"
////      "  \"int\": 123,\n"
////      "  \"string\": \"anything\",\n"
////      "  \"void\": null\n"
////      "}",

TEST(OJson, integer) {
  std::ostringstream og_stream;
  LTVar og_value(TEST_VALUE_INTEGER);
  OJson ojson(og_value);
  og_stream << ojson;
  ASSERT_EQ("123", og_stream.str());
}

TEST(OJson, text) {
  std::ostringstream og_stream;
  LTVar og_value(TEST_VALUE_TEXT);
  OJson ojson(og_value);
  og_stream << ojson;
  ASSERT_EQ("\"anything\"", og_stream.str());
}

TEST(OJson, escaped_text) {
  std::ostringstream og_stream;
  LTVar og_value("123\t456\\78\\u90EF\"\\/\b\f\n\r\t");
  OJson ojson(og_value);
  og_stream << ojson;
  ASSERT_EQ("\"123\\t456\\\\78\\u90EF\\\"\\\\\\/\\b\\f\\n\\r\\t\"",
            og_stream.str());
}

TEST(OJson, void) {
  std::ostringstream og_stream;
  LTVar og_value;
  OJson ojson(og_value);
  og_stream << ojson;
  ASSERT_EQ("null", og_stream.str());
}
