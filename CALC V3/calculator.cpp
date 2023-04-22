#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <tgmath.h>
#include <complex.h> 
#include <string.h>
#include "OPN.h"
#include "TransformFunct.h"
#include <ctype.h>

//sin(cos(pow(a,b)))
//a=PI
//b=1

void FunctTwoArg(char exp[], double* arg1, double* arg2) {
	char param1[100] = { 0 }, param2[100] = { 0 }; int flag = 0, index = 0;

	for (int i = 1; i < strlen(exp) - 1; ++i) {
		if (flag == 0 && exp[i] != ',')
			param1[i - 1] = exp[i];
		else if (flag == 1 && exp[i] != ',')
			param2[index++] = exp[i];
		if (exp[i] == ',')
			flag = 1;
	}
	*arg1 = opn(param1);
	*arg2 = opn(param2);


}

double FunctProcess(char exp[]) { //обработка выражения с функциями
	while (1) {
		char function[20] = { 0 }, buf[100] = { 0 }, ExpressionNew[100] = { 0 };
		int indexfunct = 0, indexstr = 0, count = 0, pos = 0, eow = 0;
		double arg1 = 0, arg2 = 0;
		int length = 0;
		for (int i = 0; i < strlen(exp); ++i) {
			if (!(isdigit(exp[i])) && strchr("+-*/^(),.\n", exp[i]) == NULL)
				function[indexfunct++] = exp[i]; //название функции 

			else if (function[0] != 0) {
				for (int j = i; j < strlen(exp); ++j) {
					ExpressionNew[indexstr++] = exp[j]; //выражение от которого вычесляется функция
					if (exp[j] == ')')
						count--;
					else if (exp[j] == '(')
						count++;
					length = strlen(ExpressionNew);
					if ((strcmp(function, "pow") == 0 || strcmp(function, "log") == 0) && count == 0) {
						FunctTwoArg(ExpressionNew, &arg1, &arg2);
						double x = FindFunction(function, arg1, arg2); //вычисление значения функции
						char xstr[100] = { 0 };
						sprintf(xstr, "%lf", x);
						pos = Find(exp, function);
						eow = pos + strlen(ExpressionNew) + strlen(function);
						Replace(exp, buf, xstr, pos, eow); //подставляем найденное значение в исходное выражение
						Empty(buf);
						break;
					}
					else {
						if (count == 0 && IsNotFunct(ExpressionNew) == -1) {
							double temp = FunctProcess(ExpressionNew); //вычисление значения вложенной функции
							char xstr[100] = { 0 };
							sprintf(xstr, "%lf", temp);
							pos = Find(exp, ExpressionNew);
							eow = pos + strlen(ExpressionNew);
							Replace(exp, buf, xstr, pos, eow); //подставляем найденное значение в исходное выражение
							Empty(buf);
						}
						if (count == 0 && IsNotFunct(ExpressionNew) == 0) {

							double x = FindFunction(function, opn(ExpressionNew), 0); //вычисление значения функции
							char xstr[100] = { 0 };
							sprintf(xstr, "%lf", x);
							pos = Find(exp, function);
							eow = pos + strlen(ExpressionNew) + strlen(function);
							Replace(exp, buf, xstr, pos, eow); //подставляем найденное значение в исходное выражение
							Empty(buf);
							break;
						}
					}
				}
				break;
			}
		}
		//проверка на наличие функций в выражении
		int flag = 0;
		for (int i = 0; i < strlen(exp); ++i) {
			if (!(isdigit(exp[i]) || strchr("+-*/^().\n", exp[i]) != NULL))
				flag = 1;
		}
		if (flag == 0) {
			double res = opn(exp);
			return res;
			break;
		}
	}
}

char expression[100], buf[100] = { 0 }, buf1[100] = { 0 }, buf3[100] = { 0 }, xy[100] = { 0 }, znach[100] = { 0 };
int temp1 = 0, t1 = 0, pos = 0, eow = 0;
FILE* fr;
FILE* fw;

int main() {
	fr = fopen("input.txt", "rt");
	fw = fopen("output.txt", "wt");
	fgets(expression, 100, fr);
	fprintf(fw, "%s", expression);
	printf("%s", expression);
	while (fgets(buf1, 100, fr))
	{
		fprintf(fw, "%s", buf1);
		printf("%s", buf1);
		DeleteSpaces(buf1, buf3);
		Empty(buf3);
		t1 = 0;
		Empty(xy);
		Empty(znach);
		for (int i = 0; i < strlen(buf1); ++i)
		{
			if (buf1[i] == '=')
				temp1 = 1;
			else
			{
				if (temp1 == 0)
					xy[i] = buf1[i];
				else
				{
					znach[t1] = buf1[i];
					++t1;
				}
			}
		}
		while (pos != -1)
		{
			pos = Find(expression, xy);
			if (pos != -1)
			{
				eow = pos + strlen(xy);
				Replace(expression, buf, znach, pos, eow);
				Empty(buf);
			}
		}
		temp1 = 0, pos = 0;
	}
	E_repl(expression);
	PI_repl(expression);
	DeleteSpaces(expression, buf);
	double result = FunctProcess(expression);
	printf("\nAnswer: %.5g\n", result);
	fprintf(fw, "\nAnswer: %.5g\n", result);

	fclose(fr);
	fclose(fw);

	return 0;
}