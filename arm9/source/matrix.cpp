#include "matrix.hpp"

Matrix3x3f32::Matrix3x3f32() {
	Mx = VecF32();
	My = VecF32();
	Mz = VecF32();
}
Matrix3x3f32::Matrix3x3f32(const VecF32& x, const VecF32& y, const VecF32& z) {
	Mx = x;
	My = y;
	Mz = z;
}

VecF32& Matrix3x3f32::operator[](s32 idx) {
	switch (idx) {
		case 0: return Mx;
		case 1: return My;
		case 2: return Mz;
	}
}

const VecF32& Matrix3x3f32::operator[](s32 idx) const {
	switch (idx) {
		case 0: return Mx;
		case 1: return My;
		case 2: return Mz;
	}
}

Matrix3x3f32 operator*(const Matrix3x3f32& Ma, const Matrix3x3f32& Mb) {
	Matrix3x3f32 res = Matrix3x3f32(VecF32(), VecF32(), VecF32());
	for (s32 i = 0; i < 3; i++) {
		for (s32 j = 0; j < 3; j++) {
			for (s32 k = 0; k < 3; k++) {
				res[i][j] += mulf32(Ma[i][k], Mb[k][j]);
			}
		}
	}
	return res;
}

VecF32 operator*(const Matrix3x3f32& M, const VecF32& vec) {
	VecF32 res = VecF32();
	for (s32 i = 0; i < 3; i++) {
		for (s32 j = 0; j < 3; j++) {
			res[j] += mulf32(M[i][j], vec[j]);
		}
	}
	return res;
}
