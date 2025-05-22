
#ifndef PLAYER_H
#define PLAYER_H

#include "vector.hpp"

#define PLAYER_DEFAULT_RADIUS 8
#define PLAYER_DEFAULT_COLOR RGB15(0, 31, 0)

typedef struct _Player {
	u32 HP;
	u32 radius;
	VecF32 pos;
	VecF32 lastPos;
} Player;

void renderPlayer(const Player* p);
void updatePlayerPos(Player* p);

#endif
