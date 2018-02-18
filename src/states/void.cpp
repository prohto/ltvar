#include "iterator.h"
#include "ltype.h"
#include "io/io.h"
#include "void.h"

using namespace Harmonix;

void Void::encode(Encoder& output) const { output.encode(); }
void Void::decode(Decoder& input) { input.decode(); }
