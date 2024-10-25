#include <cstddef>
#include <cstdio>
#include <cstdlib>

#include <bots/base.h>
#include <twbl/state.h>
#include <twbl/teeworlds/character.h>
#include <twbl/teeworlds/player.h>
#include <twbl/teeworlds/protocol.h>
#include <twbl/types.h>

#include <bots/sample/sample.h>

#include <bots/def_macros.h>

namespace TWBL {

void CSampleBot::Tick()
{
	SendChat(0, "hello world");
	SetWeapon(WEAPON_HAMMER, "hammer time");

	Right("yolo");
	Left("hello");
	Right("world");

	Aim(10, -100, "up");
	Aim(100, 1, "right");

	Hook(0, "off");
	Hook(1, "on");

	if(GetPos().x < 10 * 32)
		Right("go right till 10");
	else
		Left("go left till 10");

	int Tile = Collision()->GetTile((int)(GetPos().x), (int)(GetPos().y) + 32);
	printf("bot at %d/%d currently walking on tile %d\n", (int)(GetPos().x / 32), (int)(GetPos().y / 32), Tile);

	for(int i = 0; i < MAX_CLIENTS; i++)
	{
		CPlayer *pPlayer = GetPlayer(i);
		if(!pPlayer)
			continue;
		CCharacter *pChr = pPlayer->GetCharacter();
		if(!pChr)
			continue;

		printf("player cid=%d at %d/%d\n", pPlayer->GetCid(), (int)(pChr->GetPos().x / 32), (int)(pChr->GetPos().y / 32));
	}
}

} // namespace TWBL

extern "C" {

#ifdef TWBL_SHARED_OBJECT
void Twbl_SampleTickHot(const CServerBotStateIn *pStateIn, CServerBotStateOut *pStateOut, CTwblPersistentState *pState, size_t SizeOfState)
{
	dbg_assert(SizeOfState == MIN_TWBL_STATE_SIZE, "persistent state buffer does not match size");

	TWBL::CSampleBot Bot(pStateIn, pStateOut, pState, SizeOfState);
	Bot.Tick();
}
#endif

void Twbl_SampleTick(const CServerBotStateIn *pStateIn, CServerBotStateOut *pStateOut, CTwblPersistentState *pState, size_t SizeOfState)
{
	TWBL::CSampleBot Bot(pStateIn, pStateOut, pState, SizeOfState);
	Bot.Tick();
}
}

#include <bots/undef_macros.h>
