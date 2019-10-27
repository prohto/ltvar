#ifndef ITERATOR_H
#define ITERATOR_H

#include <map>
#include <memory>
#include <vector>

class LTVar;

typedef std::map<std::string, LTVar> LTVarHash;
typedef std::vector<LTVar> LTVarArray;

class LTVarIterator;

class VoidIterator {
  LTVarHash::iterator iterator_;

 protected:
  virtual bool equals(const VoidIterator& rhs) const = 0;
  virtual void increment(int delta) = 0;
  virtual bool is_hash() const { return false; }
  virtual bool is_array() const { return false; }
  friend class LTVarIterator;

 public:
  virtual ~VoidIterator() {}
  virtual LTVar first() = 0;
  virtual const LTVar& second() = 0;
};

class HashIterator : public VoidIterator {
  LTVarHash::const_iterator iterator_;

 protected:
  virtual bool equals(const VoidIterator& rhs) const override;
  virtual void increment(int delta) override;
  virtual bool is_hash() const override { return true; }

 public:
  explicit HashIterator(LTVarHash::const_iterator iterator)
      : iterator_(iterator) {}
  virtual LTVar first() override;
  virtual const LTVar& second() override;
};

class ArrayIterator : public VoidIterator {
  size_t index_;
  LTVarArray::const_iterator iterator_;

 protected:
  virtual bool equals(const VoidIterator& rhs) const override;
  virtual void increment(int delta) override;
  virtual bool is_array() const override { return true; }

 public:
  ArrayIterator(size_t index, LTVarArray::const_iterator iterator)
      : index_(index), iterator_(iterator) {}
  virtual LTVar first() override;
  virtual const LTVar& second() override;
};

class LTVarIterator {
  std::unique_ptr<VoidIterator> state_;

 public:
  LTVarIterator();
  LTVarIterator(LTVarIterator&& rhs);
  explicit LTVarIterator(VoidIterator* state);
  virtual ~LTVarIterator();
  virtual LTVar first();
  virtual const LTVar& second();
  bool operator!=(const LTVarIterator& rhs) const;
  bool operator==(const LTVarIterator& rhs) const;
  LTVarIterator& operator++();
  LTVarIterator& operator++(int delta);
  const LTVar& operator*();
  LTVarIterator& operator=(LTVarIterator&& rhs);
};
#endif  // ITERATOR_H
