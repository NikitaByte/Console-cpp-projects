#ifndef VECTOR_H
#define VECTOR_H

typedef struct Vec2 {
	int x, y;
} Vec2;

Vec2 vec2_add(Vec2 a, Vec2 b);
Vec2 vec2_sub(Vec2 a, Vec2 b);
Vec2 vec2_mul_scalar(Vec2 a, int scalar);

#endif // VECTOR_H