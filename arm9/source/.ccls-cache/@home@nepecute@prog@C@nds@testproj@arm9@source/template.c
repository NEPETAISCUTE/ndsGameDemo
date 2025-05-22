#include <gl2d.h>
#include <nds.h>
#include <stdio.h>

#define PLAYER_WIDTH inttof32(32)
#define PLAYER_HEIGHT inttof32(32)

typedef s32 f32;

typedef struct _VecF32 {
  f32 x;
  f32 y;
  f32 z;
} VecF32;

void VEC_Add(VecF32 *a, VecF32 *b, VecF32 *c) {
  c->x = a->x + b->x;
  c->y = a->y + b->y;
  c->z = a->z + b->z;
}

void VEC_Sub(VecF32 *a, VecF32 *b, VecF32 *c) {
  c->x = a->x - b->x;
  c->y = a->y - b->y;
  c->z = a->z - b->z;
}

void VEC_Scale(VecF32 *vec, f32 scale, VecF32 *res) {
  res->x = mulf32(vec->x, scale);
  res->y = mulf32(vec->y, scale);
  res->z = mulf32(vec->z, scale);
}

void VEC_Mul(VecF32 *a, VecF32 *b, VecF32 *c) {
  c->x = mulf32(a->x, b->x);
  c->y = mulf32(a->y, b->y);
  c->z = mulf32(a->z, b->z);
}

void VEC_Div(VecF32 *a, VecF32 *b, VecF32 *c) {
  c->x = divf32(a->x, b->x);
  c->y = divf32(a->y, b->y);
  c->z = divf32(a->z, b->z);
}

void VEC_DivScalar(VecF32 *vec, f32 scalar, VecF32 *res) {
  res->x = divf32(vec->x, scalar);
  res->y = divf32(vec->y, scalar);
  res->z = divf32(vec->z, scalar);
}

f32 VEC_Mag2(VecF32 *vec) {
  return mulf32(vec->x, vec->x) + mulf32(vec->y, vec->y) +
         mulf32(vec->z, vec->z);
}

f32 VEC_Mag(VecF32 *vec) { return sqrtf32(VEC_Mag2(vec)); }

void VEC_Normalize(VecF32 *vec, VecF32 *res) {
  VEC_DivScalar(vec, VEC_Mag(vec), res);
}

typedef struct _Player {
  VecF32 pos;
  VecF32 vel;
  VecF32 acc;
} Player;

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
    if (keysDown() & KEY_START)
      break;
    iprintf("\x1b[12;0HPos x = %04li\n",
            f32toint(player.pos.x)); // f32toint(player.pos.x));
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
    glBoxFilled(f32toint(player.pos.x), f32toint(player.pos.y),
                f32toint(player.pos.x) + 32, f32toint(player.pos.y) + 32,
                RGB15(0, 31, 0));

    glEnd2D();
    glFlush(0);
    swiWaitForVBlank();
  }

  return 0;
}
