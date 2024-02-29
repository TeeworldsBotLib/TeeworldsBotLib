#ifndef TWBL_SRC_SHARED_CHARACTER_H
#define TWBL_SRC_SHARED_CHARACTER_H

#include <shared/vmath.h>

#if __has_include(<game/server/entities/character.h>)
#include <game/server/entities/character.h>
#else
class CCharacterCore
{
public:
	vec2 m_Vel = vec2(0.0f, 0.0f);
};

class CCharacter
{
public:
	// use for tests only
	vec2 m_Pos = vec2(0.0f, 0.0f);

	// use for tests only
	bool m_IsGrounded = false;

	int m_FreezeTime = 0;
	CCharacterCore m_Core;

	vec2 GetPos() const { return m_Pos; }
	bool IsGrounded() const { return m_IsGrounded; }

	CCharacterCore GetCore() const { return m_Core; }
	void SetCore(CCharacterCore Core) { m_Core = Core; }
	const CCharacterCore *Core() const { return &m_Core; }
};

#endif

#endif
