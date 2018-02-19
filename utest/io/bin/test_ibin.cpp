#include "gmock/gmock.h"
#include "gtest/gtest.h"

#include "io/bin/ibin.h"
#include "test_iodata.h"
#include "utest.h"


TEST(IBin, len87) {
  std::istringstream og_stream(IOBinData::len87());
  size_t len = 0;
  IBin::decode(og_stream, len);
  ASSERT_EQ(87, len);
}

TEST(IBin, len128) {
  std::istringstream og_stream(IOBinData::len128());
  size_t len = 0;
  IBin::decode(og_stream, len);
  ASSERT_EQ(128, len);
}

TEST(IBin, len4000) {
  std::istringstream og_stream(IOBinData::len4000());
  size_t len = 0;
  IBin::decode(og_stream, len);
  ASSERT_EQ(4000, len);
}

TEST(IBin, len32159) {
  std::istringstream og_stream(IOBinData::len32159());
  size_t len = 0;
  IBin::decode(og_stream, len);
  ASSERT_EQ(32159, len);
}

TEST(IBin, len65433) {
  std::istringstream og_stream(IOBinData::len65433());
  size_t len = 0;
  IBin::decode(og_stream, len);
  ASSERT_EQ(65433, len);
}

TEST(IBin, len65535) {
  std::istringstream og_stream(IOBinData::len65535());
  size_t len = 0;
  IBin::decode(og_stream, len);
  ASSERT_EQ(65535, len);
}

TEST(IBin, len65536) {
  std::istringstream og_stream(IOBinData::len65536());
  size_t len = 0;
  IBin::decode(og_stream, len);
  ASSERT_EQ(65536, len);
}

TEST(IBin, len15309671) {
  std::istringstream og_stream(IOBinData::len15309671());
  size_t len = 0;
  IBin::decode(og_stream, len);
  ASSERT_EQ(15309671, len);
}

TEST(IBin, len3603863485) {
  std::istringstream og_stream(IOBinData::len3603863485());
  size_t len = 0;
  IBin::decode(og_stream, len);
  ASSERT_EQ(size_t(3603863485), len);
}

TEST(IBin, len4294967295) {
  std::istringstream og_stream(IOBinData::len4294967295());
  size_t len = 0;
  IBin::decode(og_stream, len);
  ASSERT_EQ(4294967295, len);
}

TEST(IBin, empty_array) {
  std::istringstream in_stream(IOBinData::empty_array());
  LTVar in_value;
  IBin IBin(in_value);
  in_stream >> IBin;
  ASSERT_EQ(LTVar::Type::kArray, in_value);
  ASSERT_EQ(0, in_value.size());
}

TEST(IBin, bool_true) {
  std::istringstream in_stream(IOBinData::bool_true());
  LTVar in_value;
  IBin IBin(in_value);
  in_stream >> IBin;
  ASSERT_EQ(LTVar::Type::kBool, in_value);
  ASSERT_EQ(true, in_value);
}

TEST(IBin, bool_false) {
  std::istringstream in_stream(IOBinData::bool_false());
  LTVar in_value;
  IBin IBin(in_value);
  in_stream >> IBin;
  ASSERT_EQ(LTVar::Type::kBool, in_value);
  ASSERT_EQ(false, in_value);
}

TEST(IBin, double_value) {
  std::istringstream in_stream(IOBinData::double_value());
  LTVar in_value;
  IBin IBin(in_value);
  in_stream >> IBin;
  ASSERT_EQ(LTVar::Type::kDouble, in_value);
  ASSERT_EQ(123.456, in_value);
}

TEST(IBin, empty_hash) {
  std::istringstream in_stream(IOBinData::empty_hash());
  LTVar in_value;
  IBin IBin(in_value);
  in_stream >> IBin;
  ASSERT_EQ(LTVar::Type::kHash, in_value);
  ASSERT_EQ(0, in_value.size());
}

TEST(IBin, integer) {
  std::istringstream in_stream(IOBinData::integer());
  LTVar in_value;
  IBin IBin(in_value);
  in_stream >> IBin;
  ASSERT_EQ(LTVar::Type::kInteger, in_value);
  ASSERT_EQ(123, in_value);
}

TEST(IBin, text) {
  std::istringstream in_stream(IOBinData::text());
  LTVar in_value;
  IBin IBin(in_value);
  in_stream >> IBin;
  ASSERT_EQ(LTVar::Type::kText, in_value);
  ASSERT_EQ(std::string("anything"), in_value);
}

TEST(IBin, void_value) {
  std::istringstream in_stream(IOBinData::void_value());
  LTVar in_value;
  IBin IBin(in_value);
  in_stream >> IBin;
  ASSERT_EQ(LTVar::Type::kVoid, in_value);
}

TEST(IBin, fill_array) {
  std::istringstream in_stream(IOBinData::fill_array());
  LTVar in_value;
  IBin IBin(in_value);
  in_stream >> IBin;
  ASSERT_EQ(LTVar::Type::kArray, in_value);
  ASSERT_EQ(6, in_value.size());
  ASSERT_EQ(LTVar::Type::kBool, in_value[0]);
  ASSERT_EQ(true, in_value[0]);
  ASSERT_EQ(LTVar::Type::kDouble, in_value[1]);
  ASSERT_EQ(123.456, in_value[1]);
  ASSERT_EQ(LTVar::Type::kInteger, in_value[2]);
  ASSERT_EQ(123, in_value[2]);
  ASSERT_EQ(LTVar::Type::kText, in_value[3]);
  ASSERT_EQ(std::string("anything"), in_value[3]);
  ASSERT_EQ(LTVar::Type::kVoid, in_value[4]);
  ASSERT_EQ(LTVar::Type::kHash, in_value[5]);
}

TEST(IBin, fill_hash) {
  std::istringstream in_stream(IOBinData::fill_hash());
  LTVar in_value;
  IBin IBin(in_value);
  in_stream >> IBin;
  ASSERT_EQ(LTVar::Type::kHash, in_value);
  ASSERT_EQ(6, in_value.size());
  ASSERT_EQ(LTVar::Type::kBool, in_value["bool"]);
  ASSERT_EQ(true, in_value["bool"]);
  ASSERT_EQ(LTVar::Type::kDouble, in_value["double"]);
  ASSERT_EQ(123.456, in_value["double"]);
  ASSERT_EQ(LTVar::Type::kInteger, in_value["integer"]);
  ASSERT_EQ(123, in_value["integer"]);
  ASSERT_EQ(LTVar::Type::kText, in_value["text"]);
  ASSERT_EQ(std::string("anything"), in_value["text"]);
  ASSERT_EQ(LTVar::Type::kVoid, in_value["void"]);
  ASSERT_EQ(LTVar::Type::kArray, in_value["array"]);
  ASSERT_EQ(0, in_value["array"].size());
}

TEST(IBin, array_hash_nested) {
  std::istringstream in_stream(IOBinData::array_hash_nested());
  LTVar in_value;
  IBin IBin(in_value);
  in_stream >> IBin;
  ASSERT_EQ(LTVar::Type::kVoid, in_value["array"][0]["void"]);
}
