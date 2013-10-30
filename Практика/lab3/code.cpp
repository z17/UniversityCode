#include <stdio.h>
#include <string>
#include <iostream>
#include <fstream>
#include <vector>
using namespace std;


vector <vector <int> > swap (vector<vector<int>> s, int n)
{
	vector<vector<int>> s2(3,3);
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < n; j++)
		{
			s2[i][j] = s[n-j-1][i];
		}
	}
	return s2;
}

void main()
{
	setlocale (LC_CTYPE,"Russian");
	int n = 3;

	vector <vector<int> > s(n,n);
	vector <vector<int> > s2(n,n);

	cout << "Введите массив" << endl;
	
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < n; j++)
		{
			cin >> s[i][j];
		}
	}
	
	cout << "Исходный массив:" << endl;
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < n; j++)
		{
			cout << s[i][j] << " ";
		}
		cout << endl;
	}
	
	cout << "Введите угол 90, 180, 270:" << endl;
	int a;
	cin >> a;
	switch (a){
		case 90 :
			s2 = swap(s,n);
			break;
		case 180 :
			s2 = swap(s,n);
			s2 = swap(s2,n);
			break;
		case 270 :
			s2 = swap(s,n);
			s2 = swap(s2,n);
			s2 = swap(s2,n);
			break;
		default:
			cout << endl << "Ошибка" << endl;
	}

	cout << "Конечный массив:" << endl;
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < n; j++)
		{
			cout << s2[i][j] << " ";
		}
		cout << endl;
	}

}