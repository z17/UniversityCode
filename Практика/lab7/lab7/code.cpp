#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

// http://acm.timus.ru/problem.aspx?space=1&num=1826

void algv2()
{
	int n;
	vector <int> times;

	cin >> n;

	int q;
	for (int i = 0; i < n; i++)
	{
		cin >> q;
		times.push_back(q);
	}

	sort(times.begin(),times.end());

	int sum1 = 0;
	for (int i = 1; i < n; i++)
	{
		sum1 += times[i];
	}
	sum1 = sum1 + times.size()/2 * times[0];

	int sum2 = 0;
	int j = 0;
	for (int i = n-1; i >= 0; i--)
	{
		if (i >= 2)
		{
			if (times[i] > times[1]*2 && i > 2)
			{
				sum2 = sum2 + times[i] + times[1] + times[1] + times[0];
				i--;
			}
			else
			{
				sum2 = sum2 + times[0] + times[0] + times[i] + times[i-1];
				i--;
			/*	if (i != 0) 
				{
					sum2 += times[i];			
					j++;
				}
				*/
			}
		}
		else
		{
			sum2 += times[1];
			break;
		}
	}
//	if (times.size() > 2)
//		sum2 = sum2 + (j+1)/2 * times[0];

//	cout << sum1 << endl << sum2 << endl;
	cout << sum2 << endl;
}

void algv1()
{
	int n;
	cin >> n;
	vector <int> mas1;
	vector <int> mas2;
	int min1, min2;
	int a;
	for (int i = 0; i < n; i++)
	{
		cin >> a;
		mas1.push_back(a);
	}
	sort(mas1.begin(),mas1.end());
	reverse(mas1.begin(),mas1.end());
	int sum = 0;

//	sum = mas1[mas1.size()-1] + mas1[mas1.size()-2];
	sum = mas1[mas1.size()-2];
	min1 = mas1[mas1.size()-1];
	min2 = mas1[mas1.size()-2];
	mas2.push_back(mas1[mas1.size()-2]);
	mas2.push_back(mas1[mas1.size()-1]);
	mas1.pop_back();
	mas1.pop_back();
	
	while (!mas1.empty())
	{
		sum = sum + mas2[mas2.size()-1];

		mas1.push_back(mas2[mas2.size()-1]);
		mas2.pop_back();
		sort(mas1.begin(),mas1.end());

		sum = sum + mas1[mas1.size()-1];
		mas2.push_back(mas1[mas1.size()-1]);
		mas1.pop_back();

		
		sort(mas2.begin(),mas2.end());
		reverse(mas2.begin(),mas2.end());
		if (mas2[mas2.size()-1] == min1 || mas2[mas2.size()-1] == min2 )
		{
			/*int q = mas1[mas1.size()-1];
			if (min2 > mas1[mas1.size()-1])
			{
				q = min2;
			}*/

			if (2 * min2 > min1 +  mas1[mas1.size()-1])
			{	
				reverse(mas1.begin(),mas1.end());
				mas2.push_back(mas1[mas1.size()-1]);
				mas1.pop_back();
			}
			else
			{
				mas2.push_back(mas1[mas1.size()-1]);
				mas1.pop_back();
				
			}

		}
		else
		{
			reverse(mas1.begin(),mas1.end());
			mas2.push_back(mas1[mas1.size()-1]);
			mas1.pop_back();
		}
		sort(mas2.begin(),mas2.end());
		reverse(mas2.begin(),mas2.end());
	}


	cout << sum << endl;
	
}

void mainTest ()
{
	algv2();
}