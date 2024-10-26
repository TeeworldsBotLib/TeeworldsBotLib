#include <bots/base.h>

#include "base_engine.h"

namespace TWBL {

CBaseEngine::CBaseEngine(CBaseBot *pBaseBot) :
	m_pBaseBot(pBaseBot)
{
}

CBaseBot *CBaseEngine::Bot()
{
	return m_pBaseBot;
}

} // namespace TWBL
