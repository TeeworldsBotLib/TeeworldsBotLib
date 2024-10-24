#ifndef TWBL_SRC_BOTS_SAMPLE_SAMPLE_H
#define TWBL_SRC_BOTS_SAMPLE_SAMPLE_H

#include <bots/base.h>
#include <twbl/state.h>
#include <twbl/types.h>

#include <cstddef>

namespace TWBL {

class TWBL_HOT CSampleBot : public CBaseBot
{
public:
	CSampleBot(
		const CServerBotStateIn *pStateIn,
		CServerBotStateOut *pStateOut,
		CTwblPersistentState *pState,
		size_t SizeOfState) :
		CBaseBot(pStateIn, pStateOut, pState, SizeOfState)
	{
	}

	void Tick();
};

} // namespace TWBL

extern "C" {

#ifdef TWBL_SHARED_OBJECT
void Twbl_SampleTickHot(const CServerBotStateIn *pStateIn, CServerBotStateOut *pStateOut, CTwblPersistentState *pState, size_t SizeOfState);
#endif

void Twbl_SampleTick(const CServerBotStateIn *pStateIn, CServerBotStateOut *pStateOut, CTwblPersistentState *pState, size_t SizeOfState);
}

#endif
