#ifndef VECTOR_H
#define VECTOR_H

typedef struct {
	int x, y;
} vec2;

// Оголошення функцій (без реалізації в заголовковому файлі)
vec2 vec2_add(vec2 a, vec2 b);
vec2 vec2_sub(vec2 a, vec2 b);
vec2 vec2_mul_scalar(vec2 a, int scalar);

#endif // VECTOR_H