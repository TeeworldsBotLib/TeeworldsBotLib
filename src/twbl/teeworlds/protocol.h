#ifndef TWBL_SRC_TWBL_PROTOCOL_H
#define TWBL_SRC_TWBL_PROTOCOL_H

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

#endif

#endif
