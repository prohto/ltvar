#include "ijson.h"
#include <iomanip>
#include "iterator.h"
#include "json.h"
#include "ltype.h"
#include "states/array.h"
#include "states/bool.h"
#include "states/double.h"
#include "states/hash.h"
#include "states/integer.h"
#include "states/string.h"
#include "states/void.h"

using namespace Harmonix;

void IJson::decode(LType& data) {
  JsonState json(*i_stream_);

  json.deserialize();
  if (!json.hasFailed()) {
    data = std::move(json.top());
  } else {
    lines_read_ = static_cast<size_t>(json.getCurrentLine());
    throw std::invalid_argument("json error");
  }
}
