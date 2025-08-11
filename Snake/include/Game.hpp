#pragma once

// === Includes ===
#include <iostream>
#include <Windows.h>
#include <vector>


// === Structs ===
struct Vector2D {
	int x, y;
};


// === Enums ===
enum class Color : WORD {
	BLACK = 0,
	WHITE = FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE | FOREGROUND_INTENSITY,
	BLUE = FOREGROUND_BLUE,
	RED = FOREGROUND_RED,
	GREEN = FOREGROUND_GREEN,
	MAGENTA = FOREGROUND_RED | FOREGROUND_BLUE | FOREGROUND_INTENSITY,
	CYAN = FOREGROUND_BLUE | FOREGROUND_GREEN | FOREGROUND_INTENSITY,
	YELLOW = FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_INTENSITY
};


// === Constants ===
constexpr int WIDTH = 20;
constexpr int HEIGHT = 20;
constexpr int UNIT_SIZE = 1;


// === Game Class ===
class Game {
public:
	// Constructor
	Game();
	~Game();

	// Main game loop
	void run();

private:
	// Game logic
	void initGame();
	void update();
	void input();

	// Update snake and food positions
	void moveSnake();
	void createFood();

	// Drawing functions
	void drawGameBoard();
	void drawSnake();
	void drawFood();

	// Display functions
	void displayScore();
	void displayGameOver();

	// Console manipulation functions
	void setCursorPosition(int x, int y);
	void clearConsoleRow();
	void replaceCharAt(short x, short y, char c, Color color = Color::WHITE);

	void checkGameOver();

private:
	// Game settings
	bool running;
	bool gameOver;

	// Player
	Vector2D playerVelocity;
	std::vector<Vector2D> snake;
	int score;

	// Food
	Vector2D foodPos;

	// Console handle
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
};