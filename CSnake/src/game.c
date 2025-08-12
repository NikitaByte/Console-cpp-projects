#include "game.h"
#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include "conhdl.h"

const int WIDTH = 30;
const int HEIGHT = 20;
const char PIXEL = 219;

Game* create_game() {
	srand((unsigned int)time(NULL));

	Game* game = malloc(sizeof(Game));
	if (!game) {
		fprintf(stderr, "Failed to allocate memory for game.\n");
		exit(EXIT_FAILURE);
	}

	defaultCP = GetConsoleOutputCP();
	SetConsoleOutputCP(437);

	game->is_running = 1;
	game->is_game_over = 0;
	game->player_vel = (Vec2){ 1, 0 };
	game->score = 0;

	// Snake and food initialization
	game->snake = create_deque(4);
	push_back(game->snake, (Vec2) { 4, 1 }); // head
	push_back(game->snake, (Vec2) { 3, 1 });
	push_back(game->snake, (Vec2) { 2, 1 });
	push_back(game->snake, (Vec2) { 1, 1 }); // tail

	draw_board();
	draw_snake(game->snake);
	spawn_food(game);
	display_score(game->score);

	return game;
}

void reset_game(Game* game) {
	game->is_game_over = 0;
	game->score = 0;
	game->player_vel = (Vec2){ 1, 0 };
	clear_deque(game->snake);
	push_back(game->snake, (Vec2) { 4, 1 }); // head
	push_back(game->snake, (Vec2) { 3, 1 });
	push_back(game->snake, (Vec2) { 2, 1 });
	push_back(game->snake, (Vec2) { 1, 1 }); // tail
	draw_board();
	draw_snake(game->snake);
	spawn_food(game);
	display_score(game->score);
}

void spawn_food(Game* game) {
	Vec2* food_pos = &game->food_pos;
	Deque* snake = game->snake;

	food_pos->x = rand() % (WIDTH - 2) + 1;
	food_pos->y = rand() % (HEIGHT - 2) + 1;

	for (int i = 0; i < snake->length; ++i) {
		if (snake->data[i].x == food_pos->x &&
			snake->data[i].y == food_pos->y) {
			spawn_food(game);
			return;
		}
	}

	draw_food(*food_pos);
}

void draw_food(const Vec2 food_pos) {
	putc_at(PIXEL, food_pos.x, food_pos.y, RED);
}

void draw_board() {
	for (int y = 0; y < HEIGHT; ++y) {
		for (int x = 0; x < WIDTH; ++x) {
			if (x == 0 || x == WIDTH - 1 ||
				y == 0 || y == HEIGHT - 1)
				putc_at(PIXEL, x, y, WHITE);
			else
				putc_at(' ', x, y, WHITE);
		}
	}
}

void draw_snake(const Deque* snake) {
	for (int i = 0; i < snake->length; ++i) {
		const Vec2 pos = snake->data[i];
		Color snake_color = GREEN;
		if (i == 0) snake_color = WHITE;
		putc_at(PIXEL, pos.x, pos.y, snake_color);
	}
}

void display_score(const int score) {
	gotoxy(0, HEIGHT + 1);
	clrline();
	printf("Score: %d", score);
}

void display_game_over(const int score) {
	gotoxy(0, HEIGHT + 1);
	clrline();
	printf("Game Over! Final Score: %d", score);
}

void input(Game* game) {
	Vec2* player_vel = &game->player_vel;

	if (_kbhit()) {
		switch (_getch()) {
		case 'w': case 'W': // Up
			if (player_vel->y == 0) *player_vel = (Vec2){ 0, -1 };
			break;
		case 's': case 'S': // Down
			if (player_vel->y == 0) *player_vel = (Vec2){ 0, 1 };
			break;
		case 'a': case 'A': // Left
			if (player_vel->x == 0) *player_vel = (Vec2){ -1, 0 };
			break;
		case 'd': case 'D': // Right
			if (player_vel->x == 0) *player_vel = (Vec2){ 1, 0 };
			break;
		case 'q': case 'Q': // Quit game
			game->is_running = 0;
			break;
		}
	}
}

void move_snake(Game* game) {
	Deque* snake = game->snake;
	const Vec2 food_pos = game->food_pos;
	const Vec2 player_vel = game->player_vel;
	const Vec2 head = vec2_add(get_front(snake), player_vel);

	// If food is eaten
	if (head.x == food_pos.x &&
		head.y == food_pos.y) {
		push_front(snake, head);
		game->score++;
		display_score(game->score);
		spawn_food(game);
	}
	else {
		const Vec2 tail = get_back(snake);
		putc_at(' ', tail.x, tail.y, WHITE);
		pop_back(snake);
		push_front(snake, head);
	}

	draw_snake(snake);
}

void check_game_over(Game* game) {
	const Deque* snake = game->snake;
	const Vec2 head = get_front(snake);

	// Check wall collision
	if (head.x <= 0 || head.x >= WIDTH - 1 ||
		head.y <= 0 || head.y >= HEIGHT - 1) {
		game->is_game_over = 1;
		return;
	}

	// Check self collision
	for (int i = 1; i < snake->length; ++i) {
		if (snake->data[i].x == head.x &&
			snake->data[i].y == head.y) {
			game->is_game_over = 1;
			return;
		}
	}
}

void game_over_dialog(Game* game)
{
	display_game_over(game->score);
	gotoxy(0, HEIGHT + 2);
	clrline();
	printf("Press Enter to restart or Q to quit...");

	char ch = _getch();
	if (ch == 'q' || ch == 'Q') {
		game->is_running = 0;
		return;
	}

	clrcon();
	reset_game(game);
}

void update(Game *game) {
	input(game);
	move_snake(game);
	draw_food(game->food_pos);
	check_game_over(game);
}

void end_game(Game* game) {
	SetConsoleOutputCP(defaultCP);
	game->is_running = 0;
	game->is_game_over = 1;
	free_deque(game->snake);
	free(game);
}