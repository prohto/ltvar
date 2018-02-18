#include "iterator.h"
#include "ltype.h"
#include "io/io.h"
#include "string.h"

using namespace Harmonix;

void String::encode(Encoder& stream) const { stream.encode(this->value_); }
void String::decode(Decoder& stream) { stream.decode(this->value_); }
