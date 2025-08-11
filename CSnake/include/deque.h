#ifndef DEQUE_H
#define DEQUE_H

#include "vector2.h"

typedef struct {
	vec2* data;
	int length;
	int capacity;
} deque;

void init_deque(deque* d, int capacity);
void free_deque(deque* d);

void push_front(deque* d, vec2 element);
void push_back(deque* d, vec2 element);

void pop_front(deque* d);
void pop_back(deque* d);

vec2 front(const deque* d);
vec2 back(const deque* d);

int is_empty(const deque* d);
void clear_deque(deque* d);

#endif // !DEQUE_H
