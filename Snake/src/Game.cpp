#include "Game.hpp"
#include <conio.h>

// Constructor
Game::Game()
{
	initGame();
}

Game::~Game()
{
	snake.clear();
}

// Public methods
void Game::run()
{
	while (running) {
		if (gameOver) {
			displayGameOver();
			setCursorPosition(0, HEIGHT + 2);
			clearConsoleRow();
			system("pause");
			system("cls");
			initGame();
			continue;
		}

		update();
		Sleep(150);
	}
}

// Private methods
void Game::initGame()
{
	srand(static_cast<unsigned int>(time(nullptr)));

	// Initialize game state
	running = true;
	gameOver = false;
	playerVelocity = { UNIT_SIZE, 0 };
	snake.clear();
	snake.push_back({ UNIT_SIZE * 4, 1 });
	snake.push_back({ UNIT_SIZE * 3, 1 });
	snake.push_back({ UNIT_SIZE * 2, 1 });
	snake.push_back({ UNIT_SIZE, 1 });
	playerVelocity = { UNIT_SIZE, 0 };
	score = 0;
	createFood();

	// Display
	drawGameBoard();
	displayScore();
}

void Game::update()
{
	input();
	moveSnake();
	drawFood();
	checkGameOver();
}

void Game::input()
{
	if (_kbhit()) {
		switch (_getch()) {
		case 'w': case 'W': // Up
			if (playerVelocity.y == 0) playerVelocity = { 0, -UNIT_SIZE };
			break;
		case 's': case 'S': // Down
			if (playerVelocity.y == 0) playerVelocity = { 0, UNIT_SIZE };
			break;
		case 'a': case 'A': // Left
			if (playerVelocity.x == 0) playerVelocity = { -UNIT_SIZE, 0 };
			break;
		case 'd': case 'D': // Right
			if (playerVelocity.x == 0) playerVelocity = { UNIT_SIZE, 0 };
			break;
		case 'q': case 'Q': // Quit game
			running = false;
			break;
		}
	}
}

void Game::moveSnake()
{
	const Vector2D head = {
		snake[0].x + playerVelocity.x,
		snake[0].y + playerVelocity.y
	};

	const Vector2D tail = snake.back();
	replaceCharAt(tail.x, tail.y, ' ');

	snake.insert(snake.begin(), head);

	// If food is eaten
	if (head.x == foodPos.x &&
		head.y == foodPos.y) {
		++score;
		displayScore();
		createFood();
	}
	else {
		snake.pop_back();
	}

	drawSnake();
}

void Game::createFood()
{
	foodPos.x = rand() % (WIDTH - 2) + 1;
	foodPos.y = rand() % (HEIGHT - 2) + 1;

	for (size_t i = 0; i < snake.size(); ++i) {
		if (snake[i].x == foodPos.x && snake[i].y == foodPos.y) {
			createFood(); // Regenerate food if it overlaps with the snake
			return;
		}
	}

	drawFood();
}

void Game::drawGameBoard()
{
	for (size_t y = 0; y < HEIGHT; ++y) {
		for (size_t x = 0; x < WIDTH; ++x) {
			if (x == 0 || x == WIDTH - 1 ||
				y == 0 || y == HEIGHT - 1)
				std::cout << '#';	// Draw walls
			else std::cout << ' ';	// Draw empty space
		}
		std::cout << '\n';
	}
}

void Game::drawSnake()
{
	bool first = true;
	for (const auto& segment : snake) {
		replaceCharAt(segment.x, segment.y, first ? '@' : 'O', Color::GREEN);
		first = false;
	}
}

void Game::drawFood()
{
	replaceCharAt(foodPos.x, foodPos.y, 'd', Color::RED);
}

void Game::displayScore()
{
	setCursorPosition(0, HEIGHT + 1);
	clearConsoleRow();
	std::cout << "Score: " << score;
}

void Game::displayGameOver()
{
	setCursorPosition(0, HEIGHT + 1);
	clearConsoleRow();
	std::cout << "Game Over! Your score: " << score << std::endl;
}

void Game::setCursorPosition(int x, int y)
{
	COORD position = { x, y };
	SetConsoleCursorPosition(hConsole, position);
}

void Game::clearConsoleRow()
{
	CONSOLE_SCREEN_BUFFER_INFO csbi;
	int width = 80;

	if (GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi))
		width = csbi.srWindow.Right - csbi.srWindow.Left + 1;

	std::cout << "\r" << std::string(width - 1, ' ') << "\r";
}

void Game::replaceCharAt(short x, short y, char c, Color color)
{
	DWORD written;
	COORD position = { x, y };
	WORD col = static_cast<WORD>(color);

	WriteConsoleOutputCharacterA(hConsole, &c, 1, position, &written);
	WriteConsoleOutputAttribute(hConsole, &col, 1, position, &written);
}

void Game::checkGameOver()
{
	if (snake[0].x <= 0 || snake[0].x >= WIDTH - 1 ||
		snake[0].y <= 0 || snake[0].y >= HEIGHT - 1) {
		gameOver = true;
		return;
	}

	for (size_t i = 1; i < snake.size(); ++i) {
		if (snake[i].x == snake[0].x &&
			snake[i].y == snake[0].y) {
			gameOver = true;
			break;
		}
	}
}