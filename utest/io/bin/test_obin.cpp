#include "gmock/gmock.h"
#include "gtest/gtest.h"

#include "io/bin/obin.h"
#include "test_iodata.h"
#include "utest.h"

using namespace Harmonix;

LTypeArray test_array_local = {LType(TEST_VALUE_BOOL_TRUE),
                               LType(TEST_VALUE_DOUBLE),
                               LType(TEST_VALUE_INTEGER),
                               LType(TEST_VALUE_TEXT),
                               LType(),
                               LType(LType::Type::kHash)};

LTypeHash test_hash_local = {
    std::make_pair("bool", LType(TEST_VALUE_BOOL_TRUE)),
    std::make_pair("double", LType(TEST_VALUE_DOUBLE)),
    std::make_pair("integer", LType(TEST_VALUE_INTEGER)),
    std::make_pair("text", LType(TEST_VALUE_TEXT)),
    std::make_pair("void", LType()),
    std::make_pair("array", LType(LType::Type::kArray))};

std::string HEX_ARR_TO_STR(std::vector<unsigned char> array) {
  return std::string(array.begin(), array.end());
}

TEST(Obin, len87) {
  std::ostringstream og_stream;
  size_t len = 87;
  OBin::encode(og_stream, len);
  ASSERT_EQ(IOBinData::len87(), og_stream.str());
}

TEST(Obin, len128) {
  std::ostringstream og_stream;
  size_t len = 128;
  OBin::encode(og_stream, len);
  ASSERT_EQ(IOBinData::len128(), og_stream.str());
}

TEST(Obin, len4000) {
  std::ostringstream og_stream;
  size_t len = 4000;
  OBin::encode(og_stream, len);
  ASSERT_EQ(IOBinData::len4000(), og_stream.str());
}

TEST(Obin, len32159) {
  std::ostringstream og_stream;
  size_t len = 32159;
  OBin::encode(og_stream, len);
  ASSERT_EQ(IOBinData::len32159(), og_stream.str());
}

TEST(Obin, len65433) {
  std::ostringstream og_stream;
  size_t len = 65433;
  OBin::encode(og_stream, len);
  ASSERT_EQ(IOBinData::len65433(), og_stream.str());
}

TEST(Obin, len65535) {
  std::ostringstream og_stream;
  size_t len = 65535;
  OBin::encode(og_stream, len);
  ASSERT_EQ(IOBinData::len65535(), og_stream.str());
}

TEST(Obin, len65536) {
  std::ostringstream og_stream;
  size_t len = 65536;
  OBin::encode(og_stream, len);
  ASSERT_EQ(IOBinData::len65536(), og_stream.str());
}

TEST(Obin, len15309671) {
  std::ostringstream og_stream;
  size_t len = 15309671;
  OBin::encode(og_stream, len);
  ASSERT_EQ(IOBinData::len15309671(), og_stream.str());
}

TEST(Obin, len3603863485) {
  std::ostringstream og_stream;
  size_t len = 3603863485;
  OBin::encode(og_stream, len);
  ASSERT_EQ(IOBinData::len3603863485(), og_stream.str());
}

TEST(Obin, len4294967295) {
  std::ostringstream og_stream;
  size_t len = 4294967295;
  OBin::encode(og_stream, len);
  ASSERT_EQ(IOBinData::len4294967295(), og_stream.str());
}

TEST(OBin, empty_array) {
  std::ostringstream og_stream;
  LType og_value(LType::Type::kArray);
  OBin obin(og_value);
  og_stream << obin;
  ASSERT_EQ(IOBinData::empty_array(), og_stream.str());
}

TEST(OBin, fill_array) {
  std::ostringstream og_stream;
  LType og_value(test_array_local);
  OBin obin(og_value);
  og_stream << obin;
  ASSERT_EQ(IOBinData::fill_array(), og_stream.str());
}

TEST(OBin, bool_true) {
  std::ostringstream og_stream;
  LType og_value(TEST_VALUE_BOOL_TRUE);
  OBin obin(og_value);
  og_stream << obin;
  ASSERT_EQ(IOBinData::bool_true(), og_stream.str());
}

TEST(OBin, bool_false) {
  std::ostringstream og_stream;
  LType og_value(TEST_VALUE_BOOL_FALSE);
  OBin obin(og_value);
  og_stream << obin;
  ASSERT_EQ(IOBinData::bool_false(), og_stream.str());
}

TEST(OBin, double) {
  std::ostringstream og_stream;
  LType og_value(TEST_VALUE_DOUBLE);
  OBin obin(og_value);
  og_stream << obin;
  ASSERT_EQ(IOBinData::double_value(), og_stream.str());
}

TEST(OBin, empty_hash) {
  std::ostringstream og_stream;
  LType og_value(LType::Type::kHash);
  OBin obin(og_value);
  og_stream << obin;
  ASSERT_EQ(IOBinData::empty_hash(), og_stream.str());
}

TEST(OBin, fill_hash) {
  std::ostringstream og_stream;
  LType og_value(test_hash_local);
  OBin obin(og_value);
  og_stream << obin;
  ASSERT_EQ(IOBinData::fill_hash(), og_stream.str());
}

TEST(OBin, integer) {
  std::ostringstream og_stream;
  LType og_value(TEST_VALUE_INTEGER);
  OBin obin(og_value);
  og_stream << obin;
  ASSERT_EQ(IOBinData::integer(), og_stream.str());
}

TEST(OBin, text) {
  std::ostringstream og_stream;
  LType og_value(TEST_VALUE_TEXT);
  OBin obin(og_value);
  og_stream << obin;
  ASSERT_EQ(IOBinData::text(), og_stream.str());
}

TEST(OBin, void) {
  std::ostringstream og_stream;
  LType og_value;
  OBin obin(og_value);
  og_stream << obin;
  ASSERT_EQ(IOBinData::void_value(), og_stream.str());
}

TEST(OBin, array_hash_nested) {
  std::ostringstream og_stream;
  LType og_value(LType::LType::kHash);
  og_value["array"] = LType::LType::kArray;
  og_value["array"][0] = LType::LType::kHash;
  og_value["array"][0]["void"] = LType::LType::kVoid;

  OBin obin(og_value);
  og_stream << obin;
  ASSERT_EQ(IOBinData::array_hash_nested(), og_stream.str());
}
