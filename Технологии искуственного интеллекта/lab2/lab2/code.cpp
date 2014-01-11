#include <iostream>
#include <vector>
#include <stdlib.h>
#include <cstdlib>
#include <algorithm>
#include <time.h>
#include <math.h>
#include <fstream>

#define PI 3.14159265

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
	pullPerson ()
	{
	}
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
	
		this -> newPerson(x,y);
	}

	// мутация всех особей с определённой вероятностью x
	void getMutation(int x)
	{
		for (int i = 0; i < pull.size(); i++)
		{
			if (rand() % 10 < x)
			{
				// -1 .. +1
				double d1 = rand() % 200 - 100;
				d1 = d1 / 100;
				double d2 = rand() % 200 - 100;
				d2 = d2 / 100;
			//	cout << d1 << " " << d2 << endl;
			
				this -> pull[i] -> x = this -> pull[i] -> x + d1;
				this -> pull[i] -> y = this -> pull[i] -> y + d2;
			}
		}
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

	// 1 скрещивание -> мутация всех -> отбор
	void choicepull(int size, int probability)
	{
		for (int i = 0; i < 25; i++)	// 25 скрещиваний
		{
			this -> makeCrossing();
		}
		this -> getMutation(probability);		
		this -> pull = sortPull(this->pull);
		for (int i = 0; i < 25; i++)
		{
			this -> pull.pop_back();
		}
	}

	// фитнесс - функция
	double fitness(double x, double y)
	{
		double ret;
	//	ret = x*x + y*y;	
	//	ret = 3*x*x + 2*y*y - 4*y + x - 2;	
	//	ret = x*x+2*y*y+4*y-x+2;
		double pre = x*x + y*y;
		ret = -(sin(pre * PI / 180))/pre;
		return ret;
	}
};

void takeResult(pullPerson *populationMain, int sizePopulation, double xreal, double yreal, vector<int> probability)
{	
	ofstream f;
	f.open("in.txt");
	pullPerson *pop = new pullPerson;	

	double x,y;
	int prob;
	for (int j = 0; j < probability.size(); j++)
	{
		*pop = *populationMain; // загрузка в population исходной созданной популяции
		prob = probability[j];
		for (int i = 0; i < 50; i++)
		{
			pop->choicepull(sizePopulation, prob);	
			double result;
			x = pop->pull[0]->x;
			y = pop->pull[0]->y;
			result = sqrt(pow(x - xreal,2) + pow(y - yreal,2));
			f << result << "	";
		}
		f << endl;
		cout << endl << " " << pop->pull[0]->x << " " << pop->pull[0]->y << " " << pop->fitness(pop->pull[0]->x,pop->pull[0]->y) << endl;

	}
	f.close();
}

void main()
{	
	srand((unsigned)time(NULL));

	pullPerson *population = new pullPerson(50, 5, 50, 5);
	int sizePopulation = 50;

	for (int i = 0; i < sizePopulation; i++)
	{
		population->newPerson();		
	}
	double xreal, yreal;	// реальные значения экстремума
	xreal = 0;
	yreal = 0;
	
	// вероятности
	vector<int> probability;
	probability.push_back(1);
	probability.push_back(5);
	probability.push_back(9);
	// запуск с разными вероятностями
	takeResult(population, sizePopulation, xreal, yreal, probability);


}