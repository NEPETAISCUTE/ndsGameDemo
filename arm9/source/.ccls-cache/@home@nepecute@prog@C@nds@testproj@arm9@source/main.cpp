#include <gl2d.h>
#include <nds.h>
#include <stdio.h>

#include "player.hpp"
#include "vector.hpp"

//---------------------------------------------------------------------------------
int main(void) {
	//---------------------------------------------------------------------------------
	touchPosition touch;
	Player player;
	s16 frameCnt = 0;

	player.pos = VecF32(inttof32(100), inttof32(100), inttof32(0));

	cpuStartTiming(0);

	videoSetMode(MODE_5_3D);
	videoSetModeSub(MODE_5_2D);
	consoleDemoInit();

	glScreen2D();
	lcdMainOnBottom();
	s16 rotQuaternions[3] = {0, 0, 512};

	while (pmMainLoop()) {
		scanKeys();
		if (keysDown() & KEY_START) break;
		u32 angle = frameCnt * 64;
		iprintf("\x1b[10;0HframeCnt = %04i\n", angle);
		// player.pos.applyRotate(rotQuaternions);
		player.pos.applyRotate2D(1);
		iprintf("\x1b[12;0HPos x = %04li\n", f32toint(player.pos.x));
		iprintf("Pos y = %04li\n", f32toint(player.pos.y));
		iprintf("Pos z = %04li\n", f32toint(player.pos.z));
		if (keysHeld() & KEY_TOUCH) {
			/*
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
			*/
		}

		/*
		VEC_Add(&player.vel, &player.acc, &player.vel);
		VEC_Add(&player.pos, &player.vel, &player.pos);
		VEC_Scale(&player.vel, floattof32(0.50), &player.vel);
		player.acc = (VecF32){0};
		*/
		glBegin2D();

		// glBoxFilled(0, 0, 32, 32, RGB15(31, 31, 31));
		const u32 dotstep = 2441;
		Player testP;
		testP.pos.x = divf32(inttof32(frameCnt), inttof32(10));
		testP.pos.y = mulf32(sinLerp(angle), inttof32(48)) +
					  divf32(inttof32(SCREEN_HEIGHT), inttof32(2)) - inttof32(32);
		iprintf("\x1b[16HPos y = %li.%04li\n", testP.pos.y >> 12, testP.pos.y & ((1 << 12) - 1));
		glBoxFilled(f32toint(testP.pos.x), f32toint(testP.pos.y), f32toint(testP.pos.x) + 32,
					f32toint(testP.pos.y) + 32, RGB15(31, 31, 31));
		glBoxFilled(f32toint(player.pos.x), f32toint(player.pos.y), f32toint(player.pos.x) + 32,
					f32toint(player.pos.y) + 32, RGB15(0, 31, 0));

		glEnd2D();
		glFlush(0);
		swiWaitForVBlank();
		frameCnt++;
	}

	return 0;
}
