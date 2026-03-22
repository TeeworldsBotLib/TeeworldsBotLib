#if __has_include(<game/server/entities/character.h>)
#include <engine/shared/protocol.h>
#include <game/server/entities/character.h>
#include <game/server/player.h>
#else

#include <twbl/teeworlds/base/dbg.h>
#include <twbl/teeworlds/character.h>

int CCharacter::GetCid()
{
	dbg_assert(m_ClientId != -1, "client id is not set");
	return m_ClientId;
}
#endif
