#include <stdio.h>
#include <iostream>
#include <vector>
#include <time.h>
#include <algorithm>

using namespace std;

int max (int a, int b)
{
	if (a > b)
	{
		return a;
	}
	return b;
}

int min (int a, int b)
{
	if (a < b)
	{
		return a;
	}
	return b;
}

struct input
{
	int numCandidates;
	int numVotes;
	vector<int> vote;					// ������	
	vector<vector<int>> voteSh;			// ������ ��� ������ ������

	input(int _numCand, int _numVotes)
	{
		srand(time(NULL));
		numCandidates = _numCand;
		numVotes = _numVotes;
		vote.resize(numCandidates);
		
		vector<int> oneList;
		vector<int> listOfCand, randomCand;
		for (int i = 0; i < numCandidates; i++)
		{
			listOfCand.push_back(i+1);		// ������ - ������ ������� ����������
		}

		// ���������� ��������� ������� ���-�� ������� �� ������� ���������
		int sum = numVotes;
		randomCand = listOfCand;
		for (int i = 0; i < numCandidates - 1; i++)
		{
			int j = rand() % randomCand.size();
			vote[randomCand[j] - 1] = rand() % sum;
			sum -= vote[randomCand[j] - 1]; 	
			randomCand.erase(randomCand.begin() + j);		
		}
		vote[randomCand[0] - 1] = sum;		

		// ���������� ������ ������������
		int indexLider = 0;
		int countLider = 0;
		for (int i = 0; i < numVotes; i++)
		{
			randomCand = listOfCand;
			oneList.clear();
			oneList.push_back(randomCand[indexLider]);
			randomCand.erase(randomCand.begin()+indexLider);
			countLider++;
			if (countLider >= vote[indexLider])
			{
				countLider = 0;
				indexLider++;
			}		
			for (int j = 0; j < numCandidates - 1; j++)
			{
				int randNum = rand() % randomCand.size();
				oneList.push_back(randomCand[randNum]);
				randomCand.erase(randomCand.begin() + randNum);
			}
			voteSh.push_back(oneList);	
		}	
		
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
		double rate = (double)data.vote[rating[0] - 1] / (double)data.numVotes;
		cout << "win = " << rate*100 << "%" << endl;
		cout << endl;
	/*	for(int i = 0; i < data.vote.size(); i++)
		{
			cout << i+1 << "\t";
		}
		cout << endl;
		for(int i = 0; i < data.vote.size(); i++)
		{
			cout << data.vote[i] << "\t";
		}
		cout << endl;*/

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
			for (int j = rating.size() - 1; j > i; j--)
			{

				if (data.vote[j] > data.vote[j-1])
				{
					int tmp;
					tmp = rating[j];
					rating[j] = rating[j-1];
					rating[j-1] = tmp;

					tmp = data.vote[j];
					data.vote[j] = data.vote[j-1];
					data.vote[j-1] = tmp;
				}
			}
		}
	}
};

struct Schulze: public poll
{
	Schulze(input data)
	{
		vector<vector<int>> matrix(data.numCandidates, data.numCandidates);

		// ��������� ������� ������������
		for (int i = 0; i < data.numVotes; i++)
		{
			for (int j = 0; j < data.numCandidates; j++)
			{
				for (int k = j; k < data.numCandidates; k++)
				{
					matrix[data.voteSh[i][j] - 1][data.voteSh[i][k] - 1]++;
				}
			}
		}

		
		vector<vector<int>> matrixPower(data.numCandidates, data.numCandidates);

		// �������� ���������� ����
		for (int i = 0; i < data.numCandidates; i++)
		{
			for (int j = 0; j < data.numCandidates; j++)
			{
				if (i != j)
				{
					if (matrix[i][j] > matrix[j][i])
					{
						matrixPower[i][j] = matrix[i][j];
					}
					else
					{
						matrixPower[i][j] = 0;
					}
				}
			}
		}
		// ���� ���������� �����
		for (int i = 0; i < data.numCandidates; i++)
		{
			for (int j = 0; j < data.numCandidates; j++)
			{
				if (i != j)
				{
					for (int k = 0; k < data.numCandidates; k++)
					{
						if (i != k && j !=k)
						{
							matrixPower[j][k] = max(matrixPower[j][k], min(matrixPower[j][i], matrixPower[i][k]));
						}
					}
				}
			}
		}

		rating.resize(data.numCandidates);
		vector<int> betterIndex = rating;
		// ��������� �������������
		for (int i = 0; i < data.numCandidates; i++)
		{
			rating[i] = i + 1;		// ��������� �������� ����������
			for (int j = 0; j < data.numCandidates; j++)
			{
				if (i != j)
				{
					if (matrixPower[i][j] > matrixPower[j][i])
					{
						betterIndex[i]++;
					}
					else
					{
						betterIndex[j]++;
					}
				}
			}
		}

		// ���������
		for (int i = 0; i < rating.size(); i++)
		{
			for (int j = rating.size() - 1; j > i; j--)
			{

				if (betterIndex[j] > betterIndex[j-1])
				{
					int tmp;
					tmp = rating[j];
					rating[j] = rating[j-1];
					rating[j-1] = tmp;

					tmp = betterIndex[j];
					betterIndex[j] = betterIndex[j-1];
					betterIndex[j-1] = tmp;
				}
			}
		}
	}
};


int main()
{  
	setlocale(LC_ALL, "Russian");

/*	input Data(4, 1000);
	FPP one(Data);
	Schulze two(Data);

	cout << "method FPP" << endl;
	one.print(Data);
	cout << endl << "method Schulze" << endl;
	two.print();
	*/
	
	srand(time(NULL));
	int n = 1;
	int k = 0;

	for (int i = 0; i < n; i++)
	{
		int cand = rand() % 4 + 3;
		int votes = rand() % 1000 + 500;
		cand = 5;
		votes = 45;
		input Data(cand, votes);
		Data.vote[0] = 10;
		Data.vote[1] = 8;
		Data.vote[2] = 12;
		Data.vote[3] = 7;
		Data.vote[4] = 8;

		Data.voteSh.clear();
		vector<int> test;
		test.resize(5);

		/* ���� �� ����
		A B C D E
		1 2 3 4 5

		5 ACBED		1 3 2 5 4
		5 ADECB		1 4 5 3 2
		8 BEDAC		2 5 4 1 3
		3 CABED		3 1 2 5 4
		7 CAEBD		3 1 5 2 4
		2 CBADE		3 2 1 4 5
		7 DCEBA		4 3 5 2 1
		8 EBADC		5 2 1 4 3
		*/
		test[0] = 1;
		test[1] = 3;
		test[2] = 2;
		test[3] = 5;
		test[4] = 4;
		Data.voteSh.push_back(test);		// 5
		Data.voteSh.push_back(test);
		Data.voteSh.push_back(test);
		Data.voteSh.push_back(test);
		Data.voteSh.push_back(test);
		test[0] = 1;
		test[1] = 4;
		test[2] = 5;
		test[3] = 3;
		test[4] = 2;
		Data.voteSh.push_back(test);		// 5
		Data.voteSh.push_back(test);
		Data.voteSh.push_back(test);
		Data.voteSh.push_back(test);
		Data.voteSh.push_back(test);
		test[0] = 2;
		test[1] = 5;
		test[2] = 4;
		test[3] = 1;
		test[4] = 3;
		Data.voteSh.push_back(test);		// 8
		Data.voteSh.push_back(test);
		Data.voteSh.push_back(test);
		Data.voteSh.push_back(test);
		Data.voteSh.push_back(test);
		Data.voteSh.push_back(test);
		Data.voteSh.push_back(test);
		Data.voteSh.push_back(test);
		test[0] = 3;
		test[1] = 1;
		test[2] = 2;
		test[3] = 5;
		test[4] = 4;
		Data.voteSh.push_back(test);		// 3
		Data.voteSh.push_back(test);
		Data.voteSh.push_back(test);
		
		test[0] = 3;
		test[1] = 1;
		test[2] = 5;
		test[3] = 2;
		test[4] = 4;
		Data.voteSh.push_back(test);		// 7
		Data.voteSh.push_back(test);
		Data.voteSh.push_back(test);
		Data.voteSh.push_back(test);
		Data.voteSh.push_back(test);
		Data.voteSh.push_back(test);
		Data.voteSh.push_back(test);		

		test[0] = 3;
		test[1] = 2;
		test[2] = 1;
		test[3] = 4;
		test[4] = 5;
		Data.voteSh.push_back(test);		// 2
		Data.voteSh.push_back(test);
		
		test[0] = 4;
		test[1] = 3;
		test[2] = 5;
		test[3] = 2;
		test[4] = 1;
		Data.voteSh.push_back(test);		// 7
		Data.voteSh.push_back(test);
		Data.voteSh.push_back(test);
		Data.voteSh.push_back(test);
		Data.voteSh.push_back(test);
		Data.voteSh.push_back(test);
		Data.voteSh.push_back(test);
		test[0] = 5;
		test[1] = 2;
		test[2] = 1;
		test[3] = 4;
		test[4] = 3;
		Data.voteSh.push_back(test);		// 8
		Data.voteSh.push_back(test);
		Data.voteSh.push_back(test);
		Data.voteSh.push_back(test);
		Data.voteSh.push_back(test);
		Data.voteSh.push_back(test);
		Data.voteSh.push_back(test);
		Data.voteSh.push_back(test);
		FPP one(Data);
		Schulze two(Data);
		one.print();
		two.print();
		if (one.rating[0] == two.rating[0])
		{
			k++;
		}
	}
	cout << "������� ���������� �����������: " << (double)((double)k/(double)n) << "%" << endl;

	system("pause");
	return 0;
}