// MathFuncsDll.h

#ifdef MATHFUNCSDLL_EXPORTS
#define MATHFUNCSDLL_API __declspec(dllexport) 
#else
#define MATHFUNCSDLL_API __declspec(dllimport) 
#endif
#include <iostream>
using namespace std;

class BigInt
{
private:
	int* value;
	int base;
	int* DigitToArray(int d,int base);
	int* DeleteNull(int* c);
	int* MinMax(int* a,int* b,char type);
	void PrintMass(int* a);
	int* CopyArray(int* arr, int* source, bool Memory);
	bool CheckNegative(int* mas);
	int* ReadFile(char* fileName,bool bin);
	void reverse_num(int* &num,int size);
	void WriteFile(int *mas,char *fileName,bool bin);
// Arithmetic Operations
	int* Addition(int *a, int *b,int *c,int base);
	int* Subtraction(int *a,int *b,int *c,int base);
	int* Multiplication(int *a,int *b,int *c,int base);
	int* DivideOnDigit(int* mas, int digit, int* answer,bool retR,int base);
	int* Dividing(int* u,int* v,int* q,bool retR,int base);
	int* Pow(int* a,int* b,int* c, int *m, int base);
	int* Mod(int* a,int* b,int base);
public:
//Constructor
	BigInt(){};
	BigInt(int num);
	BigInt(const BigInt &a);
	
//Operators Overloading
	BigInt operator+(const BigInt& rv);
	BigInt operator-(const BigInt& rv);
	BigInt operator*(const BigInt& rv);
	BigInt operator/(const BigInt& rv);
	BigInt operator%(const BigInt& rv);
	bool operator==(const BigInt& rv);
	bool operator!=(const BigInt& rv);
	bool operator>=(const BigInt& rv);
	bool operator<=(const BigInt& rv);
	bool operator<(const BigInt& rv);	
	bool operator>(const BigInt& rv);
		
//Other funcs
	BigInt Print();
	BigInt Read(char* fileName,int b, bool bin);
	BigInt Write(char* fileName, bool bin);
	BigInt Convert(int n);
	BigInt Copy(BigInt a);
	BigInt Power(BigInt a,BigInt b,BigInt m);
};