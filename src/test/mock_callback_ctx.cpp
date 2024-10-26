#include <twbl/callback_ctx.h>
#include <twbl/teeworlds/base/system.h>

#include "mock_callback_ctx.h"

/*   _
 *  | |__   __ _ ___  ___
 *  | '_ \ / _` / __|/ _ \
 *  | |_) | (_| \__ \  __/
 *  |_.__/ \__,_|___/\___|
 */

void CMockCallbackCtx::SendChat(int Team, const char *pText)
{
	dbg_msg("chat", "%d:%d: %s", GetCid(), Team, pText);
}

void CMockCallbackCtx::Die()
{
	dbg_msg("game", "killed cid=%d", GetCid());
}

void CMockCallbackCtx::Emote(int Emoticon)
{
}

/*                  _
 *    ___ _   _ ___| |_ ___  _ __ ___
 *   / __| | | / __| __/ _ \| '_ ` _ \
 *  | (__| |_| \__ \ || (_) | | | | | |
 *   \___|\__,_|___/\__\___/|_| |_| |_|
 */
