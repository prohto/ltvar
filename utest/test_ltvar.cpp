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
  bool cast_value = static_cast<bool>(value);
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
  int cast_value = static_cast<int>(value);
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
  std::string cast_value = value;
  ASSERT_EQ(value, cast_value);
  ASSERT_NE(value, TEST_VALUE_TEXT);
  ASSERT_EQ(value, LTVar::kText);
  ASSERT_NE(value, LTVar::kVoid);
}

TEST(LTVar, constChar) {
  LTVar value(TEST_VALUE_CONSTCHAR);
  ASSERT_EQ(value, std::string(TEST_VALUE_CONSTCHAR));
  std::string cast_value = value;
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
  ASSERT_THROW(value["level1"], invalid_cast);
  value = LTVar::kHash;
  ASSERT_NO_THROW(value["level1"]);
  ASSERT_NO_THROW(value[""]);
  ASSERT_THROW(value[1], invalid_cast);
  ASSERT_THROW(value["level1"]["level2"], invalid_cast);
  value["level1"] = LTVar::kHash;
  ASSERT_NO_THROW(value["level1"]["level2"]);
}

TEST(LTVar, array_access) {
  LTVar value;

  ASSERT_NE(LTVar::kArray, value);
  ASSERT_THROW(value[1], invalid_cast);
  value = LTVar::kArray;
  ASSERT_NO_THROW(value[1]);
  ASSERT_THROW(value["level1"], invalid_cast);
  ASSERT_THROW(value[1][2], invalid_cast);
  value[1] = LTVar::kArray;
  ASSERT_NO_THROW(value[1][1]);
}

TEST(LTVar, get_hash_first_level) {
  LTVar value;

  ASSERT_THROW(value.get("level1"), invalid_cast);
  value = LTVar::kHash;
  ASSERT_EQ(LTVar::kVoid, value.get("level1"));
  value["level1"] = 10;
  ASSERT_EQ(10, value.get("level1"));
}

TEST(LTVar, get_hash_second_level) {
  LTVar value(LTVar::kHash);

  ASSERT_THROW(value.get("level1.level2"), invalid_cast);
  value["level1"] = LTVar::kHash;
  ASSERT_EQ(LTVar::kVoid, value.get("level1.level2"));
  value["level1"]["level2"] = 10;
  ASSERT_EQ(10, value.get("level1.level2"));
}

TEST(LTVar, get_hash_third_level) {
  LTVar value(LTVar::kHash);

  value["level1"] = LTVar::kHash;
  ASSERT_THROW(value.get("level1.level2.level3"), invalid_cast);
  value["level1"]["level2"] = LTVar::kHash;
  ASSERT_EQ(LTVar::kVoid, value.get("level1.level2.level3"));
  value["level1"]["level2"]["level3"] = 10;
  ASSERT_EQ(10, value.get("level1.level2.level3"));
}

TEST(LTVar, get_array_first_level) {
  LTVar value;

  ASSERT_THROW(value.get("[1]"), invalid_cast);
  value = LTVar::kArray;
  ASSERT_EQ(LTVar::kVoid, value.get("[1]"));
  value[1] = 10;
  ASSERT_EQ(10, value.get("[1]"));
}

TEST(LTVar, get_array_second_level) {
  LTVar value(LTVar::kArray);

  ASSERT_THROW(value.get("[1][2]"), invalid_cast);
  value[1] = LTVar::kArray;
  ASSERT_EQ(LTVar::kVoid, value.get("[1][2]"));
  value[1][2] = 10;
  ASSERT_EQ(10, value.get("[1][2]"));
}

TEST(LTVar, get_array_third_level) {
  LTVar value(LTVar::kArray);

  value[1] = LTVar::kArray;
  ASSERT_THROW(value.get("[1][2][3]"), invalid_cast);
  value[1][2] = LTVar::kArray;
  ASSERT_EQ(LTVar::kVoid, value.get("[1][2][3]"));
  value[1][2][3] = 10;
  ASSERT_EQ(LTVar::kInteger, value.get("[1][2][3]"));
}

TEST(LTVar, get_mixed_hash_start) {
  LTVar value(LTVar::kHash);

  value["level1"] = LTVar::kArray;
  value["level1"][0] = "text";
  value["level1"][1] = LTVar::kHash;
  value["level1"][1]["level3"] = false;

  ASSERT_EQ(std::string("text"), value.get("level1[0]"));
  ASSERT_EQ(false, value.get("level1[1].level3"));
}

TEST(LTVar, get_mixed_array_start) {
  LTVar value(LTVar::kArray);

  value[0] = "text";
  value[1] = LTVar::kHash;
  value[1]["level2"] = LTVar::kArray;
  value[1]["level2"][0] = "text";
  value[1]["level2"][1] = false;

  ASSERT_EQ(std::string("text"), value.get("[0]"));
  ASSERT_EQ(std::string("text"), value.get("[1].level2[0]"));
  ASSERT_EQ(false, value.get("[1].level2[1]"));
}

TEST(LTVar, get_hash_invalid_argument) {
  LTVar value(LTVar::kHash);

  value["level1"] = LTVar::kArray;
  ASSERT_THROW(value.get(".level2.level3"), std::invalid_argument);
  ASSERT_THROW(value.get("level1..level2"), std::invalid_argument);
  ASSERT_THROW(value.get("level1[1]..level2"), std::invalid_argument);
}

TEST(LTVar, get_array_invalid_argument) {
  LTVar value(LTVar::kArray);

  value[0] = LTVar::kArray;
  value[1] = LTVar::kHash;
  value[1]["level3"] = LTVar::kArray;
  ASSERT_THROW(value.get("[uuu].level2"), std::invalid_argument);
  ASSERT_THROW(value.get("[0][ddd]"), std::invalid_argument);
  ASSERT_THROW(value.get("[1].level3[ssss]"), std::invalid_argument);
}

TEST(LTVar, get_missing_default) {
  LTVar value(LTVar::kArray);

  value[0] = "text";
  value[1] = LTVar::kHash;
  value[1]["level2"] = LTVar::kArray;
  value[1]["level2"][0] = "text";
  value[1]["level2"][1] = false;

  ASSERT_THROW(value.get("level1[2]", true), invalid_cast);
  ASSERT_THROW(value.get("[1][2]", true), invalid_cast);
  ASSERT_EQ(true, value.get("[2]", true));
  ASSERT_EQ(true, value.get("[1].unknown", true));
  value[2] = "FOUND";
  ASSERT_EQ(std::string("FOUND"), value.get("[2]", "DEFAULT"));
  ASSERT_EQ(false, value.get("[1].level2[1]", true));
}

TEST(LTVar, reset_type) {
  LTVar value(LTVar::kHash);

  value.set( "level1.level2", "text" );
  value.set( "level1", LTVar::kHash );
  ASSERT_EQ(value.get("level1.level2" ), std::string("text") );
  value.set( "level1", LTVar::kBool );
  ASSERT_EQ(LTVar::kBool, value["level1"]);
}
TEST(LTVar, set_hash_first_level) {
  LTVar value(LTVar::kBool);

  ASSERT_THROW(value.set("level1", LTVar::kBool), invalid_cast);
  value = LTVar::kHash;
  ASSERT_NO_THROW(value.set("level1", LTVar::kBool));
  ASSERT_EQ(LTVar::kBool, value["level1"]);
}

TEST(LTVar, set_hash_second_level) {
  LTVar value(LTVar::kHash);

  ASSERT_NO_THROW(value.set("level1.level2", true));
  ASSERT_EQ(true, value["level1"]["level2"]);
  value["level1"] = LTVar::kBool;
  ASSERT_THROW(value.set("level1.level2", LTVar::kBool), invalid_cast);
  value["level1"] = LTVar::kVoid;
  ASSERT_NO_THROW(value.set("level1.level2", LTVar::kBool));
  ASSERT_EQ(LTVar::kBool, value["level1"]["level2"]);
}

TEST(LTVar, set_hash_third_level) {
  LTVar value(LTVar::kHash);

  ASSERT_NO_THROW(value.set("level1.level2.level3", true));
  ASSERT_EQ(true, value["level1"]["level2"]["level3"]);
  ASSERT_EQ(LTVar::kBool, value["level1"]["level2"]["level3"]);
  value["level1"]["level2"] = LTVar::kArray;
  ASSERT_THROW(value.set("level1.level2.level3", LTVar::kBool), invalid_cast);
}

TEST(LTVar, set_array_first_level) {
  LTVar value(LTVar::kBool);

  ASSERT_THROW(value.set("[1]", LTVar::kBool), invalid_cast);
  value = LTVar::kArray;
  ASSERT_NO_THROW(value.set("[1]", true));
  ASSERT_EQ(LTVar::kBool, value[1]);
  ASSERT_EQ(true, value[1]);
}

TEST(LTVar, set_array_second_level) {
  LTVar value(LTVar::kArray);

  ASSERT_NO_THROW(value.set("[1][2]", true));
  ASSERT_EQ(LTVar::kBool, value[1][2]);
  ASSERT_EQ(true, value[1][2]);
  value[1] = LTVar::kBool;
  ASSERT_THROW(value.set("[1][2]", LTVar::kBool), invalid_cast);
}

TEST(LTVar, set_array_third_level) {
  LTVar value(LTVar::kArray);

  ASSERT_NO_THROW(value.set("[1][2][3]", true));
  ASSERT_EQ(LTVar::kBool, value[1][2][3]);
  ASSERT_EQ(true, value[1][2][3]);
  value[1][2] = LTVar::kBool;
  ASSERT_THROW(value.set("[1][2][3]", LTVar::kBool), invalid_cast);
}

TEST(LTVar, set_mixed_hash_start) {
  LTVar value;

  ASSERT_NO_THROW(value.set("level1[0]", "TEXT"));
  ASSERT_NO_THROW(value.set("level1[1].level3", true));

  ASSERT_EQ(LTVar::kText, value.get("level1[0]"));
  ASSERT_EQ(std::string("TEXT"), value.get("level1[0]"));
  ASSERT_EQ(LTVar::kBool, value.get("level1[1].level3"));
  ASSERT_EQ(true, value.get("level1[1].level3"));
}

TEST(LTVar, set_mixed_array_start) {
  LTVar value;

  ASSERT_NO_THROW(value.set("[0]", "TEXT"));
  ASSERT_NO_THROW(value.set("[1].level2[0]", "TEXT2"));
  ASSERT_NO_THROW(value.set("[1].level2[1]", true));

  ASSERT_EQ(LTVar::kText, value.get("[0]"));
  ASSERT_EQ(std::string("TEXT"), value.get("[0]"));
  ASSERT_EQ(LTVar::kText, value.get("[1].level2[0]"));
  ASSERT_EQ(std::string("TEXT2"), value.get("[1].level2[0]"));
  ASSERT_EQ(LTVar::kBool, value.get("[1].level2[1]"));
  ASSERT_EQ(true, value.get("[1].level2[1]"));
}
