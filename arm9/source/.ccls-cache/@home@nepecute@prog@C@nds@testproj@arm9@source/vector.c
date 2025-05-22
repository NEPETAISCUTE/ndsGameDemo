#include "vector.h"

#include <nds/arm9/math.h>

void VEC_Add(VecF32* a, VecF32* b, VecF32* c) {
	c->x = a->x + b->x;
	c->y = a->y + b->y;
	c->z = a->z + b->z;
}

void VEC_Sub(VecF32* a, VecF32* b, VecF32* c) {
	c->x = a->x - b->x;
	c->y = a->y - b->y;
	c->z = a->z - b->z;
}

void VEC_Scale(VecF32* vec, f32 scale, VecF32* res) {
	res->x = mulf32(vec->x, scale);
	res->y = mulf32(vec->y, scale);
	res->z = mulf32(vec->z, scale);
}

void VEC_Mul(VecF32* a, VecF32* b, VecF32* c) {
	c->x = mulf32(a->x, b->x);
	c->y = mulf32(a->y, b->y);
	c->z = mulf32(a->z, b->z);
}

void VEC_Div(VecF32* a, VecF32* b, VecF32* c) {
	c->x = divf32(a->x, b->x);
	c->y = divf32(a->y, b->y);
	c->z = divf32(a->z, b->z);
}

void VEC_DivScalar(VecF32* vec, f32 scalar, VecF32* res) {
	res->x = divf32(vec->x, scalar);
	res->y = divf32(vec->y, scalar);
	res->z = divf32(vec->z, scalar);
}

f32 VEC_Mag2(VecF32* vec) {
	return mulf32(vec->x, vec->x) + mulf32(vec->y, vec->y) + mulf32(vec->z, vec->z);
}

f32 VEC_Mag(VecF32* vec) { return sqrtf32(VEC_Mag2(vec)); }

void VEC_Normalize(VecF32* vec, VecF32* res) { VEC_DivScalar(vec, VEC_Mag(vec), res); }
