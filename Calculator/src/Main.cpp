#include "../include/Calculator.hpp"

// Variables
bool running = true;

int main()
{
	system("chcp 1251");

	// Main loop
	while (running) {
		system("cls");
		string expression;	// Input expression in infix form

		cout << "Calculator" << endl;

		cout << "Enter expression: ";
		getline(cin, expression);

		double result;
		if (tryInfixToPostfix(expression) &&
			tryCalculate(expression, result))
			cout << "Result: " << result << endl;

		// Prompt for continuation
		cout << "Would you like to continue? (y/n)";
		
		char ch = _getch();
		if (ch != 'y' && ch != 'Y')
			running = false;
	}

	return EXIT_SUCCESS;
}