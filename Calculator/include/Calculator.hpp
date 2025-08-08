#pragma once
#include <iostream>
#include <conio.h>
#include <sstream>
using namespace std;

int getPriority(const string& operation);
bool isNumber(const string& str);
bool tryInfixToPostfix(string& expression);
bool tryCalculate(string& postfix, double& result);