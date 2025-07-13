#include <twbl/teeworlds/character.h>
#include <twbl/teeworlds/gamecontext.h>
#include <twbl/teeworlds/protocol.h>

#include "ddnet_callback_ctx.h"

namespace TWBL {

CGameContext *CDDNetCallbackCtx::GameServer()
{
	return m_pGameServer;
}

void CDDNetCallbackCtx::SendChat(int Team, const char *pText)
{
	int ClientId = GetCid();
	GameServer()->SendChat(ClientId, Team, pText);
}

void CDDNetCallbackCtx::Die()
{
	int ClientId = GetCid();
	if(ClientId < 0 || ClientId >= MAX_CLIENTS)
		return;

	CPlayer *pPlayer = GameServer()->m_apPlayers[ClientId];
	if(!pPlayer)
		return;

	if(pPlayer->GetCharacter())
		pPlayer->GetCharacter()->Die(pPlayer->GetCid(), WEAPON_SELF);
}

void CDDNetCallbackCtx::Emote(int Emoticon)
{
}

bool CDDNetCallbackCtx::IsFrozen(const CCharacter *pChr)
{
	// legacy deep is -1
	// nowerdays its a bool
	// this should be properly supported with
	// https://github.com/TeeworldsBotLib/TeeworldsBotLib/issues/6
	// then the line below should say IsDeepeFrozen(pChr) instead
	if(pChr->m_FreezeTime == -1)
		return true;
	return pChr->m_FreezeTime != 0;
}

} // namespace TWBL
