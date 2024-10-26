#ifndef TWBL_SRC_BOTS_BASE_H
#define TWBL_SRC_BOTS_BASE_H

#include <cstddef>

#include <twbl/hotreload.h>
#include <twbl/teeworlds/base/system.h>
#include <twbl/teeworlds/base/vmath.h>
#include <twbl/teeworlds/character.h>
#include <twbl/teeworlds/player.h>

#include <twbl/state.h>
#include <twbl/types.h>

namespace TWBL {

// 0 is newest
// MaxEntries-1 is oldest
void PushRingStr(const char **ppBuffer, const char *pNew, size_t MaxEntries);

// 0 is newest
// MaxEntries-1 is oldest
void PushRingInt(int *pBuffer, int New, size_t MaxEntries);

class CBaseBot
{
public:
	const CServerBotStateIn *m_pStateIn;
	CServerBotStateOut *m_pStateOut;
	CTwblPersistentState *m_pState;

	CBaseBot(
		const CServerBotStateIn *pStateIn,
		CServerBotStateOut *pStateOut,
		CTwblPersistentState *pState,
		size_t SizeOfState)
	{
		dbg_assert(SizeOfState >= MIN_TWBL_STATE_SIZE, "persistent state buffer is too small");
		dbg_assert(pStateIn->m_GameTick > 0, "game tick is too low. did you forget to set it?");

		m_pStateIn = pStateIn;
		m_pStateOut = pStateOut;
		m_pState = pState;

		// the constructor should be called every tick
		m_pState->m_TwblTicks++;
	}

	const CCollision *Collision() const { return m_pStateIn->m_pCollision; }
	CCharacter *Character(int ClientId = -1);
	CPlayer *GetPlayer(int ClientId = -1);
	CCharacter *ClosestCharacter(vec2 Pos, const CCharacter *pNotThis);

	vec2 GetPos() { return Character()->GetPos(); }
	vec2 GetVel() { return Character()->Core()->m_Vel; }
	bool IsGrounded() { return Character()->IsGrounded(); }
	int FreezeTime() { return Character()->m_FreezeTime; }
	bool IsFrozen(CCharacter *pChr = nullptr);
	bool TicksPassed(int Ticks) { return m_pStateIn->m_GameTick % Ticks == 0; }
	int GameTick() { return m_pStateIn->m_GameTick; }

	// there is only raw chat and no macro
	// because tracking chat is rarely needed
	// it traces it self
	void _SendChatRaw(int Team, const char *pText);
	void SendChat(int Team, const char *pText) { _SendChatRaw(Team, pText); }

	// it is recommended to use the macros instead

	void _DieRaw() const;
	void _Die(const char *pComment) const;

	void _EmoteRaw(int Emoticon);
	void _Emote(int Emoticon, const char *pComment, const char *pFunction, const char *pFile, int Line);

	/* Aim(x, y)
	 *
	 * Aim with targets using coordinates
	 * relative to the the tee
	 */
	void _AimRaw(int TargetX, int TargetY) const;
	void _Aim(int TargetX, int TargetY, const char *pComment, const char *pFunction, const char *pFile, int Line) const;

	/* AimPos(x, y)
	 *
	 * Aim with targets using world coordinates
	 */
	void _AimPosRaw(int TargetX, int TargetY);
	void _AimPos(int TargetX, int TargetY, const char *pComment, const char *pFunction, const char *pFile, int Line);

	void _SetDirectionRaw(int Dir) const;
	void _SetDirection(int Dir, const char *pComment, const char *pFunction, const char *pFile, int Line) const;

	void _HookRaw(int Value) const;
	void _Hook(int Value, const char *pComment, const char *pFunction, const char *pFile, int Line) const;

	void _JumpRaw(int Value) const;
	void _Jump(int Value, const char *pComment, const char *pFunction, const char *pFile, int Line) const;

	void _FireRaw(int Value) const;
	void _Fire(int Value, const char *pComment, const char *pFunction, const char *pFile, int Line) const;

	void _SetWeaponRaw(int Value) const;
	void _SetWeapon(int Value, const char *pComment, const char *pFunction, const char *pFile, int Line) const;

	void Tick(){};
};

} // namespace TWBL

extern "C" {

const char *TwblInfo();
const char *TwblTicks();
}

#endif
