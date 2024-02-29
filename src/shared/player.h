#ifndef TWBL_SRC_SHARED_PLAYER_H
#define TWBL_SRC_SHARED_PLAYER_H

#include <shared/character.h>
#include <shared/vmath.h>

#if __has_include(<game/server/player.h>)
#include <game/server/player.h>
#else
class CPlayer
{
public:
	// use for tests only
	CCharacter *m_pCharacter;

	// use for tests only
	int m_ClientId = -1;

	CCharacter *GetCharacter() { return m_pCharacter; }
	int GetCid() const { return m_ClientId; }
};

#endif

#endif
