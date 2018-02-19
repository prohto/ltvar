#include "ltvar.h"
#include "test_data.h"
#include "utest.h"

using ::testing::An;
using ::testing::Matcher;
using ::testing::TypedEq;

TEST(IntegerValue, is) {
  Integer value;

  ASSERT_FALSE(value.is_array());
  ASSERT_FALSE(value.is_bool());
  ASSERT_FALSE(value.is_double());
  ASSERT_FALSE(value.is_hash());
  ASSERT_TRUE(value.is_integer());
  ASSERT_FALSE(value.is_text());
  ASSERT_FALSE(value.is_void());
}

TEST(IntegerValue, get) {
  Integer value(TEST_VALUE_INTEGER);
  ASSERT_EQ(value.get_bool(), (bool)(TEST_VALUE_INTEGER));
  ASSERT_EQ(value.get_double(), TEST_VALUE_INTEGER);
  ASSERT_EQ(value.get_int(), (int)(TEST_VALUE_INTEGER));
  ASSERT_EQ(value.get_text(), STRINGIFY(TEST_VALUE_INTEGER));

  ASSERT_THROW(value.get("tag"), std::invalid_argument);
  ASSERT_THROW(value.get((size_t)0), std::invalid_argument);
  ASSERT_THROW(value.size(), std::invalid_argument);
}

TEST(IntegerValue, set) {
  Integer value;
  ASSERT_THROW(value.set("tag", LTVar(TEST_VALUE_INTEGER)),
               std::invalid_argument);
  ASSERT_THROW(value.set((size_t)0, LTVar(TEST_VALUE_INTEGER)),
               std::invalid_argument);
}

TEST(IntegerValue, copy) {
  Integer value(TEST_VALUE_INTEGER);
  ASSERT_TRUE(value.equal(TEST_VALUE_INTEGER));

  std::unique_ptr<Void> ptr(value.copy());
  ASSERT_TRUE(ptr->is_integer());
  ASSERT_EQ(ptr->get_int(), TEST_VALUE_INTEGER);
}

TEST(IntegerValue, differ) {
  Integer lhs_value(TEST_VALUE_INTEGER);
  ASSERT_FALSE(lhs_value.equal(TEST_VALUE_INTEGER * 2));

  Bool rhs_value;
  ASSERT_NE(lhs_value, rhs_value);
}
