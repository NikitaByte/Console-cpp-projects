#include "vector2.h"

Vec2 vec2_add(Vec2 a, Vec2 b) {
	return (Vec2) { a.x + b.x, a.y + b.y };
}

Vec2 vec2_sub(Vec2 a, Vec2 b) {
	return (Vec2) { a.x - b.x, a.y - b.y };
}

Vec2 vec2_mul_scalar(Vec2 a, int scalar) {
	return (Vec2) { a.x* scalar, a.y* scalar };
}