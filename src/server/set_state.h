#ifndef TWBL_SRC_SERVER_SET_STATE_H
#define TWBL_SRC_SERVER_SET_STATE_H

// has to be included by the server
// make sure character.h is included first

#include <twbl/teeworlds/character.h>
#include <twbl/types.h>

namespace TWBL {

void CallbackDie(CCharacter *pChr)
{
	pChr->Die(pChr->GetPlayer()->GetCid(), WEAPON_SELF);
}

void SetState(CCharacter *pChr, CServerBotStateIn *pState)
{
	pState->m_pCharacter = pChr;
	pState->m_ClientId = pChr->GetPlayer()->GetCid();
	pState->m_pfnCallbackDie = CallbackDie;
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
