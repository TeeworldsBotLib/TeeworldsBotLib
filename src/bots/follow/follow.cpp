#include <cstddef>
#include <cstdio>
#include <cstdlib>

#include <bots/base.h>

#include <twbl/state.h>
#include <twbl/teeworlds/base/system.h>
#include <twbl/teeworlds/character.h>
#include <twbl/teeworlds/player.h>
#include <twbl/types.h>

#include <bots/follow/follow.h>

#include <bots/def_macros.h>

namespace TWBL {

void CFollowBot::Tick()
{
	const CCharacter *pChr = ClosestCharacter(GetPos(), Character());
	if(!pChr)
		return;

	int WalkDir = 0;
	if(pChr->GetPos().x < GetPos().x - 2 * 32)
		WalkDir = -1;
	if(pChr->GetPos().x > GetPos().x + 2 * 32)
		WalkDir = 1;

	int Tile = Collision()->GetTile((int)(GetPos().x + 32 * WalkDir), (int)(GetPos().y));
	if(Tile == 1)
		Jump(1, "jump over obstacle");
	SetDirection(WalkDir, "walk towards closest player");

	Aim(0, 10, "");
	if(IsGrounded())
		Aim(0, -10, "");
}

} // namespace TWBL

extern "C" {

#ifdef TWBL_SHARED_OBJECT
void Twbl_FollowTickHot(const CServerBotStateIn *pStateIn, CServerBotStateOut *pStateOut, CTwblPersistentState *pState, size_t SizeOfState)
{
	dbg_assert(SizeOfState == MIN_TWBL_STATE_SIZE, "persistent state buffer does not match size");

	TWBL::CFollowBot Bot(pStateIn, pStateOut, pState, SizeOfState);
	Bot.Tick();
}
#endif

void Twbl_FollowTick(const CServerBotStateIn *pStateIn, CServerBotStateOut *pStateOut, CTwblPersistentState *pState, size_t SizeOfState)
{
	TWBL::CFollowBot Bot(pStateIn, pStateOut, pState, SizeOfState);
	Bot.Tick();
}
}

#include <bots/undef_macros.h>
