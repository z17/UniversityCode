#include <iostream>
#include <vector>
#include <stdlib.h>
#include<cstdlib>
#include <algorithm>
#include <time.h>

using namespace std;

struct person
{
	double x;
	double y;
	person ()
	{
		x = 0;
		y = 0;
	}
	person (double a, double b)
	{
		x = a;
		y = b;
	}
};

struct pullPerson
{
	vector <person *> pull;
	int xMax;
	int xMin;
	int yMax;
	int yMin;

	pullPerson (int x1, int x2, int y1, int y2)
	{
		xMax = x1;
		xMin = x2;
		yMax = y1;
		yMin = y2;
	}
	
	// создание новой особи
	void newPerson()
	{
		double x, y;
		x = rand() % (xMax - xMin) + xMin;
		y = rand() % (yMax - yMin) + yMin;

		person *nPerson = new person(x,y);
		pull.push_back(nPerson);
	}
	void newPerson(double x, double y)
	{
		person *nPerson = new person(x,y);
		pull.push_back(nPerson);
	}


	// случайный выбор родителей (возвращает [x,y], где x и y - порядковые номера родителей в массиве pull)
	vector<int> getParents()
	{
		int numPair1, numPair2;
		numPair1 = rand() % pull.size();
		numPair2 = rand() % pull.size();

		vector<int> ret;
		ret.push_back(numPair1);
		ret.push_back(numPair2);
		return ret;
	}

	// скрещивание
	void makeCrossing()
	{
		vector <int> indexParents = this -> getParents();
		double x,y;
		double e = rand() % 100;
		e = e / 100;

		x = e * pull[indexParents[0]] -> x + (1 - e)* pull[indexParents[1]] -> x;
		y = e * pull[indexParents[0]] -> y + (1 - e)* pull[indexParents[1]] -> y;

		this -> getMutation(x,y);
	}

	// мутация новой особи
	void getMutation(double x, double y)
	{
		double d1 = rand() % 100;
		d1 = d1 / 100;
		double d2 = rand() % 100;
		d2 = d2 / 100;
	
		// рандомно прибавляем или отнимаем
		int a = rand() % 2;
		if (a == 0)
			x = x + d1;
		else
			x = x - d1;
		a = rand() % 2;
		if (y == 0)
			y = y + d2;
		else
			y = y - d2; 

		this -> newPerson(x,y);
	}

	// фитнесс - функция
	double fitness(double x, double y)
	{
		double ret = x*x + y*y;	
		return ret;
	}
	
	// сортировка пузырьком для массива pull
	vector<person *> sortPull(vector<person *> a)
	{
		for (int i = 0; i < a.size(); i++)
		 {
			 for (int j = a.size() - 1; j > i; j--)
			 {
				 if (this -> fitness(a[j]->x, a[j]->y) < this -> fitness(a[j-1]->x, a[j-1]->y))
				 {
					 swap (a[j], a[j - 1]);
				 }
			 }
		 }
		return a;
	}

	// скрещивание -> мутация -> отбор
	void choicepull(int size)
	{
		this -> makeCrossing();
		this->pull = sortPull(this->pull);
		this->pull.pop_back();
	}
};

void main()
{	
	srand(time(NULL));

	pullPerson *population = new pullPerson(10, 0, 10, 0);
	int sizePopulation = 10;

	for (int i = 0; i < sizePopulation; i++)
	{
		population->newPerson();		
	}

	for (int i = 0; i < 10000; i++)
	{
		population->choicepull(sizePopulation);	
	}
	cout << " " << population->pull[0]->x << " " << population->pull[0]->y << " " << population->fitness(population->pull[0]->x,population->pull[0]->y) << endl;
	cout << endl;
}