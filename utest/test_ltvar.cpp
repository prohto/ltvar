#include "ltvar.h"
#include "test_data.h"
#include "utest.h"


TEST(LTVar, array) {
  LTVar value(test_array);
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
  ASSERT_EQ(value, LTVar::kArray);
  ASSERT_NE(value, LTVar::kVoid);
}

TEST(LTVar, bool) {
  LTVar value(TEST_VALUE_BOOL_TRUE);
  ASSERT_EQ(value, TEST_VALUE_BOOL_TRUE);
  value = TEST_VALUE_BOOL_FALSE;
  ASSERT_EQ(value, TEST_VALUE_BOOL_FALSE);
  bool cast_value = (bool)value;
  ASSERT_EQ(value, cast_value);
  ASSERT_NE(value, TEST_VALUE_BOOL_TRUE);
  ASSERT_EQ(value, LTVar::kBool);
  ASSERT_NE(value, LTVar::kVoid);
}

TEST(LTVar, double) {
  LTVar value(TEST_VALUE_DOUBLE);
  ASSERT_EQ(value, TEST_VALUE_DOUBLE);
  value = TEST_VALUE_DOUBLE * 2;
  ASSERT_EQ(value, TEST_VALUE_DOUBLE * 2);
  double cast_value = (double)value;
  ASSERT_EQ(value, cast_value);
  ASSERT_NE(value, TEST_VALUE_DOUBLE);
  ASSERT_EQ(value, LTVar::kDouble);
  ASSERT_NE(value, LTVar::kVoid);
}

TEST(LTVar, hash) {
  LTVar value(test_hash);
  ASSERT_EQ(value, test_hash);
  test_hash["tag"] = TEST_VALUE_INTEGER;
  ASSERT_NE(value, test_hash);
  value["tag"] = TEST_VALUE_INTEGER;
  ASSERT_EQ(value, test_hash);
  ASSERT_EQ(value.size(), 6);
  value["tag2"] = test_hash;
  ASSERT_EQ(value["tag2"]["double"], TEST_VALUE_DOUBLE);
  ASSERT_EQ(value, LTVar::kHash);
  ASSERT_NE(value, LTVar::kVoid);
}

TEST(LTVar, integer) {
  LTVar value(TEST_VALUE_INTEGER);
  ASSERT_EQ(value, TEST_VALUE_INTEGER);
  value = TEST_VALUE_INTEGER * 2;
  ASSERT_EQ(value, TEST_VALUE_INTEGER * 2);
  int cast_value = (int)value;
  ASSERT_EQ(value, cast_value);
  ASSERT_NE(value, TEST_VALUE_INTEGER);
  ASSERT_EQ(value, LTVar::kInteger);
  ASSERT_NE(value, LTVar::kVoid);
}

TEST(LTVar, string) {
  LTVar value(TEST_VALUE_TEXT);
  ASSERT_EQ(value, TEST_VALUE_TEXT);
  value = TEST_VALUE_TEXT + "2";
  ASSERT_EQ(value, TEST_VALUE_TEXT + "2");
  std::string cast_value = (std::string)value;
  ASSERT_EQ(value, cast_value);
  ASSERT_NE(value, TEST_VALUE_TEXT);
  ASSERT_EQ(value, LTVar::kText);
  ASSERT_NE(value, LTVar::kVoid);
}

TEST(LTVar, constChar) {
  LTVar value(TEST_VALUE_CONSTCHAR);
  ASSERT_EQ(value, std::string(TEST_VALUE_CONSTCHAR));
  std::string cast_value = (std::string)value;
  ASSERT_EQ(value, cast_value);
  ASSERT_EQ(value, LTVar::kText);
  ASSERT_NE(value, LTVar::kVoid);
}

TEST(LTVar, voidvalue) {
  LTVar value;
  ASSERT_EQ(value, Void());
  ASSERT_EQ(value, LTVar::kVoid);
  ASSERT_NE(value, LTVar::kArray);
}

TEST(LTVar, iterator_hash) {
  LTVar value(test_hash);
  size_t count = 0;
  for (auto item : value) count++;
  ASSERT_EQ(count, value.size());
}

TEST(LTVar, iterator_array) {
  LTVar value(test_array);
  size_t count = 0;
  for (auto item : value) count++;
  ASSERT_EQ(count, value.size());
}

TEST(LTVar, iterator_type) {
  LTVar hash_value(test_hash);
  LTVar array_value(test_array);
  ASSERT_NE(hash_value.begin(), array_value.begin());
}

TEST(LTVar, equal) {
  LTVar equal(test_hash);
  LTVar nequal;

  ASSERT_EQ(equal, test_hash);
  ASSERT_NE(nequal, equal);

  equal = TEST_VALUE_DOUBLE;
  nequal = TEST_VALUE_DOUBLE * 2;
  ASSERT_NE(nequal, equal);
}

TEST(LTVar, hash_access) {
  LTVar value;

  ASSERT_NE(LTVar::kHash, value);
  ASSERT_THROW(value["level1"], std::invalid_argument);
  value = LTVar::kHash;
  ASSERT_NO_THROW(value["level1"]);
  ASSERT_THROW(value[1], std::invalid_argument);
  ASSERT_THROW(value["level1"]["level2"], std::invalid_argument);
  value["level1"] = LTVar::kHash;
  ASSERT_NO_THROW(value["level1"]["level2"]);
}

TEST(LTVar, array_access) {
  LTVar value;

  ASSERT_NE(LTVar::kArray, value);
  ASSERT_THROW(value[1], std::invalid_argument);
  value = LTVar::kArray;
  ASSERT_NO_THROW(value[1]);
  ASSERT_THROW(value["level1"], std::invalid_argument);
  ASSERT_THROW(value[1][2], std::invalid_argument);
  value[1] = LTVar::kArray;
  ASSERT_NO_THROW(value[1][1]);
}
