#include "gmock/gmock.h"
#include "gtest/gtest.h"

#include "io/json/ijson.h"
#include "ltype.h"
#include "test_data.h"
#include "utest.h"

#include <fstream>
#include <sstream>

using namespace Harmonix;

TEST(IJson, empty_array) {
  std::istringstream in_stream("[]");
  LType in_value;
  IJson ijson(in_value);
  in_stream >> ijson;
  ASSERT_EQ(LType::Type::kArray, in_value);
  ASSERT_EQ(0, in_value.size());
}

TEST(IJson, empty_array_spaces) {
  std::istringstream in_stream("[  \t ]");
  LType in_value;
  IJson ijson(in_value);
  in_stream >> ijson;
  ASSERT_EQ(LType::Type::kArray, in_value);
  ASSERT_EQ(0, in_value.size());
}

TEST(IJson, empty_array_lines) {
  std::istringstream in_stream("[\n\n   ]");
  LType in_value;
  IJson ijson(in_value);
  in_stream >> ijson;
  ASSERT_EQ(LType::Type::kArray, in_value);
  ASSERT_EQ(0, in_value.size());
}
TEST(IJson, fill_array) {
  std::istringstream in_stream("[true,  123.456,\t123,\n\"anything\",null,{}]");
  LType in_value;
  IJson ijson(in_value);
  in_stream >> ijson;
  ASSERT_EQ(LType::Type::kArray, in_value);
  ASSERT_EQ(6, in_value.size());
  ASSERT_EQ(LType::Type::kBool, in_value[0]);
  ASSERT_EQ(true, in_value[0]);
  ASSERT_EQ(LType::Type::kDouble, in_value[1]);
  ASSERT_EQ(123.456, in_value[1]);
  ASSERT_EQ(LType::Type::kInteger, in_value[2]);
  ASSERT_EQ(123, in_value[2]);
  ASSERT_EQ(LType::Type::kText, in_value[3]);
  ASSERT_EQ(std::string("anything"), in_value[3]);
  ASSERT_EQ(LType::Type::kVoid, in_value[4]);
  ASSERT_EQ(LType::Type::kHash, in_value[5]);
}

TEST(IJson, bool_true) {
  std::istringstream in_stream("true");
  LType in_value;
  IJson ijson(in_value);
  in_stream >> ijson;
  ASSERT_EQ(LType::Type::kBool, in_value);
  ASSERT_EQ(true, in_value);
}

TEST(IJson, bool_false) {
  std::istringstream in_stream("false");
  LType in_value;
  IJson ijson(in_value);
  in_stream >> ijson;
  ASSERT_EQ(LType::Type::kBool, in_value);
  ASSERT_EQ(false, in_value);
}

TEST(IJson, double) {
  std::istringstream in_stream("123.456");
  LType in_value;
  IJson ijson(in_value);
  in_stream >> ijson;
  ASSERT_EQ(LType::Type::kDouble, in_value);
  ASSERT_EQ(123.456, in_value);
}

TEST(IJson, empty_hash) {
  std::istringstream in_stream("{}");
  LType in_value;
  IJson ijson(in_value);
  in_stream >> ijson;
  ASSERT_EQ(LType::Type::kHash, in_value);
  ASSERT_EQ(0, in_value.size());
}

TEST(IJson, empty_hash_spaces) {
  std::istringstream in_stream("{  \t }");
  LType in_value;
  IJson ijson(in_value);
  in_stream >> ijson;
  ASSERT_EQ(LType::Type::kHash, in_value);
  ASSERT_EQ(0, in_value.size());
}

TEST(IJson, empty_hash_lines) {
  std::istringstream in_stream("{\n\n   }");
  LType in_value;
  IJson ijson(in_value);
  in_stream >> ijson;
  ASSERT_EQ(LType::Type::kHash, in_value);
  ASSERT_EQ(0, in_value.size());
}
TEST(IJson, fill_hash) {
  std::istringstream in_stream(
      "{bool:true,  double:  "
      "123.456,integer:\t123,\ntext:\"anything\",void:null,array:[]}");
  LType in_value;
  IJson ijson(in_value);
  in_stream >> ijson;
  ASSERT_EQ(LType::Type::kHash, in_value);
  ASSERT_EQ(6, in_value.size());
  ASSERT_EQ(LType::Type::kBool, in_value["bool"]);
  ASSERT_EQ(true, in_value["bool"]);
  ASSERT_EQ(LType::Type::kDouble, in_value["double"]);
  ASSERT_EQ(123.456, in_value["double"]);
  ASSERT_EQ(LType::Type::kInteger, in_value["integer"]);
  ASSERT_EQ(123, in_value["integer"]);
  ASSERT_EQ(LType::Type::kText, in_value["text"]);
  ASSERT_EQ(std::string("anything"), in_value["text"]);
  ASSERT_EQ(LType::Type::kVoid, in_value["void"]);
  ASSERT_EQ(LType::Type::kArray, in_value["array"]);
}

TEST(IJson, array_hash_nested) {
  std::istringstream in_stream("{array:[{void:null}]}");
  LType in_value;
  IJson ijson(in_value);
  in_stream >> ijson;
  ASSERT_EQ(LType::Type::kHash, in_value);
  ASSERT_EQ(LType::Type::kVoid, in_value["array"][0]["void"]);
}

TEST(IJson, integer) {
  std::istringstream in_stream("123");
  LType in_value;
  IJson ijson(in_value);
  in_stream >> ijson;
  ASSERT_EQ(LType::Type::kInteger, in_value);
  ASSERT_EQ(123, in_value);
}

TEST(IJson, text) {
  std::istringstream in_stream("\"anything\"");
  LType in_value;
  IJson ijson(in_value);
  in_stream >> ijson;
  ASSERT_EQ(LType::Type::kText, in_value);
  ASSERT_EQ(std::string("anything"), in_value);
}

TEST(IJson, escaped_text) {
  std::istringstream in_stream(
      "\"123\\t456\\\\78\\u90EF\\\"\\\\\\/\\b\\f\\n\\r\\t\"");
  LType in_value;
  IJson ijson(in_value);
  in_stream >> ijson;
  ASSERT_EQ(LType::Type::kText, in_value);
  ASSERT_EQ(std::string("123\t456\\78\\u90EF\"\\/\b\f\n\r\t"), in_value);
}

TEST(IJson, void) {
  std::istringstream in_stream("null");
  LType in_value;
  IJson ijson(in_value);
  in_stream >> ijson;
  ASSERT_EQ(LType::Type::kVoid, in_value);
}

TEST(IJson, exception) {
  std::istringstream in_stream("{\n\"name\": 10\n\"lastname\": 20\n}");
  LType in_value;
  IJson ijson(in_value);
  ASSERT_THROW(in_stream >> ijson, std::invalid_argument);
  ASSERT_EQ(3, ijson.getLinesRead());
}

TEST(IJson, empty_json) {
  std::istringstream in_stream("");
  LType in_value;
  IJson ijson(in_value);
  ASSERT_THROW(in_stream >> ijson, std::invalid_argument);
  ASSERT_EQ(0, ijson.getLinesRead());
}
