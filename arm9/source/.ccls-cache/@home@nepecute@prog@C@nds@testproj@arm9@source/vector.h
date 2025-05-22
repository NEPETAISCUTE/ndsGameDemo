
#ifndef VECTOR_H
#define VECTOR_H

#include <nds/ndstypes.h>

typedef s32 f32;

typedef struct _VecF32 {
	f32 x;
	f32 y;
	f32 z;
} VecF32;

void VEC_Add(VecF32* a, VecF32* b, VecF32* c);
void VEC_Sub(VecF32* a, VecF32* b, VecF32* c);
void VEC_Scale(VecF32* vec, f32 scale, VecF32* res);
void VEC_Mul(VecF32* a, VecF32* b, VecF32* c);
void VEC_Div(VecF32* a, VecF32* b, VecF32* c);
void VEC_DivScalar(VecF32* vec, f32 scalar, VecF32* res);
f32 VEC_Mag2(VecF32* vec);
f32 VEC_Mag(VecF32* vec);
void VEC_Normalize(VecF32* vec, VecF32* res);

#endif
