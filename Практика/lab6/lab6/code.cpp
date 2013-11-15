#include <iostream>
#include <vector>

using namespace std;
// http://acm.timus.ru/problem.aspx?space=1&num=1156

struct task
{
	bool firstRound, secondRound;	// состояние true - можно добавить, false нельзя
	task()
	{
		this -> firstRound = true;
		this -> secondRound = true;
	}
};

void main()
{
	int n,m;
	cin >> n >> m;

	int x,y;
	vector <task> mas;
	mas.resize(2*n);
	vector <int> round1, round2;

	int count1 = 0;
	int count2 = 0;
	for (int i = 0; i < m; i++)
	{
		cin >> x >> y;
		x--;
		y--;

		if (mas[x].firstRound == true && mas[x].secondRound == true && mas[y].firstRound == true && mas[y].secondRound == true)
		{
			mas[x].secondRound = false;
			mas[y].firstRound = false;
		}

		if (mas[y].secondRound == false && mas[x].firstRound == true)
		{
			mas[x].firstRound = false;
			count2++;
		}
		
		if (mas[y].firstRound == false && mas[x].secondRound == true)
		{
			mas[x].secondRound = false;
			count1++;
		}
	}

	for (int i = 0; i < 2*n; i++)
	{
		if (mas[i].firstRound == false && mas[i].secondRound )
		{
			round2.push_back(i+1);
		}		
		if (mas[i].secondRound == false && mas[i].firstRound )
		{
			round1.push_back(i+1);
		}
		if (mas[i].firstRound && mas[i].secondRound)
		{
			if (count1 <= count2)
			{
				round1.push_back(i+1);
				count1++;
			}
			else
			{
				round2.push_back(i+1);
				count2++;
			}
		}
	}
	if (count1 != count2)
	{
		cout << "IMPOSSIBLE" << endl;
	}
	else
	{
		for (int i = 0; i < round1.size(); i++)
		{
			cout << round1[i] << " ";
		}
		cout << endl;
		for (int i = 0; i < round2.size(); i++)
		{
			cout << round2[i] << " ";
		}
		cout << endl;	
	}
}