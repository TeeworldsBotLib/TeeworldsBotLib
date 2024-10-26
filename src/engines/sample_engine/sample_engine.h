#ifndef TWBL_SRC_ENGINES_SAMPLE_ENGINE_H
#define TWBL_SRC_ENGINES_SAMPLE_ENGINE_H

#include <engines/base_engine.h>

namespace TWBL {

class TWBL_HOT CSampleEngine : public CBaseEngine
{
public:
	using CBaseEngine::CBaseEngine;

	void WalkRight();
};

} // namespace TWBL

#endif
