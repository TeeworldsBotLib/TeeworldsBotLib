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

vec2 CBaseEngine::GetPos()
{
	return Bot()->GetPos();
}

vec2 CBaseEngine::GetVel()
{
	return Bot()->GetVel();
}

bool CBaseEngine::IsGrounded()
{
	return Bot()->IsGrounded();
}

int CBaseEngine::FreezeTime()
{
	return Bot()->FreezeTime();
}

bool CBaseEngine::IsFrozen(CCharacter *pChr)
{
	return Bot()->IsFrozen(pChr);
}

bool CBaseEngine::TicksPassed(int Ticks)
{
	return Bot()->TicksPassed(Ticks);
}

int CBaseEngine::GameTick()
{
	return Bot()->GameTick();
}

} // namespace TWBL
