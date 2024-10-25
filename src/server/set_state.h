#ifndef TWBL_SRC_SERVER_SET_STATE_H
#define TWBL_SRC_SERVER_SET_STATE_H

// has to be included by the server
// make sure character.h is included first

#include <server/ddnet_callback_ctx.h>
#include <twbl/callback_ctx.h>
#include <twbl/teeworlds/character.h>
#include <twbl/types.h>

namespace TWBL {

void SetState(CCharacter *pChr, CServerBotStateIn *pState)
{
	CDDNetCallbackCtx CallbackCtx;
	CallbackCtx.m_pGameServer = pChr->GameServer();

	pState->m_GameTick = pChr->GameServer()->Server()->Tick();
	pState->m_pCharacter = pChr;
	pState->m_ClientId = pChr->GetPlayer()->GetCid();
	pState->m_pCallbackCtx = &CallbackCtx;
}

} // namespace TWBL

// Sets CNetObj_PlayerInput based on CServerBotStateIn
//
// @param input CNetObj_PlayerInput is the variable of a character that will be set
// @param state CServerBotStateIn is the state computed by twbl
#define TWBL_SET_INPUT(input, state) \
	input.m_Direction = Bot.m_Direction; \
	input.m_TargetX = Bot.m_TargetX; \
	input.m_TargetY = Bot.m_TargetY; \
	input.m_Jump = Bot.m_Jump; \
	if(Bot.m_Fire) \
	{ \
		input.m_Fire++; \
	} \
	input.m_Hook = Bot.m_Hook; \
	input.m_PlayerFlags = Bot.m_PlayerFlags; \
	input.m_WantedWeapon = Bot.m_Weapon;

#endif
