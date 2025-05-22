#ifndef F32WRAP_HPP
#define F32WRAP_HPP

#include <nds/arm9/math.h>
#include <nds/ndstypes.h>
#include <stdio.h>

struct fw32 {
	s32 val;
	fw32();
	fw32(s32 val);
	constexpr fw32(float val);
	static fw32 fromInt(s32 val);

	s32 toInt() const;
	float toFloat() const;

	void printFw32At(s32 x, s32 y);
};

fw32 operator+(const fw32& a, const fw32& b) { return fw32(a.val + b.val); }
fw32 operator-(const fw32& a, const fw32& b) { return fw32(a.val - b.val); }
fw32 operator*(const fw32& a, const fw32& b) { return fw32(mulf32(a.val, b.val)); }
fw32 operator/(const fw32& a, const fw32& b) { return fw32(divf32(a.val, b.val)); }

fw32 operator+(const fw32& a, s32 b) { return a + fw32::fromInt(b); }
fw32 operator-(const fw32& a, s32 b) { return a - fw32::fromInt(b); }
fw32 operator*(const fw32& a, s32 b) { return a * fw32::fromInt(b); }
fw32 operator/(const fw32& a, s32 b) { return a / fw32::fromInt(b); }

void operator+=(fw32& a, const fw32& b) { a = a + b; }
void operator-=(fw32& a, const fw32& b) { a = a - b; }
void operator*=(fw32& a, const fw32& b) { a = a * b; }
void operator/=(fw32& a, const fw32& b) { a = a / b; }
void operator+=(fw32& a, s32 b) { a = a + b; }
void operator-=(fw32& a, s32 b) { a = a - b; }
void operator*=(fw32& a, s32 b) { a = a * b; }
void operator/=(fw32& a, s32 b) { a = a / b; }

#endif
