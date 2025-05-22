#include <gl2d.h>
#include <nds.h>
#include <stdio.h>

#include "player.h"
#include "vector.h"
//---------------------------------------------------------------------------------
int main(void) {
	//---------------------------------------------------------------------------------
	touchPosition touch;
	Player player;

	cpuStartTiming(0);

	player.pos.x = 0;
	player.pos.y = 0;
	player.pos.z = 0;

	player.vel = (VecF32){0};

	player.acc = (VecF32){0};

	videoSetMode(MODE_5_3D);
	videoSetModeSub(MODE_5_2D);
	consoleDemoInit();

	glScreen2D();
	lcdMainOnBottom();

	while (pmMainLoop()) {
		scanKeys();
		if (keysDown() & KEY_START) break;
		iprintf("\x1b[12;0HPos x = %04li\n",
				f32toint(player.pos.x));  // f32toint(player.pos.x));
		iprintf("Pos y = %04li\n", f32toint(player.pos.y));

		if (keysHeld() & KEY_TOUCH) {
			touchRead(&touch);
			VecF32 touchPos;
			touchPos.x = inttof32(touch.px);
			touchPos.y = inttof32(touch.py);
			touchPos.z = 0;

			iprintf("\x1b[10;0HTouch x = %04i, %04i\n", touch.rawx, touch.px);
			iprintf("Touch y = %04i, %04i\n", touch.rawy, touch.py);

			VecF32 playerSizeDiv2 = {inttof32(16), inttof32(16), 0};
			VecF32 playerCenterPos;
			VEC_Add(&player.pos, &playerSizeDiv2, &playerCenterPos);
			VEC_Sub(&touchPos, &playerCenterPos, &touchPos);
			VEC_Normalize(&touchPos, &touchPos);
			VEC_Add(&player.acc, &touchPos, &player.acc);
		}

		VEC_Add(&player.vel, &player.acc, &player.vel);
		VEC_Add(&player.pos, &player.vel, &player.pos);
		VEC_Scale(&player.vel, floattof32(0.50), &player.vel);
		player.acc = (VecF32){0};

		glBegin2D();

		glBoxFilled(0, 0, 32, 32, RGB15(31, 31, 31));
		glBoxFilled(f32toint(player.pos.x), f32toint(player.pos.y), f32toint(player.pos.x) + 32,
					f32toint(player.pos.y) + 32, RGB15(0, 31, 0));

		glEnd2D();
		glFlush(0);
		swiWaitForVBlank();
	}

	return 0;
}
