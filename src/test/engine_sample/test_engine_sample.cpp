#include <cstdio>

#include <test/mock_callback_ctx.h>
#include <test/setup.h>
#include <test/twbl_assert.h>
#include <twbl/callback_ctx.h>
#include <twbl/state.h>
#include <twbl/teeworlds/character.h>
#include <twbl/teeworlds/player.h>
#include <twbl/types.h>

#include <bots/engine_sample/engine_sample.h>

using namespace TWBL;

static void TestBasic()
{
	InitTest("basic");

	CTwblPersistentState PersistentState;

	CCharacter BotChar;
	CPlayer BotPlayer;
	BotPlayer.m_pCharacter = &BotChar;
	CPlayer *apPlayers[MAX_CLIENTS] = {nullptr};
	apPlayers[0] = &BotPlayer;

	CServerBotStateIn State;
	State.m_GameTick = 1;
	State.m_ppPlayers = apPlayers;
	State.m_pCharacter = &BotChar;
	CMockCallbackCtx MockCallbackCtx;
	State.m_pCallbackCtx = &MockCallbackCtx;
	CServerBotStateOut Bot;
	Twbl_EngineSampleTick(&State, &Bot, &PersistentState, sizeof(PersistentState));

	EXPECT_EQ(Bot.m_Direction, 1);
	EXPECT_STREQ(Bot.m_apDirComments[0], "sample engine walk");
}

int main()
{
	TestBasic();
}
