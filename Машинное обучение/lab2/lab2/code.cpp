#include <iostream>
#include <time.h>
#include <vector>
#include <string>
#include <math.h>
#include <fstream>

using namespace std;

// ����� k-�������

// ���������� � ����� ��� �� ���� �������� ������� ��� �����, ��������� �������� �������������. 
// ����� �������� �������� �������, ��� ��� ����� ���������� ������ ��������
// ������� ����������� � ������� ����� ��� �������, ������������ true ���� �����, ���������� ���� ��� ��������, ������ � �������
// area1, area2 � area3 ��� ��� ����������
bool area1(const double _x, const double _y)
{
	double x = 1;
	double y = 1;
	double r = 2;

	double dist = sqrt(pow((_x - x),2) + pow((_y - y),2));
	if (dist <= r)
		return true;
	return false;
}

bool area2(const double _x, const double _y)
{
	double x = 9;
	double y = 9;
	double r = 2;

	double dist = sqrt(pow((_x - x),2) + pow((_y - y),2));
	if (dist <= r)
		return true;
	return false;
}

bool area3(const double _x, const double _y)
{
	double x = 1;
	double y = 9;
	double r = 2;

	double dist = sqrt(pow((_x - x),2) + pow((_y - y),2));
	if (dist <= r)
		return true;
	return false;
}





// ���� �����
struct dot
{
	double x;
	double y;

	dot() {}
	dot(double _x, double _y)
	{
		x = _x;
		y = _y;
	}
};

// ���� ����� (����� � ����� ������)
struct item
{
	dot point;
	int nClass;

	item() {}

	item(int min, int max)														// ���� ����������� ������������, ���� �� ����� �������, � ����� ������ ������
	{
		double x = rand() % ((max - min)*100) + min*100;
		double y = rand() % ((max - min)*100) + min*100;
		point.x = x / 100;
		point.y = y / 100;
		nClass = 0;
	}


	item(int min, int max, bool (*f)(const double x, const double y))			// ���� ��������� ������� ��� �������� ��������� � �������
	{
		double x;
		double y;
		bool fl = false;
		while(fl != true)			// ����������� ���� ����� �� ����� � �������, ��-�� ����� ���� ������� ���������� ������� - ����� ����� ��������
		{			
			x = rand() % ((max - min)*100) + min*100;
			y = rand() % ((max - min)*100) + min*100;
			x = x / 100;
			y = y / 100;
			fl = f(x,y);
		}
		point.x = x;
		point.y = y;
		nClass = 0;
	}
};

// ������ ������� � ������ � ����
struct itemList
{
	vector<item> list;			// ������
	vector<dot> center;			// ������ �������

	itemList() {}
	itemList (int d, int n, int min, int max)		// ���-�� �������, ���-�� �������, ������� ���������
	{
		center.resize(d);
		srand(time(NULL));
		for(int i = 0; i < n; i++)
		{
			// item x(min, max, area1);		��� ������� �������
			// list.push_back(x);

			int q = rand() % 3 + 1;			// �������� ���������� � ����� ������� ������ ��������� �����, � ����� ���������� ��������������� ����������� 
			if (q == 1)
			{
				item x(min, max, area1);
				list.push_back(x);
			}
			if (q == 2)
			{
				item x(min, max, area2);
				list.push_back(x);
			}
			if (q == 3)
			{
				item x(min, max, area3);
				list.push_back(x);
			}
		}
	}

	// ���������� ������� = ���������� ������ i �����
	void firstCenters()
	{
		for (int i = 0; i < center.size(); i++)
		{
			center[i] = list[i].point;
		}
	}

	// ����� ����� � ������ ����� � ����������� �� ������, ������� � ��� ��� 5-�� �������, ��� �� ��������� �������� �� ������ �������� :)
	// ������� ����� � ������ exel � ����� �������� ������������ �����!
	void printList( string s)			
	{
		ofstream class1(s+"_class1.txt");		
		ofstream class2(s+"_class2.txt");	
		ofstream class3(s+"_class3.txt");	
		ofstream class4(s+"_class4.txt");	
		ofstream class5(s+"_class5.txt");	
		
		ofstream classAll("all.txt");	

		for (int i = 0; i < list.size(); i++)
		{
			classAll << list[i].point.x << "\t" << list[i].point.y << endl;
			if (list[i].nClass == 1)
			{
				class1 << list[i].point.x << "\t" << list[i].point.y << endl;
			}
			if (list[i].nClass == 2)
			{
				class2 << list[i].point.x << "\t" << list[i].point.y << endl;
			}
			if (list[i].nClass == 3)
			{
				class3 << list[i].point.x << "\t" << list[i].point.y << endl;
			}
			if (list[i].nClass == 4)
			{
				class4 << list[i].point.x << "\t" << list[i].point.y << endl;
			}
			if (list[i].nClass == 5)
			{
				class5 << list[i].point.x << "\t" << list[i].point.y << endl;
			}
		}

		class1.close();
		class2.close();
		class3.close();
		class4.close();
		class5.close();
		classAll.close();
	}

	// ��������� ��������� ���������� ��� ���� �����
	double distanceEuclidean(dot p, dot q)
	{
		double x = sqrt(pow((p.x - q.x), 2) + pow((p.y - q.y), 2));
		return x;
	}

	// ���������� ������ ������������ �������� � �������
	int indexMinValue(vector<double> mas)
	{
		if (mas.size() == 0)
			return -1;

		double min = mas[0];
		int index = 0;
		for (int i = 0; i < mas.size(); i++)
		{
			if (mas[i] < min)
			{
				min = mas[i];
				index = i;
			}
		}
		return index;
	}

	// �������� ������� �������
	bool restartCenters()				// ���������� true ���� ������ ����������
	{
		bool fl = false;
		int size = center.size();
		vector<vector<double>> mas(size,3);				// ������ �������� - ���-�� ������� ������, ����� ����� ����������� �� x � y	
		for (int i = 0; i < list.size(); i++)
		{
			mas[list[i].nClass - 1][0]++;
			mas[list[i].nClass - 1][1] += list[i].point.x;
			mas[list[i].nClass - 1][2] += list[i].point.y;
		}

		for (int i = 0; i < center.size(); i++)
		{
			double newx = mas[i][1] / mas[i][0];
			double newy = mas[i][2] / mas[i][0];
			if (center[i].x != newx || center[i].y != newy)
			{
				fl = true;
				center[i].x = newx;
				center[i].y = newy;			
			}
		}
		return fl;
	}

	// � ��� ����� �������, ���� ���� �� � ��������
	void kmeans()
	{
		bool fl = true;
		int k = 0;
		while (fl)
		{
			for (int i = 0; i < list.size(); i++)
			{
				vector<double> dist;
				for (int j = 0; j < center.size(); j++)
				{
					dist.push_back(distanceEuclidean(list[i].point, center[j]));
				}
				int minIndex = indexMinValue(dist);
				minIndex++;		// ����� ������ ���������� �� � ����, ������� ����������� �� 1 (� item ����� = 0 ���� ����� ��� �� ��������)
				list[i].nClass = minIndex;
			}
			k++;
			if (k == 1)
			{				
				printList("test1");			// ����� ����� ������� �������, ��� �� ����� ���� ���������� ��������� �� �������
			}
			fl = restartCenters();
		}
	}

};


int main()
{
	int d = 3;			// ���-�� �������
	int n = 500;		// ���-�� �������
	int min = 0;		// �������
	int max = 10;
	itemList one(d,n,min,max);
	one.firstCenters();
	
	one.kmeans();
	one.printList("test2");		// �������� �����

	system("pause");
	return 0;
}