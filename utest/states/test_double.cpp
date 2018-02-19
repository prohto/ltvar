#include "ltvar.h"
#include "test_data.h"
#include "utest.h"

using ::testing::An;
using ::testing::Matcher;
using ::testing::TypedEq;

TEST(DoubleValue, is) {
  Double value;

  ASSERT_FALSE(value.is_array());
  ASSERT_FALSE(value.is_bool());
  ASSERT_TRUE(value.is_double());
  ASSERT_FALSE(value.is_hash());
  ASSERT_FALSE(value.is_integer());
  ASSERT_FALSE(value.is_text());
  ASSERT_FALSE(value.is_void());
}

TEST(DoubleValue, get) {
  Double value(TEST_VALUE_DOUBLE);
  ASSERT_EQ(value.get_bool(), (bool)(TEST_VALUE_DOUBLE));
  ASSERT_EQ(value.get_double(), TEST_VALUE_DOUBLE);
  ASSERT_EQ(value.get_int(), (int)(TEST_VALUE_DOUBLE));
  ASSERT_EQ(value.get_text(), std::to_string(TEST_VALUE_DOUBLE));
  ASSERT_THROW(value.get("tag"), std::invalid_argument);
  ASSERT_THROW(value.get((size_t)0), std::invalid_argument);
  ASSERT_THROW(value.size(), std::invalid_argument);
}

TEST(DoubleValue, set) {
  Double value;
  ASSERT_THROW(value.set("tag", LTVar(TEST_VALUE_DOUBLE)),
               std::invalid_argument);
  ASSERT_THROW(value.set((size_t)0, LTVar(TEST_VALUE_DOUBLE)),
               std::invalid_argument);
}

TEST(DoubleValue, copy) {
  Double value(TEST_VALUE_DOUBLE);
  ASSERT_TRUE(value.equal(TEST_VALUE_DOUBLE));

  std::unique_ptr<Void> ptr(value.copy());
  ASSERT_TRUE(ptr->is_double());
  ASSERT_EQ(ptr->get_double(), TEST_VALUE_DOUBLE);
}

TEST(DoubleValue, differ) {
  Double lhs_value;
  ASSERT_FALSE(lhs_value.equal(TEST_VALUE_DOUBLE * 2));

  Integer rhs_value;
  ASSERT_NE(lhs_value, rhs_value);
}
