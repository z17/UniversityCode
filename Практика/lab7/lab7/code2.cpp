#include <iostream>   
#include <vector>   
#include <algorithm>  
#include <assert.h>
using namespace std; 

void main()
{
	int n;
	vector <int> mas;
	cin >> n;
	// по условию 2 ≤ n ≤ 100
	assert(n >= 2 && n <= 100);		
	for (int i = 0; i < n; i++)
	{
		int a;
		cin >> a;
		assert(a > 0 && a <= 600);
		mas.push_back(a);
	}	
	int res = 0;	
	while (!mas.empty())
	{
		sort(mas.begin(),mas.end());
		if (mas.size() <= 2)
		{
			res = res + mas.back();
			mas.clear();
		}
		else
		{
			if (mas.size() == 3)
            {
				res += mas[0] + mas[1] + mas[2];
				mas.clear();
            }
            else
            {
				if (mas[1]*2 + mas[0] + mas.back() < mas[0] + mas[0] + mas[mas.size()-1] + mas[mas.size()-2])
				{
					res += mas[1]*2 + mas[0] + mas.back();
					mas.pop_back();
					mas.pop_back();
				}
				else
				{
					res += mas[0] + mas[0] + mas[mas.size()-1] + mas[mas.size()-2];
					mas.pop_back();
					mas.pop_back();
				}
			}
		}
	}
	cout << res << endl;
}