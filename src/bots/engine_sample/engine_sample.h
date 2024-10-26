#ifndef TWBL_SRC_BOTS_ENGINE_SAMPLE_ENGINE_SAMPLE_H
#define TWBL_SRC_BOTS_ENGINE_SAMPLE_ENGINE_SAMPLE_H

#include <bots/base.h>
#include <engines/sample_engine/sample_engine.h>
#include <twbl/state.h>
#include <twbl/types.h>

#include <cstddef>

namespace TWBL {

class TWBL_HOT CEngineSampleBot : public CBaseBot
{
public:
	CEngineSampleBot(
		const CServerBotStateIn *pStateIn,
		CServerBotStateOut *pStateOut,
		CTwblPersistentState *pState,
		size_t SizeOfState) :
		CBaseBot(pStateIn, pStateOut, pState, SizeOfState),
		m_SampleEngine(this)
	{
	}

	CSampleEngine m_SampleEngine;

	void Tick();
};

} // namespace TWBL

extern "C" {

#ifdef TWBL_SHARED_OBJECT
void Twbl_EngineSampleTickHot(const CServerBotStateIn *pStateIn, CServerBotStateOut *pStateOut, CTwblPersistentState *pState, size_t SizeOfState);
#endif

void Twbl_EngineSampleTick(const CServerBotStateIn *pStateIn, CServerBotStateOut *pStateOut, CTwblPersistentState *pState, size_t SizeOfState);
}

#endif
