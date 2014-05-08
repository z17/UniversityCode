#include <iostream>
#include <time.h>
#include <vector>
#include <string>
#include <math.h>
#include <fstream>

using namespace std;

// метод k-средних

// изначально я делал что бы весь алгоритм работал для точек, абсолютно случайно распределённых. 
// потом пришлось добавить области, так что может показаться кривым способом
// области добавляются с помощью таких вот функций, возвращающих true если точка, переданная туда как аргумент, входит в область
// area1, area2 и area3 это три окружности

/*
1 часть
bool area1(const double _x, const double _y)
{
	double x = 2;
	double y = 2;
	double r = 2.5;

	double dist = sqrt(pow((_x - x),2) + pow((_y - y),2));
	if (dist <= r)
		return true;
	return false;
}

bool area2(const double _x, const double _y)
{
	double x = 7;
	double y = 5;
	double r = 3.5;

	double dist = sqrt(pow((_x - x),2) + pow((_y - y),2));
	if (dist <= r)
		return true;
	return false;
}

bool area3(const double _x, const double _y)
{
	double x = 2;
	double y = 8;
	double r = 2.5;

	double dist = sqrt(pow((_x - x),2) + pow((_y - y),2));
	if (dist <= r)
		return true;
	return false;
}*/

// 2 часть
/*
bool area1(const double _x, const double _y)
{
	double x = 2;
	double y = 1;
	double r = 2.8;

	double dist = sqrt(pow((_x - x),2) + pow((_y - y),2));
	if (dist <= r)
		return true;
	return false;
}

bool area2(const double _x, const double _y)
{
	double x = 8;
	double y = 1;
	double r = 2.8;

	double dist = sqrt(pow((_x - x),2) + pow((_y - y),2));
	if (dist <= r)
		return true;
	return false;
}

bool area3(const double _x, const double _y)
{
	double x = 5;
	double y = 5;
	double r = 2;

	double dist = sqrt(pow((_x - x),2) + pow((_y - y),2));
	if (dist <= r)
		return true;
	return false;
}


bool area4(const double _x, const double _y)
{
	double x = 2;
	double y = 9;
	double r = 2.8;

	double dist = sqrt(pow((_x - x),2) + pow((_y - y),2));
	if (dist <= r)
		return true;
	return false;
}

bool area5(const double _x, const double _y)
{
	double x = 8;
	double y = 9;
	double r = 2.8;

	double dist = sqrt(pow((_x - x),2) + pow((_y - y),2));
	if (dist <= r)
		return true;
	return false;
}
*/

// 3 часть
bool area1(const double _x, const double _y)
{
	double x1,y1,x2,y2,x3,y3,x4,y4;
	x1 = 0;
	x2 = 5;
	y1 = 0;
	y2 = 2;
	x3 = 0;
	x4 = 2;
	y3 = 2;
	y4 = 7;
	if (_x < x2 && _x > x1 && _y < y2 && _y > y1 || _x < x4 && _x > x3 && _y < y4 && _y > y3)
	{
		return true;
	}
	return false;
}

bool area2(const double _x, const double _y)
{
	double x1,y1,x2,y2,x3,y3,x4,y4;
	x1 = 7;
	x2 = 10;
	y1 = 1;
	y2 = 4;
	x3 = 4;
	x4 = 10;
	y3 = 4;
	y4 = 6;

	if (_x < x2 && _x > x1 && _y < y2 && _y > y1 || _x < x4 && _x > x3 && _y < y4 && _y > y3)
	{
		return true;
	}
	return false;
}

bool area3(const double _x, const double _y)
{
	double x1,y1,x2,y2,x3,y3,x4,y4;
	x1 = 1;
	x2 = 3;
	y1 = 8;
	y2 = 10;
	x3 = 3;
	x4 = 9;
	y3 = 7;
	y4 = 10;

	if (_x < x2 && _x > x1 && _y < y2 && _y > y1 || _x < x4 && _x > x3 && _y < y4 && _y > y3)
	{
		return true;
	}
	return false;
}


// одна точка
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

// один образ (точка и номер класса)
struct item
{
	dot point;
	int nClass;
	int nClass_data;

	item() {}

	item(int min, int max)														// этот конструктор использовать, если не нужны области, а нужен полный рандом
	{
		double x = rand() % ((max - min)*100) + min*100;
		double y = rand() % ((max - min)*100) + min*100;
		point.x = x / 100;
		point.y = y / 100;
		nClass = 0;			// тут храним номер класса, который посчитали
	}


	item(int min, int max, bool (*f)(const double x, const double y))			// сюда передаётся функция для проверки вхождения в область
	{
		double x;
		double y;
		bool fl = false;
		while(fl != true)			// выполняется пока точка не войдёт в область, из-за этого если область небольшого размера - может долго работать
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

// список образов и работа с ними
struct itemList
{
	vector<item> list;			// список
	vector<dot> center;			// список центров
	double percent;

	itemList() {}
	itemList (int d, int n, int min, int max)		// кол-во классов, кол-во образов, границы координат
	{
		center.resize(d);
		srand(time(NULL));
		for(int i = 0; i < n; i++)
		{
			// item x(min, max);		для полного рандома
			// list.push_back(x);

			int q = rand() % d + 1;			// случайно выбирается в какую область попадёт следующая точка, и потом вызывается соответствующий конструктор 
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
			if (q == 4)
			{
//				item x(min, max, area4);
//				list.push_back(x);
			}
			if (q == 5)
			{
//				item x(min, max, area5);
//				list.push_back(x);
			}
		}
	}

	// координаты классов = координаты первых i точек
	void firstCenters()
	{
		for (int i = 0; i < center.size(); i++)
		{
			center[i] = list[i].point;
		}
	}

	// вывод точек в разные файлы в зависимости от класса, сделано в лоб для 5-ти классов, что бы проверить работает ли вообще алгоритм :)
	// запихни вывод в график exel и будут красивые разноцветные точки!
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

	// вычисляет эвклидово расстояние для двух точек
	double distanceEuclidean(dot p, dot q)
	{
		double x = sqrt(pow((p.x - q.x), 2) + pow((p.y - q.y), 2));
		return x;
	}

	// возвращает индекс минимального значения в массиве
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

	// пересчёт центров классов
	bool restartCenters()				// возвращает true если центры изменились
	{
		bool fl = false;
		int size = center.size();
		vector<vector<double>> mas(size,3);				// первый эллемент - кол-во образов класса, затем сумма координатов по x и y	
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

	// а это самое главное, ради чего всё и делалось
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
				minIndex++;		// номер класса начинается не с нуля, поэтому увеличиваем на 1 (в item класс = 0 если класс ещё не присвоен)
				list[i].nClass = minIndex;
			}
			k++;
			if (k == 1)
			{				
				printList("test1");			// вывод после первого прохода, что бы можно было посмотреть изменение на графике
			}
			fl = restartCenters();
		}
	}

	int getNumberClass(dot point)
	{
		if (area1(point.x, point.y))
			return 1;
			
		if (area2(point.x, point.y))
			return 2;

		if (area3(point.x, point.y))
			return 3;
		
//		if (area4(point.x, point.y))
//			return 4;

//		if (area5(point.x, point.y))
	//		return 5;

		return 0;
	}


	void getPercent()
	{
		int k = 0;
		for (int i = 0; i < list.size(); i++)
		{
			if (getNumberClass(center[list[i].nClass - 1]) == getNumberClass(list[i].point))
			{
				k++;
			}
		}
		percent = (double)k / (double)list.size();
		cout << percent << endl;
	}

};


int main()
{
	int d = 3;			// кол-во классов
	int n = 1000;		// кол-во образов
	int min = 0;		// границы
	int max = 10;
	itemList one(d,n,min,max);
	one.firstCenters();
	
	one.kmeans();
	one.getPercent();
	one.printList("test2");		// итоговый вывод

	system("pause");
	return 0;
}