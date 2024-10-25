#ifndef TWBL_SRC_TWBL_TEEWORLDS_GAMECONTEXT_H
#define TWBL_SRC_TWBL_TEEWORLDS_GAMECONTEXT_H

#include <twbl/teeworlds/base/system.h>
#include <twbl/teeworlds/base/vmath.h>

#if __has_include(<game/server/gamecontext.h>)
#include <game/server/gamecontext.h>
#else

class CGameContext
{
public:
	void SendChat(int ClientId, int Team, const char *pText, int SpamProtectionClientId = -1, int VersionFlags = 0) { dbg_msg("chat", "%d %s", Team, pText); }
};

#endif

#endif
