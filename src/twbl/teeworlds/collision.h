#ifndef TWBL_SRC_TWBL_COLLISION_H
#define TWBL_SRC_TWBL_COLLISION_H

#include <twbl/teeworlds/base/vmath.h>

#if __has_include(<game/collision.h>)
#include <game/collision.h>
#else
class CCollision
{
public:
	int GetTile(int x, int y) const { return -404; }
	int IntersectLine(vec2 Pos0, vec2 Pos1, vec2 *pOutCollision, vec2 *pOutBeforeCollision) const { return -404; }

	// TODO: this is ddnet only
	int GetPureMapIndex(float x, float y) const { return 0; }
	int GetPureMapIndex(vec2 Pos) const { return GetPureMapIndex(Pos.x, Pos.y); }
	int GetTileIndex(int Index) const { return 0; }
};

#endif

#endif
