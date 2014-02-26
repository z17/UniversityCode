#include <iostream>
#include <vector>
#include <stdlib.h>

using namespace std;
//std::vector:: vector<int>operator+ (vector<int>& x)

// говно, плохая идея


struct ellement
{
	vector<int> numbers;
};

struct pairsContainer
{
	vector<ellement> tasks;
	vector<bool> tasksFl;			// false - эллемент без исключений
	
	pairsContainer(int n)
	{
		tasks.resize(2*n);
		tasksFl.resize(2*n);
	}
	void push(int x, int y)
	{
		x--;		// преобразование номера в индекс
		y--;
		tasks[x].numbers.push_back(y);
		tasksFl[x] = true;
		tasksFl[y] = true;
	}
};

void main()
{
	vector<int> firstPart;
	vector<int> secondPart;

	int n, m;
	cin >> n >> m;
	
	pairsContainer pairs(2*n);

	int q1, q2, q3;
	for (int i = 0; i < m; i++)
	{
		cin >> q1 >> q2;
		if (q1 > q2)
		{
			q3 = q2;
			q2 = q1;
			q1 = q3;			
		}
		pairs.push(q1,q2);
	}
	
	for (int i = 0; i < 2*n; i++)
	{
		if (pairs.tasks[i].numbers.size() > 0)
		{
			if (firstPart.size() > secondPart.size())
			{
				firstPart.push_back(i);
				secondPart.insert(secondPart.end(), pairs.tasks[i].numbers.begin(), pairs.tasks[i].numbers.end());
			}
			else
			{
				secondPart.push_back(i);
				firstPart.insert(firstPart.end(), pairs.tasks[i].numbers.begin(), pairs.tasks[i].numbers.end());
			}
			
		}
	}

	if (firstPart.size() == secondPart.size())
	{
		for (int i = 0; i < n; i++)
		{
			cout << firstPart[i] << " " << secondPart[i] << endl;
		}
	}
	else
	{
		cout << "IMPOSSIBLE" << endl;
	}
}