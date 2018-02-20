#ifndef OJSONPRETTY_H
#define OJSONPRETTY_H

#include <sstream>
#include "ojson.h"


class OJsonPretty : public OJson {
 private:
  size_t level_;
  uint8_t new_line_;
  uint8_t tabs_;
  uint8_t space_;
  size_t lines_;
  virtual void encode(const Array& value);
  virtual void encode(const Hash& value);

 public:
  OJsonPretty(LTVar& data)
      : OJson(data),
        level_(0),
        new_line_(0),
        tabs_(0),
        space_(0),
        lines_(0) {}
  virtual ~OJsonPretty() {}
  void setPrettyPrint() {
    new_line_ = 1;
    tabs_ = 2;
    space_ = 1;
  }
  void clearPrettyPrint() {
    new_line_ = 0;
    tabs_ = 0;
    space_ = 0;
  }
};

#endif  // OJSONPRETTY_H
