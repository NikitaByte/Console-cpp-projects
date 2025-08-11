#include "vector2.h"

vec2 vec2_add(vec2 a, vec2 b) {
	return (vec2) { a.x + b.x, a.y + b.y };
}

vec2 vec2_sub(vec2 a, vec2 b) {
	return (vec2) { a.x - b.x, a.y - b.y };
}

vec2 vec2_mul_scalar(vec2 a, int scalar) {
	return (vec2) { a.x* scalar, a.y* scalar };
}