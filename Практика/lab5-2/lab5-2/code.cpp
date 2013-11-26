#include <iostream>
#include <stdio.h>
#include <fstream>
#include <string>
using namespace std;

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

void delnoise(string s, int sum, int n)
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
	cout << s << endl;
}

void delnoiseMore(string s, int n)
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
			cout << s1 << endl;
			fl = true;
		}
		j++;
	}
}

void delnoiseLess(string s, int sum, int n)
{
	if (sum % (n+1) == 0)
	{
		s.insert(n-1,"0");
		cout << s << endl;
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
			cout << s << endl;
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
			cout << s << endl;
		}
	}
}
void main()
{
	setlocale (LC_CTYPE,"Russian");

	int n, length, sum;
	cin >> n;

	string s;
	while (cin >> s)
	{
		length = s.length();
		sum = getSum(s);
		if ((sum % (n+1) == 0 || sum == 0) && length == n)
		{
			cout << s << endl;
		}
		else
		{
			bool fl = false;
			if (length == n)		// если длина соответствует
			{		
				delnoise(s, sum, n);
			}
			if (length < n)			// если длина меньше нужной
			{	
				delnoiseLess (s, sum, n);			
			}
			if (length > n)			// если длина больше нужной
			{
				delnoiseMore(s, n);
				
			}
		}
	}
}