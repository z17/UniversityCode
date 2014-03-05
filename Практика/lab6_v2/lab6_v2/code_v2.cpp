#include <iostream>
#include <vector>
#include <stdlib.h>
using namespace std;
// http://acm.timus.ru/problem.aspx?space=1&num=1156

// òåñò http://acm.timus.ru/forum/thread.aspx?id=21908&upd=634210442998931250

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
	bool error = false;

	vector<bool> flTasks(2*n,false);	// äîáàâëåíû ëè

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
		flTasks[a-1] = true;
		flTasks[b-1] = true;
		tasks -> add(a,b);
	}
	
	resultStruct result;
	result.firstTour.push_back(tasks -> data[0] -> vall);
	result.secondTour = tasks -> data[0] -> numbers;

	for (int i = 1; i < tasks->data.size(); i++)
	{
		bool flag1 = false;
		bool flag2 = false;
		bool flag1T = false;
		bool flag2T = false;
		int posT;
		int j = 0;
		while (flag1 == false && j < result.firstTour.size())
		{
			if (tasks -> data[i] -> vall == result.firstTour[j])
			{
				flag1 = true;
			}
			j++;
		}
		j = 0;
		while (flag1T == false && j < tasks -> data[i] -> numbers.size())
		{
			for (int j1 = 0; j1 < result.secondTour.size(); j1++)
			{
				if (tasks -> data[i] -> numbers[j] == result.secondTour[j1])
				{
					flag1T = true;
					posT = j;
				}
			}
			j++;
		}

		j = 0;
		while (flag2 == false && j < result.secondTour.size())
		{
			if (tasks -> data[i] -> vall == result.secondTour[j])
			{
				flag2 = true;
			}

			j++;
		}
		j = 0;

		while (flag2T == false && j < tasks -> data[i] -> numbers.size())
		{
			for (int j1 = 0; j1 < result.firstTour.size(); j1++)
			{
				if (tasks -> data[i] -> numbers[j] == result.firstTour[j1])
				{
					flag2T = true;
					posT = j;
				}
			}
			j++;
		}
		if (flag1 && flag2 || flag1T && flag2T)
		{
			error = true;
		}
		else
		{
			if (flag1)
			{
				for (int q = 0; q < tasks -> data[i] -> numbers.size(); q++)
				{
					for (int q1 = 0; q1 < result.firstTour.size(); q1++)
					{
						if (result.firstTour[q1] == tasks -> data[i] -> numbers[q])
						{
							error = true;
						}
					}
				}
				result.secondTour.insert(result.secondTour.begin(), tasks -> data[i] -> numbers.begin(), tasks -> data[i] -> numbers.end());
			}
			if (flag2)
			{
				
				for (int q = 0; q < tasks -> data[i] -> numbers.size(); q++)
				{
					for (int q1 = 0; q1 < result.secondTour.size(); q1++)
					{
						if (result.secondTour[q1] == tasks -> data[i] -> numbers[q])
						{
							error = true;
						}
					}
				}
				result.firstTour.insert(result.firstTour.begin(), tasks -> data[i] -> numbers.begin(), tasks -> data[i] -> numbers.end());
			}
			if (flag1T)
			{
				tasks -> data[i] -> numbers.erase(tasks -> data[i] -> numbers.begin() + posT);
				result.firstTour.push_back(tasks -> data[i] -> vall);
				result.secondTour.insert(result.secondTour.begin(), tasks -> data[i] -> numbers.begin(), tasks -> data[i] -> numbers.end());
			}
			if (flag2T)
			{
				tasks -> data[i] -> numbers.erase(tasks -> data[i] -> numbers.begin() + posT);
				result.secondTour.push_back(tasks -> data[i] -> vall);
				result.firstTour.insert(result.firstTour.begin(), tasks -> data[i] -> numbers.begin(), tasks -> data[i] -> numbers.end());
			}

		}
		if (!flag1 && !flag2 && !flag1T && !flag2T)
		{
			// ÍÅÂÅĞÍÎ ĞÅÀËÈÇÎÂÀÍ ÂÛÁÎĞ
			if (result.firstTour.size() <= result.secondTour.size())
			{
				result.secondTour.push_back(tasks -> data[i] -> vall);
				result.firstTour.insert(result.firstTour.begin(), tasks -> data[i] -> numbers.begin(), tasks -> data[i] -> numbers.end());	
			}
			else
			{
				result.firstTour.push_back(tasks -> data[i] -> vall);
				result.secondTour.insert(result.secondTour.begin(), tasks -> data[i] -> numbers.begin(), tasks -> data[i] -> numbers.end());	
			}
		}
	}
	
	for (int i = 0; i < flTasks.size(); i++)
	{
		if (flTasks[i] == false)
		{
			if (result.firstTour.size() <= result.secondTour.size())
			{
				result.firstTour.push_back(i+1);
			}
			else
			{
				result.secondTour.push_back(i+1);
			}
		}
	}

	if (result.firstTour.size() != result.secondTour.size())
	{
		error = true;
	}
	if (error)
	{		
		cout << "IMPOSSIBLE" << endl;
		exit(-1);
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