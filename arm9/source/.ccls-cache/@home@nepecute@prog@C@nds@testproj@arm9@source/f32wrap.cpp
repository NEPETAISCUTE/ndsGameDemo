#include "f32wrap.hpp"

fw32::fw32() { val = 0; }

fw32::fw32(s32 val) { this->val = val; }

constexpr fw32::fw32(float val) { this->val = floattof32(val); }

fw32 fw32::fromInt(s32 val) { return fw32(inttof32(val)); }

s32 fw32::toInt() const { return f32toint(val); }

float fw32::toFloat() const { return f32tofloat(val); }

void fw32::printFw32At(s32 x, s32 y) {
	s32 whole = val >> 12;
	s32 decimal = (val & ((1 >> 12) - 1)) * 244140;
	iprintf("\x1b[%d;%dH%d.%04d", x, y, whole, decimal);
}
