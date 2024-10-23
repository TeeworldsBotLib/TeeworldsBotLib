#ifndef TWBL_SRC_BOTS_FOLLOW_FOLLOW_H
#define TWBL_SRC_BOTS_FOLLOW_FOLLOW_H

#include <bots/base.h>
#include <twbl/types.h>

namespace TWBL {

class TWBL_HOT CFollowBot : public CBaseBot
{
public:
	CFollowBot(const CServerBotStateIn *pStateIn, CServerBotStateOut *pStateOut) :
		CBaseBot(pStateIn, pStateOut)
	{
	}

	void Tick();
};

} // namespace TWBL

extern "C" {

#ifdef TWBL_SHARED_OBJECT
void Twbl_FollowTickHot(const CServerBotStateIn *pStateIn, CServerBotStateOut *pStateOut);
#endif

void Twbl_FollowTick(const CServerBotStateIn *pStateIn, CServerBotStateOut *pStateOut);
}

#endif
