#include "iterator.h"
#include "ltype.h"
#include "io/io.h"
#include "integer.h"

using namespace Harmonix;

void Integer::encode(Encoder& stream) const { stream.encode(this->value_); }
void Integer::decode(Decoder& stream) { stream.decode(this->value_); }
