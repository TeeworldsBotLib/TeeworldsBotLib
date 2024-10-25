#include <twbl/teeworlds/gamecontext.h>

#include "ddnet_callback_ctx.h"

namespace TWBL {

CGameContext *CDDNetCallbackCtx::GameServer()
{
	return m_pGameServer;
}

void CDDNetCallbackCtx::SendChat(int ClientId, int Team, const char *pText)
{
	GameServer()->SendChat(ClientId, Team, pText);
}

void CDDNetCallbackCtx::Die(int ClientId)
{
	if(ClientId < 0 || ClientId >= MAX_CLIENTS)
		return;

	CPlayer *pPlayer = GameServer()->m_apPlayers[ClientId];
	if(!pPlayer)
		return;

	pPlayer->KillCharacter(WEAPON_SELF);
}

} // namespace TWBL
