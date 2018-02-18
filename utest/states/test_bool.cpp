#include "ltype.h"
#include "test_data.h"
#include "utest.h"

using namespace std;

using namespace Harmonix;
using ::testing::An;
using ::testing::Matcher;
using ::testing::TypedEq;

TEST(BoolValue, is) {
  Bool value;

  ASSERT_FALSE(value.is_array());
  ASSERT_TRUE(value.is_bool());
  ASSERT_FALSE(value.is_double());
  ASSERT_FALSE(value.is_hash());
  ASSERT_FALSE(value.is_integer());
  ASSERT_FALSE(value.is_string());
  ASSERT_FALSE(value.is_void());
}

TEST(BoolValue, get_true) {
  Bool value(TEST_VALUE_BOOL_TRUE);
  ASSERT_EQ(value.get_bool(), TEST_VALUE_BOOL_TRUE);
  ASSERT_EQ(value.get_double(), (double)TEST_VALUE_BOOL_TRUE);
  ASSERT_EQ(value.get_int(), (int)TEST_VALUE_BOOL_TRUE);
  ASSERT_EQ(value.get_string(), STRINGIFY(TEST_VALUE_BOOL_TRUE));
}

TEST(BoolValue, get_false) {
  Bool value(TEST_VALUE_BOOL_FALSE);
  ASSERT_EQ(value.get_bool(), TEST_VALUE_BOOL_FALSE);
  ASSERT_EQ(value.get_double(), (double)TEST_VALUE_BOOL_FALSE);
  ASSERT_EQ(value.get_int(), (int)TEST_VALUE_BOOL_FALSE);
  ASSERT_EQ(value.get_string(), STRINGIFY(TEST_VALUE_BOOL_FALSE));
}

TEST(BoolValue, get) {
  Bool value;
  ASSERT_THROW(value.get("tag"), std::invalid_argument);
  ASSERT_THROW(value.get((size_t)0), std::invalid_argument);
  ASSERT_THROW(value.size(), std::invalid_argument);
}

TEST(BoolValue, set) {
  Bool value;
  ASSERT_THROW(value.set("tag", LType(TEST_VALUE_BOOL_TRUE)),
               std::invalid_argument);
  ASSERT_THROW(value.set((size_t)0, LType(TEST_VALUE_BOOL_TRUE)),
               std::invalid_argument);
}

TEST(BoolValue, copy_true) {
  Bool value(TEST_VALUE_BOOL_TRUE);
  std::unique_ptr<Void> ptr(value.copy());
  ASSERT_TRUE(ptr->is_bool());
  ASSERT_TRUE(ptr->equal(TEST_VALUE_BOOL_TRUE));
  ASSERT_EQ(ptr->get_bool(), TEST_VALUE_BOOL_TRUE);
}

TEST(BoolValue, copy_false) {
  Bool value(TEST_VALUE_BOOL_FALSE);
  value.equal((int)TEST_VALUE_BOOL_FALSE);

  std::unique_ptr<Void> ptr(value.copy());
  ASSERT_TRUE(ptr->is_bool());
  ASSERT_EQ(ptr->get_bool(), TEST_VALUE_BOOL_FALSE);
}

TEST(BoolValue, differ) {
  Bool lhs_value(TEST_VALUE_BOOL_FALSE);
  ASSERT_FALSE(lhs_value.equal(TEST_VALUE_BOOL_TRUE));

  Integer rhs_value;
  ASSERT_NE(lhs_value, rhs_value);
}
