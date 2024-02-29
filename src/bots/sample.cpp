#include <cstdio>
#include <cstdlib>

#include <bots/base.h>
#include <shared/character.h>
#include <shared/player.h>
#include <shared/types.h>

#include <bots/sample.h>

#include <bots/def_macros.h>

namespace TWBL {

void CSampleBot::Tick()
{
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
void Twbl_SampleTickHot(const CServerBotStateIn *pStateIn, CServerBotStateOut *pStateOut)
{
	TWBL::CSampleBot Bot(pStateIn, pStateOut);
	Bot.Tick();
}
#endif

void Twbl_SampleTick(const CServerBotStateIn *pStateIn, CServerBotStateOut *pStateOut)
{
	TWBL::CSampleBot Bot(pStateIn, pStateOut);
	Bot.Tick();
}
}

#include <bots/undef_macros.h>
