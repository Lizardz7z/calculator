#define _CRT_SECURE_NO_WARNINGS
#include "OPN.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <ctype.h>

int temp, index = 0;
double TempValue = 0;
char ExpressionOPN[100] = { 0 };

double opn(char ExpressionNew[]) {
	index = 0;
	for (int i = 0; i < strlen(ExpressionNew); ++i)
		ExpressionOPN[i] = ExpressionNew[i];
	next();
	double res = addition();
	return res;
}

/*ïîñèìâîëüíî ñ÷èòûâàåì ñòðîêó, ôóíêöèè îïåðàöèé ñ íèçêèì ïðèîðèòåòîì âûçûâàþò
ôóíêöèè îïåðàöèé ñ âûñîêèì ïðèîðèòåòîì ïðè âû÷èñëåíèè*/
int next() {
	while (1) {
		int c = ExpressionOPN[index];
		ExpressionOPN[index++] = ' ';
		if (c == EOF || strchr("+-*/^()\n", c) != NULL) {
			TempValue = 0;
			return temp = c;
		}
		if (c == ' ' || c == '\n') {
			TempValue = 0;
			continue;
		}
		if (isdigit(c) || c == '.') {
			ExpressionOPN[--index] = c;
			sscanf(ExpressionOPN, " %lf", &TempValue);
			for (int i = 0; i < 100; ++i) {
				if (isdigit(ExpressionOPN[i]) == 0 && ExpressionOPN[i] != ' ' && ExpressionOPN[i] != '.')
					break;
				if (ExpressionOPN[i] != ' ') {
					ExpressionOPN[i] = ' ';
					index++;
				}
			}
			return temp = -1;
		}
		printf("Input error\n");
		return 0;
	}
}

//ïðîïóñêàåò çíàêè îïåðàöèé,ñêîáêè ïðè âû÷èñëåíèè
void skip(int t) {
	if (temp != t)
		return;
	next();
}
double addition();

// îáðàáîòêà ñèìâîëîâ "()"
double symbols() {
	if (temp == -1 || (temp == '-' && TempValue == 0)) {
		double x = TempValue;
		skip(-1);
		return x;
	}
	skip('(');
	double x = addition();
	skip(')');
	return x;
}

// âîçâåäåíèå â ñòåïåíü
double factor() {
	double x = symbols();
	if (temp == '^') {
		skip('^');
		x = pow(x, factor());
	}
	return x;
}

// óìíîæåíèå è âû÷èòàíèå
double multiplication() {
	double x = factor();
	while (1) {
		if (temp == '*') {
			skip('*');
			x *= factor();
		}
		else if (temp == '/') {
			skip('/');
			x /= factor();
		}
		else return x;
	}
}

// ñëîæåíèå è âû÷èòàíèå
double addition() {
	double x = multiplication();
	while (1) {
		if (temp == '+') {
			skip('+');
			x += multiplication();
		}
		else if (temp == '-') {
			skip('-');
			x -= multiplication();
		}
		else
			return x;
	}
}