// MathFuncsDll.cpp: определяет экспортированные функции для приложения DLL.
//

//#include "stdafx.h"
#include <stdio.h>
#include <stdlib.h>
#include "MathFuncsDll.h"
#include "math.h"
#include <stdexcept>

using namespace std;

BigInt::BigInt(int num)
{
	base = 10;
	value = DigitToArray(num,base);
}
BigInt::BigInt(const BigInt &a)
{
	value = CopyArray(value,a.value,false);
	base = a.base;
}
//Operators Overloading
BigInt BigInt::operator+(const BigInt& rv) {
	BigInt temp;
	if(base == 10)
	{
		if(CheckNegative(value) == CheckNegative(rv.value))
			temp.value = Addition(value,rv.value,value,base);
		else
			temp.value = Subtraction(value,rv.value,value,base);
	}
	else temp.value = Addition(value,rv.value,value,base);
	temp.base = base;
	return temp;
	}
BigInt BigInt::operator-(const BigInt& rv){
	BigInt temp;
	if(base == 10)
	{
		if(CheckNegative(value) != CheckNegative(rv.value))
		{
			rv.value[0] *= -1;
			int* t = Addition(value,rv.value,value,10);
			rv.value[0] *= -1;
			temp.value = t;
		}
		else
			temp.value = Subtraction(value,rv.value,value,10);
	}
	else temp.value = Subtraction(value,rv.value,value,10);
	temp.base = base;
	return temp;
}
	
BigInt BigInt::operator*(const BigInt& rv) {
	BigInt temp;
	temp.value = Multiplication(value,rv.value,value,base);
	temp.base = base;
	return temp;
}
BigInt BigInt::operator/(const BigInt& rv) {
	BigInt temp;
	temp.value = Dividing(value,rv.value,value,false,base);
	temp.base = base;
	return temp;
}

BigInt BigInt::operator%(const BigInt& rv)  {
	BigInt temp;
	temp.value = Mod(value,rv.value,base);
	temp.base = base;
	return temp;
}
bool BigInt::operator==(const BigInt& rv) {
	if(value == MinMax(value,rv.value,'M') && value == MinMax(value,rv.value,'m'))
		return true;
	else return false;
}
bool BigInt::operator!=(const BigInt& rv) {
	if(value == MinMax(value,rv.value,'M') && value == MinMax(value,rv.value,'m'))
		return false;
	else return true;
}
bool BigInt::operator>=(const BigInt& rv)  {
	if((value == MinMax(value,rv.value,'M') && value == MinMax(value,rv.value,'m')) || value == MinMax(value,rv.value,'M'))
		return true;
	else return false;
}

bool BigInt::operator<=(const BigInt& rv) {
	if((value == MinMax(value,rv.value,'M') && value == MinMax(value,rv.value,'m')) || rv.value == MinMax(value,rv.value,'M'))
		return true;
	else return false;
}

bool BigInt::operator<(const BigInt& rv)  {
	if(rv.value == MinMax(value,rv.value,'M'))
		return true;
	else return false;
}

bool BigInt::operator>(const BigInt& rv) {
	if(rv.value == MinMax(value,rv.value,'m'))
		return true;
	else return false;
}
//Other functions
BigInt BigInt::Print()
	{
		PrintMass(BigInt::value);
		return *this;
	}
BigInt BigInt::Read(char* fileName,int b, bool bin)
	{
		value = ReadFile(fileName,bin);
		base = b;
		return *this;
	}
BigInt BigInt::Write(char* fileName,bool bin)
	{
		WriteFile(value,fileName,bin);
		return *this;
	}
BigInt BigInt::Convert(int n)
	{
		value = DigitToArray(n,10);
		base = 10;
		return *this;
	}
BigInt BigInt::Copy(BigInt a)
	{
		free(value);
		value = CopyArray(value,a.value,false);
		base = a.base;
		return *this;
	}
BigInt BigInt::Power(BigInt a,BigInt b,BigInt m)
{
		BigInt res;
		value = Pow(a.value,b.value, value, m.value, a.base);//function from three arguments
		base = a.base;
		return *this;
}
//=======================
int* BigInt::ReadFile(char* fileName,bool bin)
{
	int *mas = NULL;
    char* flag;
	char c;
    if(bin == false) 
		flag = "r";
    else
		flag = "rb";
    FILE *fp = fopen(fileName, flag);
    if(NULL == fp)
	{
		printf("\nCan't open file %s", fileName);
		return 0;
	}
    fseek(fp,0,SEEK_END);
	int size = ftell(fp);
	if (size == 0)
	{
		printf("\nerror: File %s is empty!", fileName);
		return 0;
	}
    fseek(fp, 0, SEEK_SET);
	if (bin == false)
	{
		char c;
		fscanf(fp,"%c",&c);
		if (!(c>='0' && c<='9' || (c == '-')))
		{ 
			printf("\nerror: Incorrect data in %s\n",fileName);
			fclose(fp);
			return 0;
		}
		for( int i = 1; i < size; i++)
		{
			fscanf(fp,"%c",&c);
			if (!(c>='0' && c<='9'))
			{ 
				printf("\nerror: Incorrect data in %s\n",fileName);
				fclose(fp);
				return 0;
			}
		}
	}else
	{
		char c=0;
		fread(&c, sizeof(char), 1, fp);
		if(!(c>='0' && c<='9' || (c == '-')))
		{
			printf("\nerror: Incorrect data %s\n",fileName);
			fclose(fp);
			return 0;
		}
		for(int i = 1; i < size; i++)
		{
			fread(&c, sizeof(char), 1, fp);
			if(!(c>='0' && c<='9'))
			{
				printf("\nerror: Incorrect data %s\n",fileName);
				fclose(fp);
				return 0;
			}
		}
	}
	fseek(fp, 0, SEEK_SET);
	mas = (int*) malloc((size+2)*sizeof(int));
	if(bin == false) 
		for(int i = size; i > 0; i--) 
			mas[i] = fgetc(fp) - 48;
    else 
		for (int i = size; i > 0; i--) 
			mas[i] = fgetc(fp)-'0';
	mas[0] = size;
    fclose(fp);
    return mas;
	if(mas[mas[0]] == -3)
    {
         mas[0]--;
         mas[0]*=-1;
    }
    return mas;
}

bool BigInt::CheckNegative(int* mas)
{
	if(mas[0]<0) 
		return true;
	else 
		return false;
}
void BigInt::reverse_num(int* &num,int size)
{
	int buff;
	for(int i=0;i<(size+1)/2;++i)
	{
		buff=num[i];
		num[i]=num[size-i];
		num[size-i]=buff;
	}
}
void BigInt::WriteFile(int *mas,char *fileName,bool bin)
{
    char* flag;
	bool negative = CheckNegative(mas);
	if(negative) mas[0]*=-1;

    char c;
    if(bin == false) 
		flag = "w";
    else 
		flag = "wb+";
	FILE *fp = fopen(fileName, flag);
	if(bin == false)
    {
        if(negative) 
			fprintf(fp,"-");
        for(int i=mas[0]; i>0; i--) 
			fprintf(fp,"%d",mas[i]);
    }
	else 
	{
		if(negative) 
			putc('-', fp);
		int s = mas[0];
		reverse_num(mas, mas[0]);
		for (int i= 0; i < s; i++)
		{		
			c = mas[i] + '0';
			putc(c,fp);
		}
	}
	fclose(fp);
	printf("\nResult was written to the file %s.\n",fileName);
}

int* BigInt::DigitToArray(int d,int base)
	{
		bool negative = false;
		if(d<0)
		{
			negative = true;
			d*=-1;
		}
		int size = 1;
		while(d>=pow((double)base,size)) 
			size++;
		int* arr = (int*) malloc((size+2)*sizeof(int));
		arr[0] = size;
		for(int i = 0;i<size;i++)
		{
			arr[i+1] = d % base;
			d /= base;
		}
		if(negative) 
			arr[0]*=-1;
		return arr;
	}

int* BigInt::MinMax(int* a,int* b,char type)
{
	bool A_negative = CheckNegative(a);
	bool B_negative = CheckNegative(b);
    if (a[0] > b[0])
    {
        if(type == 'm') return b;
        if(type == 'M') return a;
    }
    else if (a[0] < b[0])
    {
        if(type == 'm') return a;
        if(type == 'M') return b;
    }
    else
    {
		if(A_negative) a[0]*=-1;
		if(B_negative) b[0]*=-1;

        for(int i = a[0];i>0;i--)
        {
            if(a[i] > b[i])
            {
				if (A_negative && B_negative)
				{
					a[0]*=-1;
					b[0]*=-1;
					if(type == 'm') return a;
					if(type == 'M') return b;
				} 
				else
				{
					if(type == 'm') return b;
					if(type == 'M') return a;
				}
             }
            else  if(a[i] < b[i])
            {
				if (A_negative && B_negative)
				{
					a[0]*=-1;
					b[0]*=-1;
					if(type == 'm') return b;
					if(type == 'M') return a;
				} 
				else
				{
					if(type == 'm') return a;
					if(type == 'M') return b;
				}
            }
        }
    }
    return a;
}

int* BigInt::DeleteNull(int* c)
 {
    for(int i = c[0]; i>1; i--)
	{
		if( !(c[0] == 1 && c[1] == 0))
		{
			if(c[i] == 0) c[0]--;
			else break;
		}
		else break;
	}
	return c;
}
void BigInt::PrintMass(int* a)
{
	bool neg = CheckNegative(a);
	if(neg)
	{
		a[0]*=-1;
		printf("-");
	}
	for(int i = a[0];i>0;i--)
    {
      printf("%d",a[i]);
    }
	if(neg) a[0]*=-1;
	
}
int* BigInt::CopyArray(int* arr, int* source, bool Memory)
{
	bool negative = CheckNegative(source);
	if(negative) source[0]*=-1;
	
    if (!Memory)
        arr = (int*) malloc((source[0]+2)*sizeof(int));
    for(int i = 0;i<=source[0];i++)
        arr[i] = source[i];
		
	if(negative)
	{	
		arr[0]*=-1;
		source[0]*=-1;
	}
    return arr;
}


int* BigInt::Addition(int *a, int *b,int *c,int base)
{
	bool A_negative = CheckNegative(a);
	bool B_negative = CheckNegative(b);
	if(A_negative) 
		a[0]*=-1;
	if(B_negative) 
		b[0]*=-1;
	
    int* min = MinMax(a,b,'m');
    int* max = MinMax(a,b,'M');
    c = (int*) malloc((max[0]+2)*sizeof(int));
    c[0] = max[0] + 1;
    for(int i =1;i<c[0]+1;i++) 
		c[i] = 0;
	for (int i = 1; i < c[0]; i++)
    {
        if(i < min[0]+1)
            c[i] += min[i] + max[i];
        else
            c[i] += max[i];
            c[i + 1] += (c[i] / base);
            c[i] %= base;
    }
    c = DeleteNull(c);
	if(A_negative && B_negative) c[0]*=-1;
	if(A_negative) a[0]*=-1;
	if(B_negative) b[0]*=-1;
	return c;
}

int* BigInt::Subtraction(int *a,int *b,int *c,int base)
{
	bool A_negative = CheckNegative(a);
	bool B_negative = CheckNegative(b);
	if(A_negative) a[0]*=-1;
	if(B_negative) b[0]*=-1;

    int buf = 0, borrow = 0;
    int* min = MinMax(a,b,'m');
    int* max= MinMax(a,b,'M');
    c = (int*) malloc((max[0]+2)*sizeof(int));
    c[0] = max[0] + 1;
    for(int i =1;i<c[0]+1;i++) 
		c[i] = 0;
   	for(int i=1;i<c[0];i++)
	{
        if(i < min[0]+1) 
			buf = max[i] - min[i] - borrow;
		else buf = max[i] - borrow;
		if(buf>=0) {
			c[i] = buf;
			borrow = 0;
		}
		else {
			c[i] = base + buf;
			borrow = 1;
		}
	}
	c = DeleteNull(c);

	if(!A_negative)
	{
		if(a != MinMax(a,b,'M')) 
			c[0] *= -1;
	}
	else
	{
		if(b == MinMax(a,b,'m')) 
			c[0] *= -1;
	}
	if(A_negative) a[0]*=-1;
	if(B_negative) b[0]*=-1;
	return c;
}
int* BigInt::Multiplication(int *a,int *b,int *c,int base)
{
	bool A_negative = CheckNegative(a);
	bool B_negative = CheckNegative(b);
	if(A_negative) 
		a[0]*=-1;
	if(B_negative) 
		b[0]*=-1;

    c = (int*) malloc((a[0]+b[0]+2)*sizeof(int));
    c[0] = a[0]+b[0]+1;
    for(int i =1;i<c[0]+1;i++) 
		c[i] = 0;
	for (int i = 1; i<= a[0]; i++)
		for (int j = 1; j <= b[0]; j++)
			c[i + j - 1] += a[i] * b[j];
	for (int i = 1; i < c[0]; i++)
	{
		c[i + 1] +=  c[i] / base;
		c[i] %= base;
	}
	c = DeleteNull(c);

	if(A_negative != B_negative) 
		c[0]*=-1;
	if(A_negative) 
		a[0]*=-1;
	if(B_negative) 
		b[0]*=-1;
    return c;
}

int* BigInt::DivideOnDigit(int* mas, int digit, int* answer,bool retR,int base)
{
    if(digit == 0)
    {
        printf("Error! Dividing on zero value\n");
        return mas;
    }
    int ms = mas[0];
    answer = (int*) malloc((mas[0]+2)*sizeof(int));
    answer[0] = 0;
    int r = 0;
    int j = mas[0];
    while(j>0)
    {
        int cur = r * base + mas[j];
        answer[j] = (int)(cur/digit);
        r = (int)(cur % digit);
        j--;
        answer[0] ++;
    }
    answer[answer[0]+1]=r;
    if(retR)
    {
        int* r2 = DigitToArray(r,base);
        CopyArray(answer,r2,true);
        free(r2);
        return answer;
    }
    else return answer;
}
int* BigInt::Dividing(int* u,int* v,int* q,bool retR,int base)
{
	int* saveRightPart = NULL;
	int* saveLeftPart = NULL;
	saveRightPart = CopyArray(saveRightPart,v,false);
	saveLeftPart = CopyArray(saveLeftPart,u,false);
	
	bool U_negative = CheckNegative(u);
	bool V_negative = CheckNegative(v);
	if(U_negative) 
		u[0]*=-1;
	if(V_negative) 
		v[0]*=-1;

    int* f = NULL;
    int* tempV = NULL;
    if(v[0] == 1)
    {
        f = DivideOnDigit(u,v[1],f,retR,base);
        f = DeleteNull(f);
		if(U_negative != V_negative) f[0]*=-1;
		if(U_negative) u[0]*=-1;
		if(V_negative) v[0]*=-1;
        return f;
    }
    int n = v[0];
    int m = u[0] - v[0];
    q = (int*) malloc((u[0]+2)*sizeof(int));
    int* u2 = (int*) malloc((u[0]+2)*sizeof(int));
    q[0] = m+1;
    int* comp = (int*) malloc((n+2)*sizeof(int));
    int d = (base / (v[n] + 1));
    f = Multiplication(u,DigitToArray(d,base),f,base);
    if(f[0] == n+m)
    {
        f[f[0]+1] = 0;
        f[0]++;
    }
    u = CopyArray(u,f,true);
    free(f);
    f = Multiplication(v,DigitToArray(d,base),f,base);
    v = CopyArray(v,f,true);
    free(f);
    for(int j=m;j>=0;j--)
    {
        int cur = (u[j + n+1]) * base + u[j + n];
        int tempq = (int)(cur / v[n]);
        int tempr = (int)(cur % v[n]);
        do
        {
            if (tempq == base || (tempq * v[n - 2+1] > base * tempr + u[j+n-2+1]))
            {
                tempq--;
                tempr += v[n];
            }
            else break;
        }
        while(tempr < base);
        tempV = Multiplication(v,DigitToArray(tempq,base),tempV,base);
        int it = 1;
        for(int i=j+1;i<=n+j+1;i++)
        {
            int ag = u[i];
            u2[it] = u[i];
            u[i] = 0;
            it++;
        }
        u2[0] = n+1;
        bool signFlag = false;
        int saveNules = 0;
        for( int i=u2[0];i>1;i--)
        {
            if(u2[i] == 0)
            {
                u2[0]--;
                saveNules++;
            }
            else break;
        }
        if(u2 == MinMax(u2,tempV,'m') && u2 != MinMax(u2,tempV,'M')) signFlag = true;
        u2[0] = u2[0] + saveNules;
        int* f2 = NULL;
		f2 = Subtraction(u2,tempV,f2,base);
        u2 = CopyArray(u2,f2,true);
        free(f2);
        if(signFlag)
        {
            for (int i = 1; i <= n; i++) comp[i] = 0;
            comp[n+1] = 1;
            comp[0] = n+1;
            f = Subtraction(comp,u2,f,base);
            u2 = CopyArray(u2,f,true);
            free(f);
        }
        q[j+1] = tempq;
        if (signFlag)
        {
            q[j+1]--;
            int *f3 = Addition(u2,v,f3,base);
            u2 = CopyArray(u2,f3,true);
            u2[0]--;
            free(f3);
        }
        for(int i=1;i<=u2[0];i++) u[j+i] = u2[i];
    }
    q = DeleteNull(q);
    while(u[0]>n)
        u[0]--;
    int* r = NULL;
    r = DivideOnDigit(u,d,r,false,base);
    r = DeleteNull(r);
    free(tempV);
    free(comp);
    free(u2);
	
	if(U_negative != V_negative) q[0]*=-1;
	if(U_negative) u[0]*=-1;
	
	v = CopyArray(v,saveRightPart,true);
	u = CopyArray(u,saveLeftPart,true);
	
    if(retR)
    {
        free(q);
        return r;
    }
    else
    {
        free(r);
        return q;
    }
}
int* BigInt::Pow(int* a,int* b,int* c, int *m, int base)
 {
	bool A_negative = CheckNegative(a);
	bool B_negative = CheckNegative(b);
	bool paritet = false;
	if(b[1]%2!=0) 
		paritet = true;
	if(B_negative)
	{
		printf("\nSecond value can't be negative!");
		return 0;
	}
	if(A_negative) a[0]*=-1;
	
    int *new_a = Mod(a,m,base);
	free(a);
	a=new_a;

    int* f = NULL;
	c = DigitToArray(1,base);
    int* one = DigitToArray(1,base);

    while(!(b[0]==1 && b[1] ==0))
    {
		 int* temp = NULL;
		 temp = DivideOnDigit(b,2,temp,true,base);
         int* q = DivideOnDigit(b,2,temp,false,base);
         if(temp[1] == 0 && temp[0] == 1)
         {
            /* for (int i = 0; i < b[0]+1; i++)
			 {
				 b[i] = 0;
			 }*/
             b = q;
             f = Multiplication(a,a,f,base);
			 for (int i = 0; i < a[0]+1; i++)
			 {
				 a[i] = 0;
			 }
			 a = Mod(f,m,base);
			 for (int i = 0; i < f[0]+1; i++)
			 {
				 f[i] = 0;
			 }
         }
         else{
            for (int i = 0; i < q[0]+1; i++)
			 {
				 q[i] = 0;
			 }
            f = Subtraction(b,one,f,base);
			b = CopyArray(b,f,true);
		    free(f);
            f = Multiplication(c,a,f,base);
            free(c);
			c = Mod(f,m,base);
			free(f);	
			}	
     }

	if(A_negative && paritet) c[0]*=-1;
	if(A_negative) a[0]*=-1;

     return c;
 }
int* BigInt::Mod(int* a,int* b,int base)
 {
    int* m = NULL;
	m = Dividing(a,b,m,true,base);
    return m;
 }

