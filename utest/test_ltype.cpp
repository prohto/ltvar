#include "ltype.h"
#include "test_data.h"
#include "utest.h"

using namespace Harmonix;

TEST(LType, array) {
  LType value(test_array);
  ASSERT_EQ(value[1], TEST_VALUE_DOUBLE);
  ASSERT_EQ(value, test_array);
  test_array.resize(6);
  test_array[5] = TEST_VALUE_INTEGER;
  ASSERT_NE(value, test_array);
  value[5] = TEST_VALUE_INTEGER;
  ASSERT_EQ(value, test_array);
  ASSERT_EQ(value.size(), 6);
  value[6] = test_array;
  ASSERT_EQ(value[6][1], TEST_VALUE_DOUBLE);
  ASSERT_EQ(value, LType::kArray);
  ASSERT_NE(value, LType::kVoid);
}

TEST(LType, bool) {
  LType value(TEST_VALUE_BOOL_TRUE);
  ASSERT_EQ(value, TEST_VALUE_BOOL_TRUE);
  value = TEST_VALUE_BOOL_FALSE;
  ASSERT_EQ(value, TEST_VALUE_BOOL_FALSE);
  bool cast_value = (bool)value;
  ASSERT_EQ(value, cast_value);
  ASSERT_NE(value, TEST_VALUE_BOOL_TRUE);
  ASSERT_EQ(value, LType::kBool);
  ASSERT_NE(value, LType::kVoid);
}

TEST(LType, double) {
  LType value(TEST_VALUE_DOUBLE);
  ASSERT_EQ(value, TEST_VALUE_DOUBLE);
  value = TEST_VALUE_DOUBLE * 2;
  ASSERT_EQ(value, TEST_VALUE_DOUBLE * 2);
  double cast_value = (double)value;
  ASSERT_EQ(value, cast_value);
  ASSERT_NE(value, TEST_VALUE_DOUBLE);
  ASSERT_EQ(value, LType::kDouble);
  ASSERT_NE(value, LType::kVoid);
}

TEST(LType, hash) {
  LType value(test_hash);
  ASSERT_EQ(value, test_hash);
  test_hash["tag"] = TEST_VALUE_INTEGER;
  ASSERT_NE(value, test_hash);
  value["tag"] = TEST_VALUE_INTEGER;
  ASSERT_EQ(value, test_hash);
  ASSERT_EQ(value.size(), 6);
  value["tag2"] = test_hash;
  ASSERT_EQ(value["tag2"]["double"], TEST_VALUE_DOUBLE);
  ASSERT_EQ(value, LType::kHash);
  ASSERT_NE(value, LType::kVoid);
}

TEST(LType, integer) {
  LType value(TEST_VALUE_INTEGER);
  ASSERT_EQ(value, TEST_VALUE_INTEGER);
  value = TEST_VALUE_INTEGER * 2;
  ASSERT_EQ(value, TEST_VALUE_INTEGER * 2);
  int cast_value = (int)value;
  ASSERT_EQ(value, cast_value);
  ASSERT_NE(value, TEST_VALUE_INTEGER);
  ASSERT_EQ(value, LType::kInteger);
  ASSERT_NE(value, LType::kVoid);
}

TEST(LType, string) {
  LType value(TEST_VALUE_TEXT);
  ASSERT_EQ(value, TEST_VALUE_TEXT);
  value = TEST_VALUE_TEXT + "2";
  ASSERT_EQ(value, TEST_VALUE_TEXT + "2");
  std::string cast_value = (std::string)value;
  ASSERT_EQ(value, cast_value);
  ASSERT_NE(value, TEST_VALUE_TEXT);
  ASSERT_EQ(value, LType::kText);
  ASSERT_NE(value, LType::kVoid);
}

TEST(LType, constChar) {
  LType value(TEST_VALUE_CONSTCHAR);
  ASSERT_EQ(value, std::string(TEST_VALUE_CONSTCHAR));
  std::string cast_value = (std::string)value;
  ASSERT_EQ(value, cast_value);
  ASSERT_EQ(value, LType::kText);
  ASSERT_NE(value, LType::kVoid);
}

TEST(LType, voidvalue) {
  LType value;
  ASSERT_EQ(value, Void());
  ASSERT_EQ(value, LType::kVoid);
  ASSERT_NE(value, LType::kArray);
}

TEST(LType, iterator_hash) {
  LType value(test_hash);
  size_t count = 0;
  for (auto item : value) count++;
  ASSERT_EQ(count, value.size());
}

TEST(LType, iterator_array) {
  LType value(test_array);
  size_t count = 0;
  for (auto item : value) count++;
  ASSERT_EQ(count, value.size());
}

TEST(LType, iterator_type) {
  LType hash_value(test_hash);
  LType array_value(test_array);
  ASSERT_NE(hash_value.begin(), array_value.begin());
}

TEST(LType, equal) {
  LType equal(test_hash);
  LType nequal;

  ASSERT_EQ(equal, test_hash);
  ASSERT_NE(nequal, equal);

  equal = TEST_VALUE_DOUBLE;
  nequal = TEST_VALUE_DOUBLE * 2;
  ASSERT_NE(nequal, equal);
}

TEST(LType, hash_access) {
  LType value;

  ASSERT_NE(LType::kHash, value);
  ASSERT_THROW(value["level1"], std::invalid_argument);
  value = LType::kHash;
  ASSERT_NO_THROW(value["level1"]);
  ASSERT_THROW(value[1], std::invalid_argument);
  ASSERT_THROW(value["level1"]["level2"], std::invalid_argument);
  value["level1"] = LType::kHash;
  ASSERT_NO_THROW(value["level1"]["level2"]);
}

TEST(LType, array_access) {
  LType value;

  ASSERT_NE(LType::kArray, value);
  ASSERT_THROW(value[1], std::invalid_argument);
  value = LType::kArray;
  ASSERT_NO_THROW(value[1]);
  ASSERT_THROW(value["level1"], std::invalid_argument);
  ASSERT_THROW(value[1][2], std::invalid_argument);
  value[1] = LType::kArray;
  ASSERT_NO_THROW(value[1][1]);
}
