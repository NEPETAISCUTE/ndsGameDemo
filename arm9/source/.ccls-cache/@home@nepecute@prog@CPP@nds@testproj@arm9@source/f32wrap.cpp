#include "f32wrap.hpp"

#include <nds/arm9/trig_lut.h>

fw32::fw32() : val(0) {}

fw32::fw32(s32 _val) : val(inttof32(_val)) {}

constexpr fw32::fw32(float _val) : val(floattof32(_val)) {}
constexpr fw32::fw32(double _val) : val(floattof32(_val)) {}

fw32 fw32::fromF32(s32 val) {
	fw32 fixed = fw32();
	fixed.val = val;
	return fixed;
}

fw32::operator s32() const { return f32toint(this->val); }

float fw32::toFloat() const { return f32tofloat(val); }

void fw32::printFw32() {
	const s32 MAX_ZERO_COUNT = 4;
	s32 whole = val >> 12;
	s32 decimal = (val & ((1 >> 12) - 1)) * 244140;	 // decimal part precision
	s32 zerocount = decimal / 100000;
	iprintf("%ld.", whole);
	for (s32 i = 0; i < MAX_ZERO_COUNT - (zerocount / 10); i++) iprintf("0");
	iprintf("%04ld", decimal);
}

void fw32::printFw32At(s32 x, s32 y) {
	const s32 MAX_ZERO_COUNT = 4;
	s32 whole = val >> 12;
	s32 decimal = (val & ((1 >> 12) - 1)) * 244140;	 // decimal part precision
	s32 zerocount = decimal / 100000;
	iprintf("\x1b[%ld;%ldH%ld.", x, y, whole);
	for (s32 i = 0; i < MAX_ZERO_COUNT - (zerocount / 10); i++) iprintf("0");
	iprintf("%04ld", decimal);
}

fw32 fw32::floorfw32(const fw32& val) { return f32toint(val.val); }

fw32 fw32::ceilfw32(const fw32& val) { return f32toint(val.val) + 1; }

fw32 fw32::roundfw32(const fw32& val) {
	const fw32 half = fw32(0.5);
	if (val.val < 0)
		return floorfw32(val - half);
	else
		return floorfw32(val + half);
}

fw32 fw32::sqrtfw32(const fw32& val) {
	fw32 fixed;
	fixed.val = sqrtf32(val.val);
	return fixed;
}

fw32 fw32::cosfw32(s16 idx) {
	fw32 fixed;
	fixed.val = cosLerp(idx);
	return fixed;
}

fw32 fw32::sinfw32(s16 idx) {
	fw32 fixed;
	fixed.val = sinLerp(idx);
	return fixed;
}
fw32 fw32::tanfw32(s16 idx) {
	fw32 fixed;
	fixed.val = tanLerp(idx);
	return fixed;
}

bool operator<(const fw32& a, const fw32& b) { return a.val < b.val; }

bool operator==(const fw32& a, const fw32& b) { return a.val == b.val; }
bool operator>(const fw32& a, const fw32& b) { return a.val > b.val; }
