#ifndef TWBL_SRC_BOTS_SAMPLE_H
#define TWBL_SRC_BOTS_SAMPLE_H

#include <bots/base.h>
#include <shared/types.h>

namespace TWBL {

class TWBL_HOT CSampleBot : public CBaseBot
{
public:
	CSampleBot(const CServerBotStateIn *pStateIn, CServerBotStateOut *pStateOut) :
		CBaseBot(pStateIn, pStateOut)
	{
	}

	void Tick();
};

} // namespace TWBL

extern "C" {

#ifdef TWBL_SHARED_OBJECT
void Twbl_SampleTickHot(const CServerBotStateIn *pStateIn, CServerBotStateOut *pStateOut);
#endif

void Twbl_SampleTick(const CServerBotStateIn *pStateIn, CServerBotStateOut *pStateOut);
}

#endif
