#include "ijson.h"
#include <iomanip>
#include "json.h"
#include "ltvar.h"


void IJson::decode(LTVar& data) {
  JsonState json(*i_stream_);

  json.deserialize();
  if (!json.hasFailed()) {
    data = std::move(json.top());
  } else {
    lines_read_ = static_cast<size_t>(json.getCurrentLine());
    throw std::invalid_argument("json error");
  }
}

void operator>>( std::string lhs, LTVar& rhs ){
  IJson ijson( rhs );
	std::istringstream is( lhs );
	is >> ijson;
}
