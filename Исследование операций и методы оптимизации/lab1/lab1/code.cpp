#include <stdio.h>
#include <iostream>
#include <vector>
#include <time.h>
#include <algorithm>

using namespace std;


struct input
{
	int numCandidates;
	int numVotes;
	vector<int> vote;

	input(int _numCand, int _numVotes)
	{
		srand(time(NULL));
		numCandidates = _numCand;
		numVotes = _numVotes;
		vote.resize(numCandidates);
		int sum = numVotes;
		for (int i = 0; i < numCandidates - 1; i++)
		{
			vote[i] = rand() % sum;
			sum -= vote[i]; 			
		}
		vote[numCandidates - 1] = sum;		
	}

};

struct poll
{
	vector<int> rating;
	poll() {}

	void print()
	{
		cout << "rating:" << endl;
		for(int i = 0; i < rating.size(); i++)
		{
			cout << rating[i] << " ";
		}
		cout << endl;
	}

	void print(input data)
	{
		print();
		cout << endl;
		for(int i = 0; i < data.vote.size(); i++)
		{
			cout << i+1 << "\t";
		}
		cout << endl;
		for(int i = 0; i < data.vote.size(); i++)
		{
			cout << data.vote[i] << "\t";
		}
		cout << endl;
	}
};

struct FPP: public poll
{
	
	FPP(input data)
	{
		rating.resize(data.numCandidates);
		for (int i = 0; i < data.numCandidates; i++)
		{
			rating[i] = i+1;
		}
				

		for (int i = 0; i < rating.size(); i++)
		{
			int f = 0;
			for (int j = 0; j < rating.size() - i - 1; j++)
			{
				if (data.vote[rating[j]-1] < data.vote[rating[j+1]-1])
				{
					int tmp;
					tmp = rating[j];
					rating[j] = rating[j+1];
					rating[j+1] = tmp;

					tmp = data.vote[rating[j]-1];
					data.vote[rating[j]-1] = data.vote[rating[j+1]-1];
					data.vote[rating[j+1]-1] = tmp;
					f = 1;
				}

			}
			if (f == 0)
			{
				break;
			}
		}
	}
};


int main()
{
	input Data(4, 9340);
	FPP one(Data);
	one.print(Data);
	
	system("pause");
	return 0;
}