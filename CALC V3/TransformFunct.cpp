#include "TransformFunct.h"
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#define _USE_MATH_DEFINES
#include <math.h>
#include <string.h>


int IsNotFunct(char exp[]) { //
	for (int i = 0; i < strlen(exp); ++i) {
		if (!(isdigit(exp[i]) || strchr("+-*/^(),.\n", exp[i]) != NULL))
			return -1;
	}
	return 0;
}

int Find(char exp[], char x[]) //ищет в exp подстроку x
{
	int check = 0;
	for (int i = 0; i < strlen(exp); ++i)
	{
		if (exp[i] == x[0])
		{
			check++;
			for (int j = 1; j < strlen(x); ++j)
			{
				++i;
				if (exp[i] == x[j])
					check++;
				else
				{
					i = i - j;
					break;
				}

			}
		}
		if (check == strlen(x))
			return i - strlen(x) + 1;
		check = 0;
	}
	return -1;
}

void Replace(char exp[], char buf[], char x[], int ukaz, int endofword) //заменяет в exp значение переменной на месте ukaz на ее значение x
{
	int t = 0;
	for (int i = 0; i < ukaz; ++i)
	{
		buf[i] = exp[i];
	}
	buf[strlen(buf)] = '(';
	for (int i = ukaz + 1; i < ukaz + strlen(x) + 1; ++i)
	{
		buf[i] = x[t];
		++t;

	}
	buf[ukaz + strlen(x) + 1] = ')';
	for (int i = ukaz + strlen(x) + 2; i > 0; ++i)
	{
		if (exp[endofword] != 0)
		{
			buf[i] = exp[endofword];
			endofword++;
		}
		else break;
	}
	Empty(exp);
	for (int i = 0; i < strlen(buf); ++i)
	{
		exp[i] = buf[i];
	}

}

void DeleteSpaces(char exp[], char buf[]) //удаляет пробелы и \n в exp
{
	int t = 0;
	for (int i = 0; i < strlen(exp); ++i)
		if (exp[i] != ' ' && exp[i] != '\n')
		{
			buf[t] = exp[i];
			++t;
		}
	for (int i = 0; i < strlen(exp); ++i)
	{
		if (i < strlen(buf))
		{
			exp[i] = buf[i];
		}
		else
		{
			exp[i] = 0;
		}
	}
	if (exp[strlen(exp) - 1] == '\n')
		exp[strlen(exp) - 1] = '\0';
}

void TwoSigns(char exp[]) //заменяет два подряд идущих знака на один
{
	char minus[3] = { 0 };
	char plus[3] = { 0 };
	minus[0] = '-';
	plus[0] = '+';
	char buf2[100] = { 0 };
	for (int i = 0; i < strlen(exp) - 1; ++i)
	{
		if (exp[i] == '+' && exp[i + 1] == '-')
		{
			Replace(exp, buf2, minus, i, i + 2);
		}
		if (exp[i] == '-' && exp[i + 1] == '-')
		{
			Replace(exp, buf2, plus, i, i + 2);
		}
	}
}

void Empty(char exp[]) // опустошает буфер exp
{
	int a = strlen(exp);
	for (int i = 0; i < a; ++i)
		exp[i] = 0;
}

double FindFunction(char NameFunct[], double expr, double arg2) //Определяет какую функцию нужно вызвать и вызывает её (второй аргумент можно передаь как ноль, если такового нет
{
	//printf("%g", exp);
	if (strcmp(NameFunct, "sin") == 0) {

		return sin(expr);
	}
	else if (strcmp(NameFunct, "cos") == 0) {

		return cos(expr);
	}
	else if (strcmp(NameFunct, "tg") == 0) {

		return tan(expr);
	}
	else if (strcmp(NameFunct, "ln") == 0) {
		{
			printf("Input data error\n");
			exit(1);
		}
		return log(expr);
	}
	else if (strcmp(NameFunct, "sqrt") == 0) {

		return sqrt(expr);
	}
	else if (strcmp(NameFunct, "abs") == 0) {

		return fabs(expr);
	}
	else if (strcmp(NameFunct, "exp") == 0) {

		return EXPONENT(expr);
	}
	else if (strcmp(NameFunct, "real") == 0) {

		//вызываем real
	}
	else if (strcmp(NameFunct, "imag") == 0) {

		//вызываем imag
	}
	else if (strcmp(NameFunct, "mag") == 0) {

		//вызываем mag
	}
	else if (strcmp(NameFunct, "phase") == 0) {

		//вызываем phase
	}
	else if (strcmp(NameFunct, "pow") == 0) {

		return pow(expr, arg2);
	}
	else if (strcmp(NameFunct, "log") == 0) {
		if (expr <= 0 || arg2 <= 0 || arg2 == 1)
		{
			printf("Input data error\n");
			exit(1);
		}
		return log(expr) / log(arg2);
	}
}

void PI_repl(char exp[])
{
	char pi[3] = { 0 };
	pi[0] = 'P';
	pi[1] = 'I';
	char PI[100] = { 0 };
	sprintf(PI, "%lf", M_PI);
	int pos = 0, eow = 0;
	char buf[100] = { 0 };
	while (pos != -1)
	{
		pos = Find(exp, pi);
		if (pos != -1)
		{
			eow = pos + strlen(pi);
			Replace(exp, buf, PI, pos, eow);
			Empty(buf);
		}
	}
}

void E_repl(char exp[])
{
	char e[2] = { 0 };
	e[0] = 'E';
	char E[100] = { 0 };
	sprintf(E, "%lf", M_E);
	int pos = 0, eow = 0;
	char buf[100] = { 0 };
	while (pos != -1)
	{
		pos = Find(exp, e);
		if (pos != -1)
		{
			eow = pos + strlen(e);
			Replace(exp, buf, E, pos, eow);
			Empty(buf);
		}
	}
}

double EXPONENT(double x)
{
	return exp(x);
}