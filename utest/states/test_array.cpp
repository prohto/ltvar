#include "ltvar.h"
#include "test_data.h"
#include "utest.h"

using ::testing::An;
using ::testing::Matcher;
using ::testing::TypedEq;

LTVarArray test_array_differ = {
    LTVar(TEST_VALUE_BOOL_TRUE), LTVar(TEST_VALUE_DOUBLE),
    LTVar(TEST_VALUE_INTEGER), LTVar(TEST_VALUE_TEXT), LTVar(TEST_VALUE_TEXT)};

TEST(ArrayValue, is) {
  Array value;

  ASSERT_TRUE(value.is_array());
  ASSERT_FALSE(value.is_bool());
  ASSERT_FALSE(value.is_double());
  ASSERT_FALSE(value.is_hash());
  ASSERT_FALSE(value.is_integer());
  ASSERT_FALSE(value.is_text());
  ASSERT_FALSE(value.is_void());
}

TEST(ArrayValue, get_empty) {
  Array value;
  LTVarArray empty;
  ASSERT_FALSE(value.get_bool());
  ASSERT_EQ(value.get_double(), 0.0);
  ASSERT_EQ(value.get_int(), 0);
  ASSERT_EQ(value.get_text(), "<array>");

  ASSERT_THROW(value.get((const char *)"tag"), std::invalid_argument);
  LTVar void_value;
  ASSERT_EQ(value.get((size_t)0), void_value);
  ASSERT_EQ(value.size(), 0);
}

TEST(ArrayValue, get_const) {
  const Array const_value(test_array);
  LTVar void_value;
  ASSERT_EQ(const_value.get(test_array.size()), void_value);
  ASSERT_EQ(const_value.size(), test_array.size());
  ASSERT_EQ(const_value.get((size_t)0), test_array[0]);
}

TEST(ArrayValue, get_fill) {
  Array value(test_array);
  ASSERT_TRUE(value.get_bool());
  ASSERT_EQ(value.get_double(), test_array.size());
  ASSERT_EQ(value.get_int(), test_array.size());
  ASSERT_EQ(value.get_text(), "<array>");

  ASSERT_THROW(value.get("tag"), std::invalid_argument);
  ASSERT_EQ(value.get((size_t)0), test_array[0]);
  ASSERT_EQ(value.size(), test_array.size());
}

TEST(ArrayValue, set) {
  Array value;
  ASSERT_THROW(value.set("tag", LTVar(TEST_VALUE_DOUBLE)),
               std::invalid_argument);
  ASSERT_NO_THROW(value.set((size_t)0, LTVar(TEST_VALUE_DOUBLE)));
}

TEST(ArrayValue, copy) {
  Array value(test_array);
  ASSERT_TRUE(value.equal(test_array));

  std::unique_ptr<Void> ptr(value.copy());
  ASSERT_TRUE(ptr->is_array());
  ASSERT_EQ(*ptr, value);
}

TEST(ArrayValue, differ) {
  Array lhs(test_array);
  ASSERT_FALSE(lhs.equal(test_array_differ));

  Array rhs(test_array_differ);
  ASSERT_NE(lhs, rhs);
}

TEST(ArrayValue, empty_iterator) {
  Array value;
  size_t count = 0;
  for (auto item : value) {
    count++;
  }
  ASSERT_EQ(count, value.size());
  LTVarIterator biter = value.begin();
  LTVarIterator eiter = value.end();
  ASSERT_EQ(biter, eiter);
}

TEST(ArrayValue, fill_iterator) {
  Array value(test_array);
  size_t count = 0;
  for (auto item : value) {
    count++;
  }
  ASSERT_EQ(count, value.size());
  LTVarIterator iter;
  iter = value.begin();
  ASSERT_EQ(iter.first(), 0);
  ASSERT_EQ(iter.second(), test_array[(size_t)0]);
}
