#include <twbl/teeworlds/gamecontext.h>

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

	pPlayer->KillCharacter(WEAPON_SELF);
}

void CDDNetCallbackCtx::Emote(int Emoticon)
{
}

} // namespace TWBL
