#include <bots/base.h>
#include <twbl/teeworlds/collision.h>

#include "base_engine.h"

namespace TWBL {

/*   _
 *  | |__   __ _ ___  ___
 *  | '_ \ / _` / __|/ _ \
 *  | |_) | (_| \__ \  __/
 *  |_.__/ \__,_|___/\___|
 */

CBaseEngine::CBaseEngine(CBaseBot *pBaseBot) :
	m_pBaseBot(pBaseBot)
{
}

CBaseBot *CBaseEngine::Bot()
{
	return m_pBaseBot;
}

const CCollision *CBaseEngine::Collision()
{
	return Bot()->Collision();
}

CCharacter *CBaseEngine::Character(int ClientId)
{
	return Bot()->Character(ClientId);
}

int CBaseEngine::GetTile(vec2 Pos)
{
	return Collision()->GetTileIndex(Collision()->GetPureMapIndex(Pos));
}

CPlayer *CBaseEngine::GetPlayer(int ClientId)
{
	return Bot()->GetPlayer(ClientId);
}

CCharacter *CBaseEngine::ClosestCharacter(vec2 Pos, const CCharacter *pNotThis)
{
	return Bot()->ClosestCharacter(Pos, pNotThis);
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

/*                  _
 *    ___ _   _ ___| |_ ___  _ __ ___
 *   / __| | | / __| __/ _ \| '_ ` _ \
 *  | (__| |_| \__ \ || (_) | | | | | |
 *   \___|\__,_|___/\__\___/|_| |_| |_|
 */

} // namespace TWBL
