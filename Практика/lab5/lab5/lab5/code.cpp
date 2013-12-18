#include <iostream>
#include <stdio.h>
#include <fstream>
#include <string>
using namespace std;

#define TAP_COMPILE
#include "libtap\vs_tap.h"


int getSum (string s)
{
	int sum,length;
	length = s.length();
	sum = 0;
	for (int j = 0; j < length; j++)
		{
			if (s[j] == '1')
			{
				sum = sum + j + 1;
			}
		}
	return sum;
}

int getNumberOne (string s)
{
	int sum,length;
	length = s.length();
	sum = 0;
	for (int j = 0; j < length; j++)
		{
			if (s[j] == '1')
			{
				sum++;
			}
		}
	return sum;
}

string delnoise(string s, int sum, int n)
{
	int sumOld = sum;
	int index;
	bool fl = false;
	while (fl == false)
	{
		sumOld--;
		if (sumOld %(n+1) == 0)
		{
			fl = true;
		}
	}
	index = sum - sumOld;
	s[index-1] = '0';
	//cout << s << endl;
	return s;
}

string delnoiseMore(string s, int n)
{
	int j = 0;
	bool fl = false;
	string s1 = s;
	while (fl == false && j <= n)
	{
		s1 = s;
		s1.erase(j,1);
		int as = getSum(s1);
		if (getSum(s1) % (n+1) == 0 && fl == false)
		{
			//cout << s1 << endl;
			return s1;
			fl = true;
		}
		j++;
	}
}

string delnoiseLess(string s, int sum, int n)
{
	if (sum % (n+1) == 0)
	{
		s.insert(n-1,"0");
		//cout << s << endl;
		return s;
	}
	else
	{
		int sumOld = sum;
		sum = (sumOld / (n+1) + 1) * (n+1);
		int dev = sum - sumOld;
		int countOne = getNumberOne(s);
		if (dev <= countOne)
		{
			int i = s.size();
			int j = 0;
			while (j != dev)
			{
				i--;
				if (s[i] == '1')
				{
					j++;
				}
			}
			s.insert(i,"0");
			//cout << s << endl;
			return s;
		}
		else
		{
			int i = s.size()-1;
			int countOneRight = 0;
			i = s.size();
			while (i + countOneRight + sumOld + 1 != sum)
			{
				i--;
				if (s[i] == '1')
				{
					countOneRight++;
				}
			}
			s.insert(i,"1");
			//cout << s << endl;
			return s;
		}
	}
}

string start(int n, string s)
{
	int length, sum;
	string out;

	if (s.length() > n+1 || s.length() < n-1)
	{
		return "-1";
	}
	for (int i = 0; i < s.length(); i++)
	{
		if (s[i] != '1' && s[i] != '0')
		{
			return "-1";
		}
	}

	length = s.length();
	sum = getSum(s);
	if ((sum % (n+1) == 0 || sum == 0) && length == n)
	{
		return s;
	}
	else
	{
	bool fl = false;
		if (length == n)		// если длина соответствует
		{		
			out = delnoise(s, sum, n);
		}
		if (length < n)			// если длина меньше нужной
		{	
			out = delnoiseLess (s, sum, n);			
		}
		if (length > n)			// если длина больше нужной
		{
			out = delnoiseMore(s, n);				
		}
	}
	return out;
}

void main()
{
	setlocale (LC_CTYPE,"Russian");
	int n1 = 4;
	string s11 = "0000";
	string s12 = "011";
	string s13 = "1011";
	string s14 = "11011";

	
	int n2 = 5;
	string s21 = "1111";
	string s22 = "1011";
	string s23 = "11111";
	string s24 = "000000";
	
	int n3 = 4;
	string s31 = "11";
	string s32 = "101111";

	int n4 = 3;	
	string s41 = "11a";
	string s42 = "abcd";

	
	plan_tests(12);
	ok1(start(n1, s11) == "0000");
	ok1(start(n1, s12) == "0110");
	ok1(start(n1, s13) == "1001");
	ok1(start(n1, s14) == "1111");
	ok1(start(n2, s21) == "11011");
	ok1(start(n2, s22) == "11011");
	ok1(start(n2, s23) == "11011");
	ok1(start(n2, s24) == "00000");
	ok1(start(n3, s31) == "-1");
	ok1(start(n3, s32) == "-1");
	ok1(start(n4, s41) == "-1");
	ok1(start(n4, s42) == "-1");
}