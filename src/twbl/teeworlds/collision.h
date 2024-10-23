#ifndef TWBL_SRC_TWBL_COLLISION_H
#define TWBL_SRC_TWBL_COLLISION_H

#if __has_include(<game/collision.h>)
#include <game/collision.h>
#else
class CCollision
{
public:
	int GetTile(int x, int y) const { return -404; }
};

#endif

#endif
