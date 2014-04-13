#include <iostream>
#include <vector>
#include <stdlib.h>
using namespace std;

// http://acm.timus.ru/problem.aspx?space=1&num=1017

int GetVal (int i, vector<int>* row)
{
	if (i == 0)
		return 0;
	if (i == 1)
		return 1;

	if (row->at(i) > 0)
	{
		return row->at(i);
	}

	int i2  = i / 2;
	if (i2 + i2 == i)
	{
		if (row->at(i2) < 0)
		{
			row->at(i2) = GetVal(i2, row);
		}
		row->at(i) = row->at(i2);
	}
	if (i2 + i2 + 1 == i)
	{
		if (row->at(i2) < 0)
		{
			row->at(i2) = GetVal(i2, row);
		}
		if (row->at(i2+1) < 0)
		{
			row->at(i2+1) = GetVal(i2+1, row);
		}
		row->at(i) = row->at(i2) + row->at(i2+1);
	}
	return row->at(i);
};

void main()
{
	int n;
	cin >> n;
	vector<int> row(100000, -1);
	row[0] = 0;
	row[1] = 1;

	while (n != 0)
	{
		int max = -1;
		int val;
		int start = 1;
		for (int i = start; i <= n; i++)
		{
			val = GetVal(i, &row);
			if (max < val)
			{
				max = val;
			}			
		}
		cout << max <<  endl;
		cin >> n;
	}
}