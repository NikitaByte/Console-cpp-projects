#ifndef DEQUE_H
#define DEQUE_H

#include "vector2.h"

typedef struct Deque {
	Vec2* data;
	int length;
	int capacity;
} Deque;

void init_deque(Deque* d, int capacity);
Deque* create_deque(int capacity);
void free_deque(Deque* d);

void push_front(Deque* d, Vec2 element);
void push_back(Deque* d, Vec2 element);

void pop_front(Deque* d);
void pop_back(Deque* d);

Vec2 get_front(const Deque* d);
Vec2 get_back(const Deque* d);

int is_empty(const Deque* d);
void clear_deque(Deque* d);

#endif // !DEQUE_H
