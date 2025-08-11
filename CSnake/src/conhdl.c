#include "conhdl.h"

void gotoxy(int x, int y) {
	COORD coord = { (SHORT)x, (SHORT)y };
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleCursorPosition(hConsole, coord);
}

void set_color(enum Color color) {
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(hConsole, color);
}

void clrcon() {
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	COORD coord = { 0, 0 };
	DWORD written;
	CONSOLE_SCREEN_BUFFER_INFO csbi;
	GetConsoleScreenBufferInfo(hConsole, &csbi);
	DWORD size = csbi.dwSize.X * csbi.dwSize.Y;
	FillConsoleOutputCharacter(hConsole, ' ', size, coord, &written);
	FillConsoleOutputAttribute(hConsole, csbi.wAttributes, size, coord, &written);
	SetConsoleCursorPosition(hConsole, coord);
}

void clrline() {
	CONSOLE_SCREEN_BUFFER_INFO csbi;
	int width = 80;

	if (GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi))
		width = csbi.srWindow.Right - csbi.srWindow.Left + 1;

	printf("\r%*s\r", width - 1, "");

	//std::cout << "\r" << std::string(width - 1, ' ') << "\r";
	
	//HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	//COORD coord = { 0, 0 };
	//DWORD written;
	//CONSOLE_SCREEN_BUFFER_INFO csbi;
	//GetConsoleScreenBufferInfo(hConsole, &csbi);
	//DWORD size = csbi.dwSize.X;
	//FillConsoleOutputCharacter(hConsole, ' ', size, coord, &written);
	//FillConsoleOutputAttribute(hConsole, csbi.wAttributes, size, coord, &written);
	//SetConsoleCursorPosition(hConsole, coord);
}

void putc_at(char c, int x, int y, enum Color color) {
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	DWORD written;
	COORD position = { x, y };
	if (!color) {
		color = WHITE;
	}
	WORD col = (WORD)color;

	WriteConsoleOutputCharacterA(hConsole, &c, 1, position, &written);
	WriteConsoleOutputAttribute(hConsole, &col, 1, position, &written);
}