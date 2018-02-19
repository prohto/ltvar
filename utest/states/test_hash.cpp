#include "ltvar.h"
#include "test_data.h"
#include "utest.h"

using ::testing::An;
using ::testing::Matcher;
using ::testing::TypedEq;

LTVarHash test_hash_nested = {
    std::make_pair("bool", LTVar(TEST_VALUE_BOOL_TRUE)),
    std::make_pair("double", LTVar(TEST_VALUE_DOUBLE)),
};

LTVarHash test_hash_nested_differ = {
    std::make_pair("bool", LTVar(TEST_VALUE_BOOL_TRUE)),
    std::make_pair("double", LTVar()),
};

LTVarHash test_hash_local = {
    std::make_pair("bool", LTVar(TEST_VALUE_BOOL_TRUE)),
    std::make_pair("double", LTVar(TEST_VALUE_DOUBLE)),
    std::make_pair("int", LTVar(TEST_VALUE_INTEGER)),
    std::make_pair("text", LTVar(TEST_VALUE_TEXT)),
    std::make_pair("void", LTVar()),
    std::make_pair("array", LTVar(test_array)),
    std::make_pair("hash", LTVar(test_hash_nested))};

LTVarHash test_hash_differ = {
    std::make_pair("bool", LTVar(TEST_VALUE_BOOL_TRUE)),
    std::make_pair("double", LTVar(TEST_VALUE_DOUBLE)),
    std::make_pair("int", LTVar(TEST_VALUE_INTEGER)),
    std::make_pair("text", LTVar(TEST_VALUE_TEXT)),
    std::make_pair("void", LTVar()),
    std::make_pair("array", LTVar(test_array)),
    std::make_pair("hash", LTVar(test_hash_nested_differ))};

TEST(HashValue, is) {
  Hash value;

  ASSERT_FALSE(value.is_bool());
  ASSERT_FALSE(value.is_double());
  ASSERT_TRUE(value.is_hash());
  ASSERT_FALSE(value.is_array());
  ASSERT_FALSE(value.is_integer());
  ASSERT_FALSE(value.is_text());
  ASSERT_FALSE(value.is_void());
}

TEST(HashValue, get_empty) {
  Hash value;
  LTVarHash empty_hash;
  ASSERT_FALSE(value.get_bool());
  ASSERT_EQ(value.get_double(), 0.0);
  ASSERT_EQ(value.get_int(), 0);
  ASSERT_EQ(value.get_text(), "<hash>");
  ASSERT_EQ(value.get("tag"), LTVar());
  ASSERT_THROW(value.get((size_t)0), std::invalid_argument);
  ASSERT_EQ(value.size(), 0);
}

TEST(HashValue, get_const) {
  const Hash const_value(test_hash_local);
  ASSERT_EQ(const_value.get("tag"), LTVar());
  ASSERT_EQ(const_value.size(), test_hash_local.size());
  ASSERT_EQ(const_value.get("double"), test_hash_local["double"]);
}

TEST(HashValue, get_fill) {
  Hash value(test_hash);
  ASSERT_TRUE(value.get_bool());
  ASSERT_EQ(value.get_double(), test_hash.size());
  ASSERT_EQ(value.get_int(), test_hash.size());
  ASSERT_EQ(value.get_text(), "<hash>");
  ASSERT_EQ(value.get("double"), test_hash_local["double"]);
  ASSERT_THROW(value.get((const size_t)0), std::invalid_argument);
  ASSERT_EQ(value.size(), test_hash.size());
}

TEST(HashValue, set) {
  Hash value;
  ASSERT_NO_THROW(value.set("tag", LTVar(TEST_VALUE_DOUBLE)));
  ASSERT_THROW(value.set((size_t)0, LTVar(TEST_VALUE_DOUBLE)),
               std::invalid_argument);
  ASSERT_THROW(value.set(nullptr, LTVar(TEST_VALUE_DOUBLE)),
               std::invalid_argument);
}

TEST(HashValue, copy) {
  Hash value(test_hash);
  ASSERT_TRUE(value.equal(test_hash));

  std::unique_ptr<Void> ptr(value.copy());
  ASSERT_TRUE(ptr->is_hash());
  ASSERT_EQ(*ptr, value);
}

TEST(HashValue, differ) {
  Hash lhs_value(test_hash);
  ASSERT_TRUE(lhs_value.equal(test_hash));

  Hash rhs_value(test_hash_differ);
  ASSERT_NE(lhs_value, rhs_value);
}

TEST(HashValue, empty_iterator) {
  Hash value;
  size_t count = 0;
  for (auto item : value) {
    count++;
  }
  ASSERT_EQ(count, value.size());
  LTVarIterator biter = value.begin();
  LTVarIterator eiter = value.end();
  ASSERT_EQ(biter, eiter);
}

TEST(HashValue, fill_iterator) {
  Hash value(test_hash);
  size_t count = 0;
  for (auto item : value) {
    count++;
  }
  ASSERT_EQ(count, value.size());
  LTVarIterator iter;
  iter = value.begin();
  ASSERT_EQ(iter.second(), test_hash_local[(std::string)iter.first()]);
}
