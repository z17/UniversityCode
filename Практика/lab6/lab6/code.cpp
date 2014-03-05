#include <iostream>
#include <vector>
#include <stdlib.h>
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

/*
test 
3 4
1 2
1 3
4 5
4 6
WA
выводит IMPOSSIBLE
а должен 
1 5 6
2 3 4

Тест
4 6
1 2
2 3
3 4
4 5
6 7
7 8

ANS:
 1 3 5 7
 2 4 6 8
*/
/* неверный старый код
	//////////////////////////
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
		
		int swap;		// костыль, который падает на 3-м тесте
		if (count1 <= count2)
		{
			swap = x;
			x = y;
			y = swap;
		}
		if (mas[x].firstRound == true && mas[x].secondRound == true && mas[y].firstRound == true && mas[y].secondRound == true)
		{
			mas[x].secondRound = false;
			mas[y].firstRound = false;
		}
		else
		{

			
			if (mas[x].secondRound == false && mas[y].firstRound == true)
			{
				mas[y].firstRound = false;
				count2++;

			}
			if (mas[x].firstRound == false && mas[y].secondRound == true)
			{
				mas[y].secondRound = false;
				count1++;

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

		/*

		if (mas[x].secondRound == false && mas[y].firstRound == true)
		{
			mas[y].firstRound = false;
			count2++;

		}
		if (mas[x].firstRound == false && mas[y].secondRound == true)
		{
			mas[y].secondRound = false;
			count1++;

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
		}* /

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
	if (count1 != count2 || round1.size() < n || round2.size() < n)
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
*/

struct couple
{
	int a,b;
	couple()
	{
		this->a = -1;
		this->b = -1;
	}
};

bool in_array(int find, vector<int> mas)
{
	for(int i = 0; i < mas.size(); i++)
	{
		if (mas[i] == find)
		{
			return true;
		}
	}
	return false;
}
/*
bool arrayVSarray(vector<int> mas1, vector<int> mas2)
{
	for(int i = 0; i < mas1.size(); i++)
	{
		for(int j = 0; j < mas2.size(); j++)
		{


		}
	}
	return false;
}*/

void main1()
{
	int n,m;
	cin >> n >> m;

	int x,y;

	vector <vector<int>> mas;
	mas.resize(2*n);

	for (int i = 0; i < m; i++)
	{
		cin >> x >> y;

		// массив начинается с 0-ого эллемента, поэтому -1
		x--;	
		y--;

		mas[x].push_back(y);
		mas[y].push_back(x);
	}

	
	vector <int> round1, round2;
	vector <bool> fl(2*n);

	bool impos = false;
	int count1 = 0;
	int count2 = 0;

	for (int i = 0; i < 2*n; i++)
	{
	//	if (in_array(i,)
		if (fl[i] == false)
		{
			if (count1 > count2)
			{
				round2.push_back(i);
				count2++;
				fl[i] = true;
				for (int j = 0; j < mas[i].size(); j++)
				{
					if (fl[mas[i][j]] == false)
					{
						round1.push_back(mas[i][j]);
						count1++;
						fl[mas[i][j]] = true;
					}
				}
			}
			else
			{
				round1.push_back(i);
				count1++;
				fl[i] = true;
				for (int j = 0; j < mas[i].size(); j++)
				{
					if (fl[mas[i][j]] == false)
					{
						round2.push_back(mas[i][j]);
						count2++;
						fl[mas[i][j]] = true;
					}
				}
			}
		}
	}	
/*	for (int i = 0; i < 2*n; i++)
	{
		if (fl[i] == false)
		{
			if (round1.size()< round2.size())
			{
				round1.push_back(i);
			}
			else
			{
				round2.push_back(i);
			}
		}
	}
*/
	if (round1.size() < n || round2.size() < n || impos == true)
	{
		cout << "IMPOSSIBLE" << endl;
	}
	else
	{
		for (int i = 0; i < round1.size(); i++)
		{
			cout << round1[i]+1 << " ";
		}
		cout << endl;
		for (int i = 0; i < round2.size(); i++)
		{
			cout << round2[i]+1 << " ";
		}
		cout << endl;	
	}
}

