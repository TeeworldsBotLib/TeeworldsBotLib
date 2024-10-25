#include <cstdio>

#include <test/setup.h>
#include <test/twbl_assert.h>
#include <twbl/state.h>
#include <twbl/teeworlds/character.h>
#include <twbl/teeworlds/player.h>
#include <twbl/types.h>
#include <twbl/callback_ctx.h>
#include <test/mock_callback_ctx.h>

#include <bots/sample/sample.h>

using namespace TWBL;

static void TestPushStr()
{
	InitTest("push str");

	CServerBotStateOut Bot;

	EXPECT_EQ(sizeof(Bot.m_apDirComments) / sizeof(const char *), TWBL_MAX_LOG_LEN);

	EXPECT_STREQ(Bot.m_apDirComments[0], "");
	EXPECT_STREQ(Bot.m_apDirComments[1], "");

	PushRingStr(Bot.m_apDirComments, "hello", sizeof(Bot.m_apDirComments) / sizeof(const char *));
	EXPECT_STREQ(Bot.m_apDirComments[0], "hello");
	EXPECT_STREQ(Bot.m_apDirComments[1], "");

	PushRingStr(Bot.m_apDirComments, "world", sizeof(Bot.m_apDirComments) / sizeof(const char *));
	EXPECT_STREQ(Bot.m_apDirComments[0], "world");
	EXPECT_STREQ(Bot.m_apDirComments[1], "hello");

	PushRingStr(Bot.m_apDirComments, "", sizeof(Bot.m_apDirComments) / sizeof(const char *));
	EXPECT_STREQ(Bot.m_apDirComments[0], "");
	EXPECT_STREQ(Bot.m_apDirComments[1], "world");
	EXPECT_STREQ(Bot.m_apDirComments[2], "hello");

	PushRingStr(Bot.m_apDirComments, "foo", sizeof(Bot.m_apDirComments) / sizeof(const char *));
	EXPECT_STREQ(Bot.m_apDirComments[0], "foo");
	EXPECT_STREQ(Bot.m_apDirComments[1], "");
	EXPECT_STREQ(Bot.m_apDirComments[2], "world");
	EXPECT_STREQ(Bot.m_apDirComments[3], "hello");

	for(int i = 0; i < TWBL_MAX_LOG_LEN * 2; i++)
		PushRingStr(Bot.m_apDirComments, "max*2", sizeof(Bot.m_apDirComments) / sizeof(const char *));

	EXPECT_STREQ(Bot.m_apDirComments[0], "max*2");
	EXPECT_STREQ(Bot.m_apDirComments[TWBL_MAX_LOG_LEN - 1], "max*2");
}

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
	Twbl_SampleTick(&State, &Bot, &PersistentState, sizeof(PersistentState));

	EXPECT_EQ(Bot.m_Direction, 1);

	EXPECT_STREQ(Bot.m_apDirComments[0], "go right till 10");
	EXPECT_STREQ(Bot.m_apDirComments[1], "world");
	EXPECT_STREQ(Bot.m_apDirComments[2], "hello");
	EXPECT_STREQ(Bot.m_apDirComments[3], "yolo");
	EXPECT_STREQ(Bot.m_apDirFunctions[0], "Tick");
	EXPECT_EQ(Bot.m_aDirLines[0], 34);

	EXPECT_STREQ(Bot.m_apAimComments[0], "right");
	EXPECT_EQ(Bot.m_TargetX, 100);
	EXPECT_EQ(Bot.m_TargetY, 1);

	EXPECT_STREQ(Bot.m_apHookComments[0], "on");
	EXPECT_EQ(Bot.m_Hook, 1);

	BotChar.m_Pos.x = 20 * 32;
	Twbl_SampleTick(&State, &Bot, &PersistentState, sizeof(PersistentState));
	EXPECT_STREQ(Bot.m_apDirComments[0], "go left till 10");
}

int main()
{
	TestPushStr();
	TestBasic();
}
