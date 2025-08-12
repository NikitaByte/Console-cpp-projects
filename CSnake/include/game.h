#ifndef GAME_H
#define GAME_H

#include <Windows.h>
#include "vector2.h"
#include "deque.h"

static UINT defaultCP = 0;

typedef struct Game {
	int is_running;
	int is_game_over;
	Vec2 player_vel;
	Deque* snake;
	Vec2 food_pos;
	int score;
} Game;

Game* create_game();
void reset_game(Game* game);
void spawn_food(Game* game);
void draw_board();
void draw_snake(const Deque* snake);
void draw_food(const Vec2 food_pos);
void display_score(const int score);
void display_game_over(const int score);
void input(Game* game);
void move_snake(Game* game);
void check_game_over(Game* game);
void game_over_dialog(Game* game);
void update(Game* game);
void end_game(Game* game);

#endif // GAME_H