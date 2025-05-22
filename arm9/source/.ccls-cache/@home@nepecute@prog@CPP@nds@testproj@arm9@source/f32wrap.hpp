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
	constexpr fw32(double val);
	static fw32 fromF32(s32 val);

	explicit operator s32() const;
	float toFloat() const;

	void printFw32();
	void printFw32At(s32 x, s32 y);

	static fw32 floorfw32(const fw32& val);
	static fw32 ceilfw32(const fw32& val);
	static fw32 roundfw32(const fw32& val);

	static fw32 sqrtfw32(const fw32& val);
	static fw32 cosfw32(s16 idx);
	static fw32 sinfw32(s16 idx);
	static fw32 tanfw32(s16 idx);
};

fw32 operator+(const fw32& a, const fw32& b) { return fw32(a.val + b.val); }
fw32 operator-(const fw32& a, const fw32& b) { return fw32(a.val - b.val); }
fw32 operator*(const fw32& a, const fw32& b) { return fw32(mulf32(a.val, b.val)); }
fw32 operator/(const fw32& a, const fw32& b) { return fw32(divf32(a.val, b.val)); }

void operator+=(fw32& a, const fw32& b) { a = a + b; }
void operator-=(fw32& a, const fw32& b) { a = a - b; }
void operator*=(fw32& a, const fw32& b) { a = a * b; }
void operator/=(fw32& a, const fw32& b) { a = a / b; }

bool operator<(const fw32& a, const fw32& b);
bool operator==(const fw32& a, const fw32& b);
bool operator>(const fw32& a, const fw32& b);

#endif
