#include "deque.h"
#include <stdio.h>
#include <stdlib.h>

void init_deque(deque* d, int capacity) {
	d->data = malloc(capacity * sizeof(vec2));
	d->length = 0;
	d->capacity = capacity;
}

void free_deque(deque* d) {
	free(d->data);
	d->data = NULL;
	d->length = 0;
	d->capacity = 0;
}

static void resize_deque(deque* d) {
	d->capacity *= 2;
	d->data = realloc(d->data, d->capacity * sizeof(vec2));
	if (!d->data) {
		perror("realloc failed");
		exit(1);
	}
}

void push_front(deque* d, vec2 element) {
	if (d->length == d->capacity) {
		resize_deque(d);
	}
	for (int i = d->length; i > 0; --i) {
		d->data[i] = d->data[i - 1];
	}
	d->data[0] = element;
	d->length++;
}

void push_back(deque* d, vec2 element) {
	if (d->length == d->capacity) {
		resize_deque(d);
	}
	d->data[d->length] = element;
	d->length++;
}

void pop_front(deque* d) {
	if (d->length == 0) return;
	for (int i = 0; i < d->length - 1; ++i) {
		d->data[i] = d->data[i + 1];
	}
	d->length--;
}

void pop_back(deque* d) {
	if (d->length == 0) return;
	d->length--;
}

vec2 front(const deque* d) {
	if (d->length == 0) {
		fprintf(stderr, "Error: deque is empty\n");
		exit(1);
	}
	return d->data[0];
}

vec2 back(const deque* d) {
	if (d->length == 0) {
		fprintf(stderr, "Error: deque is empty\n");
		exit(1);
	}
	return d->data[d->length - 1];
}

int is_empty(const deque* d) {
	return d->length == 0;
}

void clear_deque(deque* d) {
	d->length = 0;
}