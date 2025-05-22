
#ifndef VECTOR_HPP
#define VECTOR_HPP

#include <nds/arm9/math.h>
#include <nds/ndstypes.h>

#include "f32wrap.hpp"

struct VecF32 {
   public:
	fw32 x;
	fw32 y;
	fw32 z;

	VecF32();
	VecF32(fw32 x, fw32 y, fw32 z);

	static VecF32 fromS32(s32 x, s32 y, s32 z);

	static fw32 dotproduct(const VecF32& a, const VecF32& b);
	static VecF32 crossproduct(const VecF32& a, const VecF32& b);
	static fw32 dist2(const VecF32& a, const VecF32& b);
	static fw32 dist(const VecF32& a, const VecF32& b);

	static VecF32 min(const VecF32& a, const VecF32& b);
	static VecF32 max(const VecF32& a, const VecF32& b);
	static VecF32 clamp(const VecF32& vec, const VecF32& a, const VecF32& b);
	static VecF32 lerp(const VecF32& a, const VecF32& b, fw32 t);
	static VecF32 lerp(const VecF32& a, const VecF32& b, fw32 tX, fw32 tY, fw32 tZ);
	static fw32 mag2(const VecF32& vec);
	static fw32 mag(const VecF32& vec);

	fw32 dotproduct(const VecF32& other);
	VecF32 crossproduct(const VecF32& other);
	fw32 dist2(const VecF32& other);
	fw32 dist(const VecF32& other);

	VecF32 min(const VecF32& other);
	VecF32 max(const VecF32& other);
	VecF32 clamp(const VecF32& a, const VecF32& b);
	fw32 mag2() const;
	fw32 mag() const;

	VecF32 floor();
	void applyFloor();
	VecF32 ceil();
	void applyCeil();
	VecF32 round();
	void applyRound();
	VecF32 norm() const;
	void applyNorm();
	VecF32 limit(fw32 val);
	void applyLimit(fw32 val);

	// VecF32 rotate(s16 angle, const VecF32& origin = VecF32(),
	//			  const VecF32& axis = VecF32(0, 0, inttof32(1)));
	VecF32 rotate2D(s16 angle, const VecF32& orgin = VecF32());
	VecF32 rotate(s16 angle, const VecF32& origin = VecF32(),
				  const VecF32& axis = VecF32(0, 0, inttof32(1)));
	// void applyRotate(s16 angle, const VecF32& origin = VecF32(),
	//				 const VecF32& axis = VecF32(0, 0, inttof32(1)));
	void applyRotate2D(s16 angle, const VecF32& origin = VecF32());
	void applyRotate(s16 angle, const VecF32& origin = VecF32(),
					 const VecF32& axis = VecF32((fw32)0, 0, inttof32(1)));

	void setMag(fw32 val);

	fw32& operator[](s32 idx) {
		switch (idx) {
			case 0: return x;
			case 1: return y;
			case 2: return z;
		}
	}
	const fw32& operator[](s32 idx) const {
		switch (idx) {
			case 0: return x;
			case 1: return y;
			case 2: return z;
		}
	}
};

VecF32 operator+(const VecF32& lhs, const VecF32& rhs);
VecF32 operator-(const VecF32& lhs, const VecF32& rhs);
VecF32 operator+(const VecF32& vec, fw32 scl);
VecF32 operator-(const VecF32& vec, fw32 scl);
VecF32 operator*(const VecF32& vec, fw32 scl);
VecF32 operator/(const VecF32& vec, fw32 scl);

VecF32& operator+=(VecF32& lhs, const VecF32& rhs);
VecF32& operator-=(VecF32& lhs, const VecF32& rhs);
VecF32& operator+=(VecF32& vec, fw32 scl);
VecF32& operator-=(VecF32& vec, fw32 scl);
VecF32& operator*=(VecF32& vec, fw32 scl);
VecF32& operator/=(VecF32& vec, fw32 scl);

bool operator==(const VecF32& lhs, const VecF32& rhs);
bool operator!=(const VecF32& lhs, const VecF32& rhs);

#endif
