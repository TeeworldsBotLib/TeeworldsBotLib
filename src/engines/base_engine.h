#ifndef TWBL_SRC_ENGINES_BASE_ENGINE_H
#define TWBL_SRC_ENGINES_BASE_ENGINE_H

#include <twbl/hotreload.h>
#include <twbl/teeworlds/base/vmath.h>
#include <twbl/teeworlds/character.h>

namespace TWBL {

class CBaseBot;

class CBaseEngine
{
	/*   _
	 *  | |__   __ _ ___  ___
	 *  | '_ \ / _` / __|/ _ \
	 *  | |_) | (_| \__ \  __/
	 *  |_.__/ \__,_|___/\___|
	 */

	CBaseBot *m_pBaseBot;

protected:
	CBaseBot *Bot();

	vec4 ColorRed() { return vec4(1, 0, 0, 0.6f); }
	vec4 ColorGreen() { return vec4(0, 1, 0, 0.6f); }

	const CCollision *Collision();
	CCharacter *Character(int ClientId = -1);
	CPlayer *GetPlayer(int ClientId = -1);
	CCharacter *ClosestCharacter(vec2 Pos, const CCharacter *pNotThis);

	int GetTile(vec2 Pos);

	vec2 GetPos();
	vec2 GetVel();
	bool IsGrounded();
	int FreezeTime();
	bool IsFrozen(CCharacter *pChr = nullptr);
	bool TicksPassed(int Ticks);
	int GameTick();

public:
	CBaseEngine(CBaseBot *pBaseBot);

	/*                  _
	 *    ___ _   _ ___| |_ ___  _ __ ___
	 *   / __| | | / __| __/ _ \| '_ ` _ \
	 *  | (__| |_| \__ \ || (_) | | | | | |
	 *   \___|\__,_|___/\__\___/|_| |_| |_|
	 */
};

} // namespace TWBL

#endif
