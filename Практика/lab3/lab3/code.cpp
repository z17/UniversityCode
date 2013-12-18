#include <stdio.h>
#include <string>
#include <iostream>
#include <fstream>
#include <vector>
using namespace std;


vector <vector <int> > swap (vector<vector<int>> s)
{
	int n1 = s.size();
	int n2 = s[0].size();
	vector<vector<int>> s2(n2,n1);

	for (int i = 0; i < n1; i++)
	{
		for (int j = 0; j < n2; j++)
		{
			s2[j][i] = s[n1-1-i][j];
		}
	}

	return s2;
}

vector <vector <int> > swapWrap(vector<vector<int>> s, int angl)
{
	
	int n1 = s.size();
	int n2 = s[0].size();
	vector <vector<int> > s2;

	switch (angl)
	{
		case 90 :
			s2 = swap(s);
			break;
		case 180 :
			s2 = swap(s);
			s2 = swap(s2);
			break;
		case 270 :
			s2 = swap(s);
			s2 = swap(s2);
			s2 = swap(s2);
			break;
		case 360 :
			s2 = s;
			break;
		default:
			s2.resize(1);
			s2[0].resize(1);
			s2[0][0] = -1;
	}
	return s2;

};


void main()
{
	setlocale (LC_CTYPE,"Russian");
	int n1,n2;
	cout << "Введите размер массива" << endl;
	cin >> n1 >> n2;

	vector <vector<int> > s(n1,n2);
	vector <vector<int> > s2(n1,n2);

	cout << "Введите массив" << endl;
	
	for (int i = 0; i < n1; i++)
	{
		for (int j = 0; j < n2; j++)
		{
			cin >> s[i][j];
		}
	}
	
	cout << "Исходный массив:" << endl;
	for (int i = 0; i < n1; i++)
	{
		for (int j = 0; j < n2; j++)
		{
			cout << s[i][j] << " ";
		}
		cout << endl;
	}
	
	cout << "Введите угол 90, 180, 270:" << endl;
	int a;
	cin >> a;
	s2 = swapWrap(s,a);

	cout << "Конечный массив:" << endl;
	for (int i = 0; i < s2.size(); i++)
	{
		for (int j = 0; j < s2[0].size(); j++)
		{
			cout << s2[i][j] << " ";
		}
		cout << endl;
	}

}