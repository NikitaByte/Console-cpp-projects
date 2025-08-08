#define _USE_MATH_DEFINES

#include "../include/Calculator.hpp"
#include <iostream>
#include <stack>

int getPriority(const string& operation) {
	if (operation == "+" || operation == "-") return 1;
	else if (operation == "*" || operation == "/") return 2;
	else if (operation == "^") return 3;
	else if (operation == "sqrt") return 4;
	else return 0;
}

bool isNumber(const string& str) {
	if (str.empty()) return false;

	bool isDecimalPointFound = false;
	size_t start = 0;

	if (str[0] == '-' || str[0] == '+')
		start = 1;

	if (start == str.size())
		return false;

	for (size_t i = start; i < str.size(); ++i) {
		if (str[i] == '.') {
			if (isDecimalPointFound)
				return false;
			isDecimalPointFound = true;
		}
		else if (!isdigit(static_cast<unsigned char>(str[i])))
			return false;
	}

	return true;
}

bool tryInfixToPostfix(string& expression) {
	string postfix = ""; // Result in postfix form
	stack<string> stack; // Stack for operators and functions

	istringstream iss(expression); // Stream for splitting an expression into tokens
	string token;

	while (iss >> token) {

		// If token is a number or constant
		if (isNumber(token)) {
			if (token == "pi")
				postfix += to_string(M_PI) + " ";	// Add π constant
			else if (token == "e")
				postfix += to_string(M_E) + " ";	// Add e constant
			else
				postfix += token + " ";				// Add number or constant
		}

		// If token is a unary function
		else if (token == "sqrt")
			stack.push(token);						// Add sqrt function

		// If token is an open or close parenthesis
		else if (token == "(")
			stack.push(token);						// Add open parenthesis

		else if (token == ")") {

			// While the stack is not empty and the top element is not an open bracket
			while (!stack.empty() && stack.top() != "(") {
				postfix += stack.top() + " ";
				stack.pop();
			}

			// If is an unmatched closing parenthesis
			if (!stack.empty() && stack.top() == "(") {
				stack.pop();
			}

			// If the top of the stack is a unary function (sqrt)
			if (!stack.empty() && stack.top() == "sqrt") {
				postfix += stack.top() + " ";
				stack.pop();
			}
		}

		// If token is an operator
		else if (token == "+" || token == "-" ||
			token == "*" || token == "/" ||
			token == "^") {

			// As long as the stack is not empty and the priority of the current operator is lower or equal
			while (!stack.empty() &&
				(getPriority(stack.top()) > getPriority(token) ||
					(getPriority(stack.top()) == getPriority(token) && token != "^"))) {
				postfix += stack.top() + " ";
				stack.pop();
			}

			stack.push(token);						// Add the current operator
		}

		// If token is an unknown token
		else {
			cerr << "Unknown token: " << token << endl;
			cerr << "Error: Unable to convert expression to postfix form." << endl;
			return false;
		}
	}

	// After reading all tokens, clear the stack
	while (!stack.empty()) {
		string operation = stack.top();
		stack.pop();
		postfix += operation + " ";
	}

	expression = postfix; // We keep the postfix form in the original expression.

	return true;
}

bool tryCalculate(string& postfix, double& result) {
	result = 0;
	stack<string> stack; // Operand stack

	istringstream iss(postfix); // Stream for splitting an expression into tokens
	string token;

	while (iss >> token) {

		// If the token is a constant pi or e
		if (token == "pi") {
			stack.push(to_string(M_PI));			// Add π constant
			continue;
		}
		else if (token == "e") {
			stack.push(to_string(M_E));				// Add π constant
			continue;
		}

		// If the token is a number or constant
		if (isNumber(token))
			stack.push(token);						// Add number or constant

		// If the token is a unary function (sqrt)
		else if (token == "sqrt") {

			// If the stack is empty, we cannot perform the sqrt operation
			if (stack.empty()) {
				cerr << "Error: Not enough arguments for the sqrt function." << endl;
				return false;
			}

			double a = stod(stack.top());			// Convert the top element of the stack to a number
			stack.pop();

			// If the number is negative, we cannot calculate the square root
			if (a < 0) {
				cerr << "Error: Root of a negative number." << endl;
				return false;
			}

			result = sqrt(a);						// Calculating the root
			stack.push(to_string(result));			// Add the result back to the stack
		}

		else {
			char operation = token[0];				// Get the first character of the token as the operation

			// If the stack does not have enough elements for the operation, we cannot perform it
			if (stack.size() < 2) {
				cerr << "Error: Insufficient arguments for operation " << operation << "." << endl;
				return false;
			}

			double b = stod(stack.top());			// Convert the top element of the stack to a number
			stack.pop();
			double a = stod(stack.top());			// Convert the next top element of the stack to a number
			stack.pop();

			// Determine the operation
			switch (operation) {
			case '+': result = a + b; break;
			case '-': result = a - b; break;
			case '*': result = a * b; break;
			case '/': {

				// If the second operand is zero, we cannot perform division
				if (b == 0) {
					cerr << "Error: Division by zero." << endl;
					return false;
				}

				result = a / b;
			} break;
			case '^': result = pow(a, b); break;

			default:
				cerr << "Unknown operation: " << operation << endl;
				return false;
			}

			stack.push(to_string(result));			// Add the result back to the stack
		}
	}

	// If there is only one element left in the stack, it is the result
	if (stack.size() != 1) {
		cerr << "Error: There are extra elements left in the stack" << endl;
		return false;
	}

	result = stod(stack.top());						// Convert the final result to a number

	return true;
}