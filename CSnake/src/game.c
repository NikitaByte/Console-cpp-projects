#include "game.h"
#include <stdio.h>
#include <time.h>
#include <conio.h>
#include "deque.h"
#include "conhdl.h"

#define TRUE 1
#define FALSE 0

typedef int bool;

// === Constants ===
const int WIDTH = 30;
const int HEIGHT = 20;
const char PIXEL = 219;

// === Game State Variables ===
bool is_running;
bool is_game_over;
vec2 player_vel;
deque snake;
vec2 food_pos;
int score;

UINT defaultCP;

// === Function Declarations ===
void init_console();
void init_game();
void spawn_food();
void draw_board();
void draw_snake();
void draw_food();
void display_score();
void display_game_over();
void input();
void move_snake();
void check_game_over();
void update();
void stop_game();

// === Console Initialization ===
void init_console() {
	defaultCP = GetConsoleOutputCP();
	SetConsoleOutputCP(437);
}

// === Game Initialization ===
void init_game() {
	srand((unsigned int)time(NULL));
	is_running = TRUE;
	is_game_over = FALSE;
	player_vel = (vec2){ 1, 0 };
	init_deque(&snake, 4);
	push_back(&snake, (vec2) { 4, 1 }); // head
	push_back(&snake, (vec2) { 3, 1 });
	push_back(&snake, (vec2) { 2, 1 });
	push_back(&snake, (vec2) { 1, 1 }); // tail

	spawn_food();
	score = 0;

	draw_board();
	display_score();
}

// === Food Management ===
void spawn_food() {
	food_pos.x = rand() % (WIDTH - 2) + 1;
	food_pos.y = rand() % (HEIGHT - 2) + 1;

	// Check if food spawned on snake
	for (int i = 0; i < snake.length; ++i) {
		if (snake.data[i].x == food_pos.x && snake.data[i].y == food_pos.y) {
			spawn_food(); // Recursively find new position
			return;
		}
	}

	draw_food();
}

void draw_food() {
	putc_at(PIXEL, food_pos.x, food_pos.y, RED);
}

// === Drawing Functions ===
void draw_board() {
	for (int y = 0; y < HEIGHT; ++y) {
		for (int x = 0; x < WIDTH; ++x) {
			if (x == 0 || x == WIDTH - 1 || y == 0 || y == HEIGHT - 1) {
				putc_at(PIXEL, x, y, WHITE); // Draw walls
			}
			else {
				putc_at(' ', x, y, WHITE); // Draw empty space
			}
		}
	}
	draw_snake();
}

void draw_snake() {
	for (int i = 0; i < snake.length; ++i) {
		const vec2 pos = snake.data[i];
		if (i == 0) {
			putc_at(PIXEL, pos.x, pos.y, WHITE);
		}
		else {
			putc_at(PIXEL, pos.x, pos.y, GREEN);
		}
	}
}

// === UI Functions ===
void display_score() {
	gotoxy(0, HEIGHT + 1);
	clrline();
	printf("Score: %d", score);
}

void display_game_over() {
	gotoxy(0, HEIGHT + 1);
	clrline();
	printf("Game Over! Final Score: %d", score);
}

// === Input Handling ===
void input() {
	if (_kbhit()) {
		switch (_getch()) {
		case 'w': case 'W': // Up
			if (player_vel.y == 0) player_vel = (vec2){ 0, -1 };
			break;
		case 's': case 'S': // Down
			if (player_vel.y == 0) player_vel = (vec2){ 0, 1 };
			break;
		case 'a': case 'A': // Left
			if (player_vel.x == 0) player_vel = (vec2){ -1, 0 };
			break;
		case 'd': case 'D': // Right
			if (player_vel.x == 0) player_vel = (vec2){ 1, 0 };
			break;
		case 'q': case 'Q': // Quit game
			is_running = FALSE;
			break;
		}
	}
}

// === Snake Movement ===
void move_snake() {
	const vec2 head = vec2_add(front(&snake), player_vel);

	// If food is eaten
	if (head.x == food_pos.x && head.y == food_pos.y) {
		push_front(&snake, head); // Add new head
		score++;
		display_score();
		spawn_food();
	}
	else {
		const vec2 tail = back(&snake);
		putc_at(' ', tail.x, tail.y, WHITE); // Clear the tail
		pop_back(&snake); // Remove tail
		push_front(&snake, head); // Add new head
	}

	draw_snake();
}

// === Game Logic ===
void check_game_over() {
	vec2 head = front(&snake);

	// Check wall collision
	if (head.x <= 0 || head.x >= WIDTH - 1 ||
		head.y <= 0 || head.y >= HEIGHT - 1) {
		is_game_over = TRUE;
		return;
	}

	// Check self collision
	for (int i = 1; i < snake.length; ++i) {
		if (snake.data[i].x == head.x &&
			snake.data[i].y == head.y) {
			is_game_over = TRUE;
			return;
		}
	}
}

void update() {
	input();
	move_snake();
	draw_food();
	check_game_over();
}

void stop_game() {
	SetConsoleOutputCP(defaultCP);
	is_running = FALSE;
	is_game_over = TRUE;
	free_deque(&snake);
}

// === Main Game Loop ===
void run_game() {
	init_console();
	init_game();

	while (is_running) {
		if (is_game_over) {
			free_deque(&snake);
			display_game_over();
			gotoxy(0, HEIGHT + 2);
			clrline();
			int dummy = getchar();
			(void)dummy;
			clrcon();
			init_game();
			continue;
		}

		update();
		Sleep(150);
	}

	stop_game();
}