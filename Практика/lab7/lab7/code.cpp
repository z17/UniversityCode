#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

void main()
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