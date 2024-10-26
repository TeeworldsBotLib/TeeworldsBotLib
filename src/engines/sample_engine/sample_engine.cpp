#include <bots/base.h>

#include "sample_engine.h"

#include <engines/def_macros.h>

namespace TWBL {

void CSampleEngine::WalkRight()
{
	Right("sample engine walk");
}

} // namespace TWBL

#include <engines/undef_macros.h>
