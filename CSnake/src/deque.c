#include "deque.h"
#include <stdio.h>
#include <stdlib.h>

void init_deque(Deque* d, int capacity) {
	d->data = malloc(capacity * sizeof(Vec2));
	if (!d->data) {
		fprintf(stderr, "Failed to allocate memory for deque data.\n");
		exit(EXIT_FAILURE);
	}
	d->length = 0;
	d->capacity = capacity;
}

Deque* create_deque(int capacity) {
	Deque* d = malloc(sizeof(Deque));
	if (!d) {
		fprintf(stderr, "Failed to allocate memory for deque structure.\n");
		exit(EXIT_FAILURE);
	}

	init_deque(d, capacity);

	return d;
}

void free_deque(Deque* d) {
	if (d) {
		free(d->data);
		d->data = NULL;
		d->length = 0;
		d->capacity = 0;
	}
}

static void resize_deque(Deque* d) {
	d->capacity *= 2;
	d->data = realloc(d->data, d->capacity * sizeof(Vec2));
	if (!d->data) {
		fprintf(stderr, "Failed to reallocate memory for deque data.\n");
		exit(EXIT_FAILURE);
	}
}

void push_front(Deque* d, Vec2 element) {
	if (d->length == d->capacity) {
		resize_deque(d);
	}
	for (int i = d->length; i > 0; --i) {
		d->data[i] = d->data[i - 1];
	}
	d->data[0] = element;
	d->length++;
}

void push_back(Deque* d, Vec2 element) {
	if (d->length == d->capacity) {
		resize_deque(d);
	}
	d->data[d->length] = element;
	d->length++;
}

void pop_front(Deque* d) {
	if (d->length == 0) return;
	for (int i = 0; i < d->length - 1; ++i) {
		d->data[i] = d->data[i + 1];
	}
	d->length--;
}

void pop_back(Deque* d) {
	if (d->length == 0) return;
	d->length--;
}

Vec2 get_front(const Deque* d) {
	if (d->length == 0) {
		fprintf(stderr, "Error: deque is empty\n");
		exit(EXIT_FAILURE);
	}
	return d->data[0];
}

Vec2 get_back(const Deque* d) {
	if (d->length == 0) {
		fprintf(stderr, "Error: deque is empty\n");
		exit(EXIT_FAILURE);
	}
	return d->data[d->length - 1];
}

int is_empty(const Deque* d) {
	return d->length == 0;
}

void clear_deque(Deque* d) {
	d->length = 0;
}