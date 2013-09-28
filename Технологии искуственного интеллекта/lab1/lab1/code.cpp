#include <stdio.h>
#include <string>
#include <iostream>
#include <fstream>

using namespace std;

int fact(int x)
{
	if (x != 1) 
	{
		return x*fact(x-1);
	}
	else
		return x;
};

int fib(int n)
{
	if ((n < 2))
	{
		return 1;
	}
	else
	{
		return fib(n-1)+fib(n-2);
	}
}

int fib2(int n, int f1, int f2)	// быстрый подсчёт фиб рекурсией
{
	if ((n < 2))
	{
		return f2;
	}
	else
	{	
		return fib2(n-1,f2,f1+f2);
	}
}

int getfib (int n)	// обёртка
{
	return fib2 (n,1,1);
}

void printBit (string x, int cur, int max, int countX, int countXMax)
{
	if (cur == max)
	{
		if (countXMax == countX)
			cout << x << "\n";
		return;
	}

	if (max - countX >= max - countXMax)
		printBit (x + "0 ",cur+1,max, countX, countXMax);	
	
	if (countX < countXMax)
		printBit (x + "1 ",cur+1,max, countX+1, countXMax);	
	
}

void printBit2 (string x, int count0, int count0Max, int count1, int count1Max)
{
	if (count1 + count0 == count1Max + count0Max)
	{
			cout << x << "\n";
			return;
	}

	if (count0 < count0Max)
		printBit2 (x + "0 ",count0+1, count0Max, count1, count1Max);	
	
	if (count1 < count1Max)
		printBit2 (x + "1 ",count0, count0Max, count1+1, count1Max);	
	
}

void main()
{
/*	int x = 5;
	int factX;
	factX = fact(x);
	printf("fac = %d\n",factX);
	int fibX;
	fibX = getfib(35);
	printf("fib = %d\n",fibX);
	printf("-----\n");*/
//	freopen("asd.txt", "w", stdout);
	printBit2("",0,1,0,29);
}