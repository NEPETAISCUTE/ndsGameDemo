
#ifndef MATRIX_HPP
#define MATRIX_HPP

#include "vector.hpp"

struct Matrix3x3f32 {
	VecF32 Mx;
	VecF32 My;
	VecF32 Mz;

	Matrix3x3f32();
	Matrix3x3f32(const VecF32& x, const VecF32& y, const VecF32& z);

	VecF32& operator[](s32 idx);
	const VecF32& operator[](s32 idx) const;
};

Matrix3x3f32 operator*(const Matrix3x3f32& Ma, const Matrix3x3f32& Mb);
VecF32 operator*(const Matrix3x3f32& M, const VecF32& vec);

#endif
