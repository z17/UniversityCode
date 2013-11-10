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
				sum = sum + j + 1;
		}
	return sum;
}
void main()
{
	setlocale (LC_CTYPE,"Russian");

	int n, length,sum;
	cin >> n;

	/*
4    
0000 
011  
1011 
11011
*/
	string s;
	while (cin >> s)
	{
	//	cin >> s;
		length = s.length();
		sum = getSum(s);
		int a = sum % (n+1);
		if ((sum % (n+1) == 0 || sum == 0) && length == n)
		{
			cout << s << endl;
		}
		else
		{
			bool fl = false;
			if (length == n && (sum % (n+1) != 0 || sum != 0))
			{
				
				
				int sumOld = sum;
				int index;
				while (fl == false)
				{
					sumOld--;
					if (sumOld %(n+1) ==0)
					{
						fl = true;
					}
				}
					index = sum - sumOld;
					s[index-1] = '0';
				cout << s << endl;
			}
			if (length < n &&  fl == false)
			{				
				for (int j = 0; j < n; j++)
				{
					string s1 = s;
					s1.insert(j,"1");
					if (getSum(s1) % (n+1) == 0 && fl == false)
					{
						cout << s1 << endl;
						fl = true;
					}
					s1 = s;
					s1.insert(j,"0");
					if (getSum(s1) % (n+1) == 0 && fl == false)
					{
						cout << s1 << endl;
						fl = true;
					}
				}
				}
			if (length > n &&  fl == false)
			{
				for (int j = 0; j < n; j++)
				{
					string s1 = s;
					s1.erase(j,1);
					if (getSum(s1) % (n+1) == 0 && fl == false)
					{
						cout << s1 << endl;
						fl = true;
					}
				}
			}
		}
	}
}