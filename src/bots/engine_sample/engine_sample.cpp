#include "engine_sample.h"

#include <bots/def_macros.h>

namespace TWBL {

void CEngineSampleBot::Tick()
{
	m_SampleEngine.WalkRight();
}

} // namespace TWBL

extern "C" {

#ifdef TWBL_SHARED_OBJECT
void Twbl_EngineSampleTickHot(const CServerBotStateIn *pStateIn, CServerBotStateOut *pStateOut, CTwblPersistentState *pState, size_t SizeOfState)
{
	dbg_assert(SizeOfState == MIN_TWBL_STATE_SIZE, "persistent state buffer does not match size");

	TWBL::CEngineSampleBot Bot(pStateIn, pStateOut, pState, SizeOfState);
	Bot.Tick();
}
#endif

void Twbl_EngineSampleTick(const CServerBotStateIn *pStateIn, CServerBotStateOut *pStateOut, CTwblPersistentState *pState, size_t SizeOfState)
{
	TWBL::CEngineSampleBot Bot(pStateIn, pStateOut, pState, SizeOfState);
	Bot.Tick();
}
}

#include <bots/undef_macros.h>
