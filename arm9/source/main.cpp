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

	player.pos = VecF32((s32)100L, (s32)100L, (s32)0L);

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
		testP.pos.x = (fw32)((s32)frameCnt) / (s32)10;
		testP.pos.y = fw32::sinfw32(angle) * (s32)48 + SCREEN_HEIGHT / (s32)2 - (s32)32;
		iprintf("\x1b[16HPos y = %li.%04li\n", testP.pos.y >> 12, testP.pos.y & ((1 << 12) - 1));
		glBoxFilled((s32)testP.pos.x, (s32)testP.pos.y, (s32)testP.pos.x + (s32)32,
					(s32)testP.pos.y + (s32)32, RGB15(31, 31, 31));
		glBoxFilled((s32)player.pos.x, (s32)player.pos.y, (s32)player.pos.x + (s32)32,
					(s32)player.pos.y + (s32)32, RGB15(0, 31, 0));

		glEnd2D();
		glFlush(0);
		swiWaitForVBlank();
		frameCnt++;
	}

	return 0;
}
