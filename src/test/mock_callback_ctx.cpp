#include <twbl/callback_ctx.h>
#include <twbl/teeworlds/base/system.h>

#include "mock_callback_ctx.h"

void CMockCallbackCtx::SendChat(int ClientId, int Team, const char *pText)
{
	dbg_msg("chat", "%d:%d: %s", ClientId, Team, pText);
}

void CMockCallbackCtx::Die(int ClientId)
{
	dbg_msg("game", "killed cid=%d", ClientId);
}
