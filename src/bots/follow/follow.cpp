#include <cstdio>
#include <cstdlib>

#include <bots/base.h>
#include <shared/character.h>
#include <shared/player.h>
#include <shared/types.h>

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
void Twbl_FollowTickHot(const CServerBotStateIn *pStateIn, CServerBotStateOut *pStateOut)
{
	TWBL::CFollowBot Bot(pStateIn, pStateOut);
	Bot.Tick();
}
#endif

void Twbl_FollowTick(const CServerBotStateIn *pStateIn, CServerBotStateOut *pStateOut)
{
	TWBL::CFollowBot Bot(pStateIn, pStateOut);
	Bot.Tick();
}
}

#include <bots/undef_macros.h>
