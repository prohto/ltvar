#include "iterator.h"
#include "ltype.h"
#include "io/io.h"
#include "double.h"

using namespace Harmonix;

void Double::encode(Encoder& stream) const { stream.encode(this->value_); }
void Double::decode(Decoder& stream) { stream.decode(this->value_); }
