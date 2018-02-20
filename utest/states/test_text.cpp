#include "ltvar.h"
#include "test_data.h"
#include "utest.h"

using ::testing::An;
using ::testing::Matcher;
using ::testing::TypedEq;

TEST(TextValue, is) {
  Text value;

  ASSERT_FALSE(value.is_array());
  ASSERT_FALSE(value.is_bool());
  ASSERT_FALSE(value.is_double());
  ASSERT_FALSE(value.is_hash());
  ASSERT_FALSE(value.is_integer());
  ASSERT_TRUE(value.is_text());
  ASSERT_FALSE(value.is_void());
}

TEST(TextValue, get_true) {
  Text value(STRINGIFY(TEST_VALUE_BOOL_TRUE));
  ASSERT_EQ(value.get_bool(), TEST_VALUE_BOOL_TRUE);
  ASSERT_THROW(value.get_double(), std::invalid_argument);
  ASSERT_THROW(value.get_int(), std::invalid_argument);
  ASSERT_EQ(value.get_text(), STRINGIFY(TEST_VALUE_BOOL_TRUE));
  ASSERT_THROW(value.get("tag"), std::invalid_argument);
  ASSERT_THROW(value.get((size_t)0), std::invalid_argument);
  ASSERT_THROW(value.size(), std::invalid_argument);
}

TEST(TextValue, get_double) {
  Text value(STRINGIFY(TEST_VALUE_DOUBLE));
  ASSERT_EQ(value.get_bool(), false);
  ASSERT_EQ(value.get_double(), TEST_VALUE_DOUBLE);
  ASSERT_EQ(value.get_int(), TEST_VALUE_INTEGER);
  ASSERT_EQ(value.get_text(), STRINGIFY(TEST_VALUE_DOUBLE));
  ASSERT_THROW(value.get("tag"), std::invalid_argument);
  ASSERT_THROW(value.get((size_t)0), std::invalid_argument);
  ASSERT_THROW(value.size(), std::invalid_argument);
}

TEST(TextValue, get_integer) {
  Text value(STRINGIFY(TEST_VALUE_INTEGER));
  ASSERT_EQ(value.get_bool(), false);
  ASSERT_EQ(value.get_double(), TEST_VALUE_INTEGER);
  ASSERT_EQ(value.get_int(), TEST_VALUE_INTEGER);
  ASSERT_EQ(value.get_text(), STRINGIFY(TEST_VALUE_INTEGER));
  ASSERT_THROW(value.get("tag"), std::invalid_argument);
  ASSERT_THROW(value.get((size_t)0), std::invalid_argument);
  ASSERT_THROW(value.size(), std::invalid_argument);
}

TEST(TextValue, get_anything) {
  Text value(TEST_VALUE_TEXT);
  ASSERT_EQ(value.get_bool(), TEST_VALUE_BOOL_FALSE);
  ASSERT_THROW(value.get_double(), std::invalid_argument);
  ASSERT_THROW(value.get_int(), std::invalid_argument);
  ASSERT_EQ(value.get_text(), TEST_VALUE_TEXT);
  ASSERT_THROW(value.get("tag"), std::invalid_argument);
  ASSERT_THROW(value.get((size_t)0), std::invalid_argument);
  ASSERT_THROW(value.size(), std::invalid_argument);
}

TEST(TextValue, set) {
  Text value;
  ASSERT_THROW(value.set("tag", LTVar(TEST_VALUE_TEXT)),
               std::invalid_argument);
  ASSERT_THROW(value.set((size_t)0, LTVar(TEST_VALUE_TEXT)),
               std::invalid_argument);
}

TEST(TextValue, copy) {
  Text value(TEST_VALUE_TEXT);
  ASSERT_TRUE(value.equal(TEST_VALUE_TEXT));

  std::unique_ptr<Void> ptr(value.copy());
  ASSERT_TRUE(ptr->is_text());
  ASSERT_EQ(ptr->get_text(), TEST_VALUE_TEXT);
}

TEST(TextValue, differ) {
  Text lhs_value;
  ASSERT_FALSE(lhs_value.equal(TEST_VALUE_TEXT));

  Bool rhs_value;
  ASSERT_NE(lhs_value, rhs_value);
}
