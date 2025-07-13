#ifndef TWBL_SRC_TWBL_PROTOCOL_H
#define TWBL_SRC_TWBL_PROTOCOL_H

#if __has_include(<engine/shared/protocol.h>)
#include <engine/shared/protocol.h>
#else
#ifndef MAX_CLIENTS
#define MAX_CLIENTS 64
#endif
#endif

#if __has_include(<game/generated/protocol.h>)
#include <game/generated/protocol.h>
#else

enum
{
	INPUT_STATE_MASK = 0x3f
};

enum
{
	WEAPON_HAMMER = 0,
	WEAPON_GUN,
	WEAPON_SHOTGUN,
	WEAPON_GRENADE,
	WEAPON_LASER,
	WEAPON_NINJA,
	NUM_WEAPONS
};

enum
{
	WEAPON_SELF = -2,
};

enum
{
	EMOTICON_OOP,
	EMOTICON_EXCLAMATION,
	EMOTICON_HEARTS,
	EMOTICON_DROP,
	EMOTICON_DOTDOT,
	EMOTICON_MUSIC,
	EMOTICON_SORRY,
	EMOTICON_GHOST,
	EMOTICON_SUSHI,
	EMOTICON_SPLATTEE,
	EMOTICON_DEVILTEE,
	EMOTICON_ZOMG,
	EMOTICON_ZZZ,
	EMOTICON_WTF,
	EMOTICON_EYES,
	EMOTICON_QUESTION,
	NUM_EMOTICONS
};

#endif

#endif
