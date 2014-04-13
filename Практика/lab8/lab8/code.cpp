#include <stdio.h>
#include <iostream>
#include <string>
#include <fstream>
#include <time.h>

using namespace std;

// http://acm.timus.ru/problem.aspx?space=1&num=1354

string ReverseString (string s)
{
	#ifdef _DEBUG
	char dateStr [9];
	_strdate(dateStr);
	string name = "log_";
	name += dateStr;
	name += ".txt";
	name.replace(6,1,"_");
	name.replace(9,1,"_");
	ofstream f(name, ios::app);
	f << "function ReverseString, s = " << s << endl;
	#endif



	int n = s.length();
	for (int i = 0; i < n / 2 ; i++)
	{
		char q;
		q = s[i];
		s[i] = s[n-i-1];
		s[n-i-1] = q;
	}

	#ifdef _DEBUG
	f << "return = " << s << endl << endl;
	f.close();
	#endif

	return s;
}

int main()
{
	string s;
	cin >> s;

	#ifdef _DEBUG
	char dateStr [9];
	_strdate(dateStr);
	string name = "log_";
	name += dateStr;
	name += ".txt";
	name.replace(6,1,"_");
	name.replace(9,1,"_");
	ofstream f(name, ios::app);
	f << "---------------------------" << endl <<"start , s = " << s << endl;
	#endif

	int length = s.length();
	int maxLen = 0;
	int posPol = length-1;
	string polindrom;
	bool fl = false;
	for (int i = length - 1; i + 1 >= length / 2; i--)
	{
		if (i >= length / 2)
		{
			string polRight = ReverseString(s.substr(i + 1, length - i - 1));
			string polLeft = s.substr(i + 1 - length + i, length - i - 1);
			if (polRight == polLeft && polRight.length() > maxLen && polLeft.length()*2 + 1 < length)
			{
				maxLen = polRight.length();
				posPol = i;
				fl = false;
			}
		}
		if (i - length + i + 2 > 0)
		{
			string polRight = ReverseString(s.substr(i + 1,  length - i - 1));
			string polLeft = s.substr(i - length + i + 2, length - i - 1);
			if (polRight == polLeft && polRight.length() > maxLen)
			{
				maxLen = polRight.length();
				posPol = i;
				fl = true;
			}
		}
	}
	if (ReverseString(s.substr(0,posPol)).length() == 0)
	{
		fl = true;
	}
	polindrom = s.substr(0,posPol+1) + ReverseString(s.substr(0,posPol));
	if (fl)
	{
		polindrom = s.substr(0,posPol+1) + ReverseString(s.substr(0,posPol+1));
	}
	cout << polindrom << endl;

	#ifdef _DEBUG
	f << "end = " << polindrom << endl << endl;
	f.close();
	#endif

	system("pause");
	return 0;
}