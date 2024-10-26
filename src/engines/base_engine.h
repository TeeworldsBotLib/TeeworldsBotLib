#ifndef TWBL_SRC_ENGINES_BASE_ENGINE_H
#define TWBL_SRC_ENGINES_BASE_ENGINE_H

#include <twbl/hotreload.h>
#include <twbl/teeworlds/base/vmath.h>
#include <twbl/teeworlds/character.h>

namespace TWBL {

class CBaseBot;

class CBaseEngine
{
	CBaseBot *m_pBaseBot;

protected:
	CBaseBot *Bot();

	const CCollision *Collision();
	CCharacter *Character(int ClientId = -1);
	CPlayer *GetPlayer(int ClientId = -1);
	CCharacter *ClosestCharacter(vec2 Pos, const CCharacter *pNotThis);

	vec2 GetPos();
	vec2 GetVel();
	bool IsGrounded();
	int FreezeTime();
	bool IsFrozen(CCharacter *pChr = nullptr);
	bool TicksPassed(int Ticks);
	int GameTick();

public:
	CBaseEngine(CBaseBot *pBaseBot);
};

} // namespace TWBL

#endif
