#include <iostream>
#include <vector>
#include <stdlib.h>
using namespace std;
// http://acm.timus.ru/problem.aspx?space=1&num=1156

struct task
{
	int vall;
	vector<int> numbers;
	
	task()
	{
	}
	task(int name, int fvall)
	{
		this->vall = name;
		this->numbers.push_back(fvall);
	}
};

struct taskpull
{
	vector<task *> data;

	void add (int name, int vall)
	{
		int ind = -1;
		for (int i = 0; i < data.size(); i++)
		{
			if (name == data[i]->vall)
			{
				ind = i;
			}
		}
		if (ind == -1)
		{
			task *newt = new task(name, vall);
			data.push_back(newt);
		}
		else
		{
			this -> data[ind] -> numbers.push_back(vall); 
		}
		
	}
};

struct resultStruct
{
	vector<int> firstTour;
	vector<int> secondTour;
};

void main()
{
	int n, m;
	cin >> n >> m;

	taskpull *tasks = new taskpull;

	for (int i = 0; i < m; i++)
	{
		int a,b,c;
		cin >> a >> b;

		if (a > b)
		{
			c = b;
			b = a;
			a = c;
		}
		tasks -> add(a,b);
	}
	
	resultStruct result;
	result.firstTour.push_back(tasks -> data[0] -> vall);
	result.secondTour = tasks -> data[0] -> numbers;

	for (int i = 1; i < tasks->data.size(); i++)
	{
		bool flag1 = false;
		bool flag2 = false;
		int j = 0;
		while (flag1 == false && j < result.firstTour.size())
		{
			if (tasks -> data[i] -> vall == result.firstTour[j])
			{
				flag1 == true;
			}
			j++;
		}
		j = 0;
		while (flag2 == false && j < result.secondTour.size())
		{
			int testa = tasks -> data[i] -> vall;
			int testb = result.secondTour[j];
			if (tasks -> data[i] -> vall == result.secondTour[j])
			{
				flag2 == true;
			}
			j++;
		}
		if (flag1 && flag2)
		{
			cout << "IMPOSSIBLE" << endl;
			exit(-1);
		}
		else
		{
			if (flag1)
			{
				result.secondTour.insert(result.secondTour.begin(), tasks -> data[i] -> numbers.begin(), tasks -> data[i] -> numbers.end());
			}
			if (flag2)
			{
				result.firstTour.insert(result.firstTour.begin(), tasks -> data[i] -> numbers.begin(), tasks -> data[i] -> numbers.end());
			}
		}

	}

	for (int i = 0; i < result.firstTour.size(); i++)
	{
		cout << result.firstTour[i] << " ";
	}
	cout << endl;
	for (int i = 0; i < result.secondTour.size(); i++)
	{
		cout << result.secondTour[i] << " ";
	}
	cout << endl;
}