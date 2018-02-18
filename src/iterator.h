#ifndef ITERATOR_H
#define ITERATOR_H

#include <map>
#include <memory>
#include <vector>

namespace Harmonix {

class LType;

typedef std::map<std::string, LType> LTypeHash;
typedef std::vector<LType> LTypeArray;

class LTypeIterator;

class VoidIterator {
  ;
  LTypeHash::iterator iterator_;

 protected:
  virtual bool equals(const VoidIterator& rhs) const = 0;
  virtual void increment(int delta) = 0;
  virtual bool is_hash() const { return false; }
  virtual bool is_array() const { return false; }
  friend class LTypeIterator;

 public:
  virtual ~VoidIterator() {}
  virtual LType first() = 0;
  virtual const LType& second() = 0;
};

class HashIterator : public VoidIterator {
  LTypeHash::const_iterator iterator_;

 protected:
  virtual bool equals(const VoidIterator& rhs) const;
  virtual void increment(int delta);
  virtual bool is_hash() const { return true; }

 public:
  HashIterator(LTypeHash::const_iterator iterator) : iterator_(iterator) {}
  virtual LType first();
  virtual const LType& second();
};

class ArrayIterator : public VoidIterator {
  size_t index_;
  LTypeArray::const_iterator iterator_;

 protected:
  virtual bool equals(const VoidIterator& rhs) const;
  virtual void increment(int delta);
  virtual bool is_array() const { return true; }

 public:
  ArrayIterator(size_t index, LTypeArray::const_iterator iterator)
      : index_(index), iterator_(iterator) {}
  virtual LType first();
  virtual const LType& second();
};

class LTypeIterator {
  std::unique_ptr<VoidIterator> state_;

 public:
  LTypeIterator();
  LTypeIterator(LTypeIterator&& rhs);
  LTypeIterator(VoidIterator* state);
  ~LTypeIterator();
  virtual LType first();
  virtual const LType& second();
  bool operator!=(const LTypeIterator& rhs) const;
  bool operator==(const LTypeIterator& rhs) const;
  LTypeIterator& operator++();
  const LType& operator*();
  LTypeIterator& operator=(LTypeIterator&& rhs);
};
}  // namespace Harmonix
#endif  // ITERATOR_H
