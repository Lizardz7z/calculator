#ifndef TranformFunct_H
#define TranformFunct_H


int Find(char exp[], char x[]);
void Replace(char exp[], char buf[], char x[], int ukaz, int endofword);
void DeleteSpaces(char exp[], char buf[]);
void TwoSigns(char exp[]);
void Empty(char exp[]);
double FindFunction(char NameFunct[], double expr, double arg2);
int IsNotFunct(char exp[]);

void PI_repl(char exp[]);
void E_repl(char exp[]);

double EXPONENT(double x);
#endif