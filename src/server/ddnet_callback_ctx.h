#ifndef TWBL_SRC_SERVER_DDNET_CALLBACK_CTX_H
#define TWBL_SRC_SERVER_DDNET_CALLBACK_CTX_H

#include <twbl/callback_ctx.h>

class CGameContext;

namespace TWBL {

class CDDNetCallbackCtx : public CCallbackCtx
{
public:
	CGameContext *m_pGameServer = nullptr;
	CGameContext *GameServer();

	void SendChat(int Team, const char *pText) override;
	void Die() override;
	void Emote(int Emote) override;
};

} // namespace TWBL

#endif
