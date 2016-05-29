// MyDll.cpp: определяет точку входа для консольного приложения.
// compile with: /EHsc /link MathFuncsDll.lib
#include "MathFuncsDll.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
using namespace std;

int main(int argc, char* argv[])
{
	bool bin, res;
	int base = 10;
		bool ModBool = true;
		printf("Enter string in such way:\n");
		printf("[name of program] [file1] [operator] [file2] [result file] [-b] [mod file]\n");
	char *file1 = argv[1];
	char *oper = argv[2];
	char *file2 =argv[3];
	char *resf = argv[4];
	char *binMark = argv[5];
	char *modFile = argv[6];

	if (argc < 2)
		return 0;

	if (argc > 8)
	{
		printf("\nToo many parameters.\n");
		return 0;
	}

	if ((argc > 1) && (argc < 6))
	{
		printf("\nIntroduced not all parameters.\n");
		return 0;
	}
	if(argc < 7)
	{
		ModBool = false;
	}
	if(argc == 7)
	{
		ModBool = true;
	}
	if (strlen(argv[2]) > 1)
	{
		printf("Invalid input operation.\n");
		return 0;
	}
	if(strcmp(binMark,"-b") == 0) 
	{ 
		bin = true;
	}
	else
	{
		bin = false;
	}
	BigInt a = a.Read(file1,base, bin);
	/*if (a == 0)
		return 0;*/
	BigInt b = b.Read(file2,base, bin);
	/*if (b == 0)
		return 0;*/
	if(oper[0] == '+') a = a + b;
	else if(oper[0] == '-') a = a - b;
	else if(oper[0] == '*') a = a * b;
	else if(oper[0] == '/') a = a / b;
	else if(oper[0] == '%') a = a % b;
	else if(oper[0] == '^')
	{
		if(ModBool == true)
		{
			BigInt m = m.Read(modFile, base, bin);
			a = a.Power(a,b,m);
		}
		else
		{
			printf("\nerror: mod file not found!");
			return 0;
		}
	}
	if(ModBool)
	{
		BigInt m = m.Read(modFile,base,bin);
		a = a % m;
	}
	a.Write(resf, bin);
	printf("\nOperation was succesfully done!");
	return 0;
}

