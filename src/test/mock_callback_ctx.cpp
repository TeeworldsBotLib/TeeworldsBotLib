#include <twbl/callback_ctx.h>
#include <twbl/teeworlds/base/system.h>

#include "mock_callback_ctx.h"

void CMockCallbackCtx::SendChat(int Team, const char *pText)
{
	dbg_msg("chat", "%d:%d: %s", GetCid(), Team, pText);
}

void CMockCallbackCtx::Die()
{
	dbg_msg("game", "killed cid=%d", GetCid());
}

void CMockCallbackCtx::Emote(int Emote)
{
}
