#include "ojson.h"
#include <iomanip>


//std::ostream& operator<<(std::ostream& ostream, const std::string& str) {
//  ostream.write(str.c_str(), str.length());
//  return ostream;
//}

void OJson::encode(const LTVar& value) { serializeFrom(value); }

void OJson::encode(const Array& value) {
  (*o_stream_) << "[";
  size_t idx = 0;
  for (auto iter : value) {
    if (idx > 0) {
      (*o_stream_) << ',';
    }
    encode(iter);
    idx++;
  }
  (*o_stream_) << "]";
}

void OJson::encode(const bool& value) {
  if (value)
    (*o_stream_) << "true";
  else
    (*o_stream_) << "false";
}

void OJson::encode(const double& value) {
  (*o_stream_) << std::setprecision(10) << value;
}

void OJson::encode(const Hash& value) {
  (*o_stream_) << "{";
  size_t idx = 0;
  for (LTVarIterator iter = value.begin(); iter != value.end(); ++iter) {
    if (idx > 0) {
      (*o_stream_) << ',';
    }
    encode(iter.first());
    (*o_stream_) << ":";
    encode(iter.second());
    idx++;
  }
  (*o_stream_) << "}";
}

void OJson::encode(const int& value) { (*o_stream_) << value; }

void OJson::encode(const std::string& value) {
  (*o_stream_) << "\"";
  for (size_t curr = 0; curr < value.size(); curr++) {
    char c = value.c_str()[curr];
    switch (c) {
      case '"':
        (*o_stream_) << "\\\"";
        break;
      case '\\':
        if (value.c_str()[curr + 1] == 'u') {
          (*o_stream_) << "\\";
        } else {
          (*o_stream_) << "\\\\";
        }
        break;
      case '/':
        (*o_stream_) << "\\/";
        break;
      case '\b':
        (*o_stream_) << "\\b";
        break;
      case '\f':
        (*o_stream_) << "\\f";
        break;
      case '\n':
        (*o_stream_) << "\\n";
        break;
      case '\r':
        (*o_stream_) << "\\r";
        break;
      case '\t':
        (*o_stream_) << "\\t";
        break;
      default:
        (*o_stream_) << c;
    }
  }
  (*o_stream_) << "\"";
}

void OJson::encode() { (*o_stream_) << "null"; }
