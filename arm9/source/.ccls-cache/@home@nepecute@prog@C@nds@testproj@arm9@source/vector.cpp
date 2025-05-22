#include "vector.hpp"

#include <nds/arm9/math.h>
#include <nds/arm9/trig_lut.h>
#include <stdio.h>

#include "matrix.hpp"

namespace std {
	template <typename _Tp>
	constexpr inline const _Tp& min(const _Tp& __a, const _Tp& __b) {
		// concept requirements
		// return __b < __a ? __b : __a;
		if (__b < __a) return __b;
		return __a;
	}

	template <typename _Tp>
	constexpr inline const _Tp& max(const _Tp& __a, const _Tp& __b) {
		// concept requirements
		// return  __a < __b ? __b : __a;
		if (__a < __b) return __b;
		return __a;
	}

	template <typename _Tp>
	constexpr inline const _Tp& clamp(const _Tp& __val, const _Tp& __lo, const _Tp& __hi) {
		return std::min(std::max(__val, __lo), __hi);
	}
}  // namespace std

inline fw32 lerpf32(fw32 a, fw32 b, fw32 t) { return a + (b - a) * t; }

VecF32::VecF32() {
	this->x = 0;
	this->y = 0;
	this->z = 0;
}

VecF32::VecF32(fw32 x, fw32 y, fw32 z) {
	this->x = x;
	this->y = y;
	this->z = z;
}

VecF32 VecF32::fromS32(s32 x, s32 y, s32 z) {
	VecF32 vec;
	vec.x = fw32::fromInt(x);
	vec.y = fw32::fromInt(y);
	vec.z = fw32::fromInt(z);
	return vec;
}

fw32 VecF32::dotproduct(const VecF32& a, const VecF32& b) {
	return a.x * b.x + a.y * b.y + a.z * b.z;
}

VecF32 VecF32::crossproduct(const VecF32& a, const VecF32& b) {
	VecF32 res;
	// float crossX = v1.y * v2.z - v1.z * v2.y;
	// float crossY = v1.z * v2.x - v1.x * v2.z;
	// float crossZ = v1.x * v2.y - v1.y * v2.x;
	res.x = a.y * b.z - a.z * b.y;
	res.y = a.z * b.x - a.x * b.z;
	res.z = a.x * b.y - a.y * b.x;
	return res;
}

fw32 VecF32::dist2(const VecF32& a, const VecF32& b) { return (b - a).mag2(); }

fw32 VecF32::dist(const VecF32& a, const VecF32& b) { return (b - a).mag(); }

VecF32 VecF32::min(const VecF32& a, const VecF32& b) {
	return VecF32(std::min(a.x, b.x), std::min(a.y, b.y), std::min(a.z, b.z));
}

VecF32 VecF32::max(const VecF32& a, const VecF32& b) {
	return VecF32(std::max(a.x, b.x), std::max(a.y, b.y), std::max(a.z, b.z));
}

VecF32 VecF32::clamp(const VecF32& vec, const VecF32& a, const VecF32& b) {
	return VecF32(std::clamp(vec.x, a.x, b.x), std::clamp(vec.y, a.y, b.y),
				  std::clamp(vec.z, a.z, b.z));
}

VecF32 VecF32::lerp(const VecF32& a, const VecF32& b, fw32 t) {
	VecF32 diff = b - a;
	return a + diff * t;
}

VecF32 VecF32::lerp(const VecF32& a, const VecF32& b, fw32 tX, fw32 tY, fw32 tZ) {
	return VecF32(lerpf32(a.x, b.x, tX), lerpf32(a.y, b.y, tY), lerpf32(a.z, b.z, tZ));
}

fw32 VecF32::mag2(const VecF32& vec) { return vec.x * vec.x + vec.y * vec.y + vec.z * vec.z; }

fw32 VecF32::mag(const VecF32& vec) { return sqrtfw32(mag2(vec)); }

fw32 VecF32::dotproduct(const VecF32& other) { return dotproduct(*this, other); }
VecF32 VecF32::crossproduct(const VecF32& other) { return crossproduct(*this, other); }
fw32 VecF32::dist2(const VecF32& other) { return dist2(*this, other); }
fw32 VecF32::dist(const VecF32& other) { return dist(*this, other); }

VecF32 VecF32::min(const VecF32& other) { return min(*this, other); }
VecF32 VecF32::max(const VecF32& other) { return max(*this, other); }
VecF32 VecF32 ::clamp(const VecF32& a, const VecF32& b) { return clamp(*this, a, b); }
fw32 VecF32::mag2() const { return mag2(*this); }

fw32 VecF32::mag() const { return mag(*this); }

VecF32 VecF32::floor() { return VecF32(fw32floor(x), fw32floor(y), fw32floor(z)); }

void VecF32::applyFloor() { *this = floor(); }

VecF32 VecF32::ceil() { return VecF32(fw32ceil(x), fw32ceil(y), fw32ceil(z)); }

void VecF32::applyCeil() { *this = ceil(); }

// VecF32 round();
// void applyRound();

VecF32 VecF32::norm() const { return *this / mag(); }
void VecF32::applyNorm() { *this = norm(); }
VecF32 VecF32::limit(fw32 val) { return norm() * std::min(mag(), val); }

void VecF32::applyLimit(fw32 val) { *this = limit(val); }

VecF32 VecF32::rotate2D(s16 angle, const VecF32& origin) {
	VecF32 vec = *this - origin;

	fw32 cosres = fw32(cosLerp(angle));
	fw32 sinres = fw32(sinLerp(angle));

	VecF32 res = VecF32();
	res.x = vec.x * cosres - vec.y * sinres;
	res.y = vec.x * sinres + vec.y * cosres;

	res = res + origin;
	return res;
}

VecF32 VecF32::rotate(s16 angle, const VecF32& origin, const VecF32& axis) {
	/*VecF32 vec = *this - origin;
	Matrix3x3f32 rotmatroll = Matrix3x3f32(
		VecF32(cosLerp(quaternions[0]), -sinLerp(quaternions[0]), 0),
		VecF32(sinLerp(quaternions[0]), cosLerp(quaternions[0]), 0), VecF32(0, 0, inttof32(1)));
	Matrix3x3f32 rotmatpitch = Matrix3x3f32(
		VecF32(cosLerp(quaternions[1]), 0, sinLerp(quaternions[1])), VecF32(0, inttof32(1), 0),
		VecF32(-sinLerp(quaternions[1]), 0, cosLerp(quaternions[1])));
	Matrix3x3f32 rotmatyaw = Matrix3x3f32(
		VecF32(inttof32(1), 0, 0), VecF32(0, cosLerp(quaternions[2]), -sinLerp(quaternions[2])),
		VecF32(0, sinLerp(quaternions[2]), cosLerp(quaternions[2])));

	Matrix3x3f32 rotmat = rotmatroll * rotmatyaw * rotmatpitch;
	iprintf("\x1b[1;0HMatrix: xx = %d, xy = %d, xz = %d\n", rotmat[0][0], rotmat[0][1],
			rotmat[0][2]);
	iprintf("        yx = %d, yy = %d, yz = %d\n", rotmat[1][0], rotmat[1][1], rotmat[1][2]);
	iprintf("        zx = %d, zy = %d, zz = %d\n", rotmat[2][0], rotmat[2][1], rotmat[2][2]);
	iprintf("\x1b[8;0Hvector: x = %d, y = %d, z = %d\n", f32toint(vec.x), f32toint(vec.y),
			f32toint(vec.z));
	vec = rotmat * vec;
	iprintf("\x1b[10;0Hvector: x = %d, y = %d, z = %d\n", f32toint(vec.x), f32toint(vec.y),
			f32toint(vec.z));
	return vec + origin;*/

	return *this * cosLerp(angle) + VecF32::crossproduct(axis, *this) * sinLerp(angle) +
		   axis * VecF32::dotproduct(axis, *this) * (inttof32(1) - cosLerp(angle));

	VecF32 v = *this - origin;
	VecF32 k = axis.norm();
	VecF32 cross = VecF32::crossproduct(v, k);
	fw32 dot = VecF32::dotproduct(v, k);
	fw32 cos_ = fw32(cosLerp(angle));
	fw32 sin_ = fw32(sinLerp(angle));

	VecF32 tempV = v * cos_;
	VecF32 tempCross = cross * sin_;
	VecF32 tempK = k * (dot * (fw32(1) - cos_));

	VecF32 res = tempV + tempCross + tempK;
	return res + origin;
}

void VecF32::applyRotate(s16 angle, const VecF32& origin, const VecF32& axis) {
	*this = rotate(angle, origin, axis);
}
void VecF32::applyRotate2D(s16 angle, const VecF32& origin) { *this = rotate2D(angle, origin); }
/*
void VecF32::applyRotate(const s16 quaternions[3], const VecF32& origin) {
	*this = rotate(quaternions, origin);
}*/

void VecF32::setMag(fw32 val) { *this = norm() * val; }

VecF32 operator+(const VecF32& lhs, const VecF32& rhs) {
	VecF32 res;
	res.x = lhs.x + rhs.x;
	res.y = lhs.y + rhs.y;
	res.z = lhs.z + rhs.z;
	return res;
}

VecF32 operator-(const VecF32& lhs, const VecF32& rhs) {
	VecF32 res;
	res.x = lhs.x - rhs.x;
	res.y = lhs.y - rhs.y;
	res.z = lhs.z - rhs.z;
	return res;
}

VecF32 operator+(const VecF32& vec, fw32 scl) {
	VecF32 res;
	res.x = vec.x + scl;
	res.y = vec.y + scl;
	res.z = vec.z + scl;
	return res;
}

VecF32 operator-(const VecF32& vec, fw32 scl) {
	VecF32 res;
	res.x = vec.x - scl;
	res.y = vec.y - scl;
	res.z = vec.z - scl;
	return res;
}

VecF32 operator*(const VecF32& vec, fw32 scl) {
	VecF32 res;
	res.x = vec.x * scl;
	res.y = vec.y * scl;
	res.z = vec.z * scl;
	return res;
}

VecF32 operator/(const VecF32& vec, fw32 scl) {
	VecF32 res;
	res.x = vec.x / scl;
	res.y = vec.y / scl;
	res.z = vec.z / scl;
	return res;
}

VecF32& operator+=(VecF32& lhs, const VecF32& rhs) {
	lhs.x += rhs.x;
	lhs.y += rhs.y;
	lhs.z += rhs.z;
	return lhs;
}

VecF32& operator-=(VecF32& lhs, const VecF32& rhs) {
	lhs.x -= rhs.x;
	lhs.y -= rhs.y;
	lhs.z -= rhs.z;
	return lhs;
}

VecF32& operator+=(VecF32& vec, fw32 scl) {
	vec.x += scl;
	vec.y += scl;
	vec.z += scl;
	return vec;
}

VecF32& operator-=(VecF32& vec, fw32 scl) {
	vec.x -= scl;
	vec.y -= scl;
	vec.z -= scl;
	return vec;
}

VecF32& operator*=(VecF32& vec, fw32 scl) {
	vec.x = vec.x * scl;
	vec.y = vec.y * scl;
	vec.z = vec.z * scl;
	return vec;
}

VecF32& operator/=(VecF32& vec, fw32 scl) {
	vec.x = vec.x / scl;
	vec.y = vec.y / scl;
	vec.z = vec.z / scl;
	return vec;
}

bool operator==(const VecF32& lhs, const VecF32& rhs) {
	return lhs.x == rhs.x && lhs.y == rhs.y && lhs.z == rhs.z;
}

bool operator!=(const VecF32& lhs, const VecF32& rhs) { return !(lhs == rhs); }
