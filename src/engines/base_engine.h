#ifndef TWBL_SRC_ENGINES_BASE_ENGINE_H
#define TWBL_SRC_ENGINES_BASE_ENGINE_H

#include <twbl/hotreload.h>
#include <twbl/teeworlds/base/color.h>
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

	ColorRGBA ColorRed() { return ColorRGBA(1, 0, 0, 0.6f); }
	ColorRGBA ColorGreen() { return ColorRGBA(0, 1, 0, 0.6f); }

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

	/// Returns true every time the server game tick reaches
	/// a multiple of the *Ticks* argument.
	///
	/// This can be used to schedule some actions that should happen
	/// in intervals.
	///
	/// But be careful! The bot library will be called multiple times
	/// per game tick most likely. So this will be true for multiple ticks in a row.
	/// this can be useful to properly send inputs because between game tick inputs don't work well
	/// anyways. But if you need some specific action to actually only happen once then
	/// checkout the LibTicksPassed() method
	bool GameTicksPassed(int Ticks);

	/// Returns true every time the library ticked a multiple of *Ticks* times
	/// this can be used to schedule a action in intervals.
	/// But be careful if you pick intervals lower than the server tick speed the event might be lost or overriden.
	/// If you need to be independent from the bot tick speed and do something tied to gameplay and inputs
	/// it is recommended to use GameTicksPassed() instead
	bool LibTicksPassed(int Ticks);

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
