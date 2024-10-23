#include <cstdio>
#include <shared/character.h>
#include <shared/player.h>
#include <shared/types.h>
#include <test/setup.h>
#include <test/twbl_assert.h>

#include <bots/follow/follow.h>

using namespace TWBL;

static void TestBasic()
{
	InitTest("basic");

	CCharacter HumanChar;
	HumanChar.m_Pos = vec2(0.0f, 0.0f);
	CPlayer HumanPlayer;
	HumanPlayer.m_pCharacter = &HumanChar;

	CCharacter BotChar;
	BotChar.m_Pos = vec2(4.0f * 32, 0.0f);
	CPlayer BotPlayer;
	BotPlayer.m_pCharacter = &BotChar;

	CPlayer *apPlayers[MAX_CLIENTS] = {nullptr};
	apPlayers[0] = &HumanPlayer;
	apPlayers[1] = &BotPlayer;

	CServerBotStateIn State;
	State.m_ppPlayers = apPlayers;
	State.m_pCharacter = &BotChar;

	CServerBotStateOut Bot;

	Twbl_FollowTick(&State, &Bot);
	EXPECT_EQ(Bot.m_Direction, -1);

	BotChar.m_Pos = vec2(-4.0f * 32, 0.0f);

	Twbl_FollowTick(&State, &Bot);
	EXPECT_EQ(Bot.m_Direction, 1);

	BotChar.m_Pos = vec2(1.0f * 32, 0.0f);

	Twbl_FollowTick(&State, &Bot);
	EXPECT_EQ(Bot.m_Direction, 0);
}

int main()
{
	TestBasic();
}
