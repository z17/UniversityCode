#include <vector>
#include <algorithm>
#include <complex>
#include <cmath>
#include <random>
#include <iostream>
#include <fstream>

using namespace std;

//typedef pair <float, float> Point;
typedef complex <double> Point;

struct Item{
	/*
	void operator+= (const Item& i){
		//this->point.first += i.point.first;
		//this->point.second += i.point.second;
		this->point += i.point;
	}

	void operator/= (int i){
		//this->point.first /= i;
		//this->point.second /= i;
	}

	void operator-= (const Item& i){
		//this->point.first -= i.point.first;
		//this->point.second -= i.point.second;
		this->point -= i.point;
	}
	*/
	Item(){}
	Item(double x, double y, bool cat){
		point = Point(x, y);
		category = cat;
	}
	Point point;
	bool category; // к какому классу принадлежит
};

class Set{
public:
	Set(){}
	Set (vector<int> size, vector<vector<uniform_real_distribution <double>::param_type>> options) {
		vector <Item> set1,
			set2;
		random_device gen;
		uniform_real_distribution <double> rndX;
		uniform_real_distribution <double> rndY;	
	
		
		rndX.param(options[0][0]);
		rndY.param(options[0][1]);

		// 1 тип
		for(int i = 0; i < size[0]; ++i){			
			Item p (rndX(gen), rndY(gen), 0);
			set1.push_back (p);
		}
		rndX.param(options[0][2]);
		rndY.param(options[0][3]);

		for(int i = 0; i < size[1]; ++i){
			Item p (rndX(gen), rndY(gen), 0);
			set1.push_back (p);
		}

		// 2 тип
		rndX.param(options[1][0]);
		rndY.param(options[1][1]);

		for(int i = 0; i < size[1]; ++i){
			Item p (rndX(gen), rndY(gen), 1);
			set2.push_back (p);
		}
		
		rndX.param(options[1][2]);
		rndY.param(options[1][3]);

		for(int i = 0; i < size[0]; ++i){
			Item p (rndX(gen), rndY(gen), 1);
			set2.push_back (p);
		}
		divide (set1, set2);
	}

	void printPoints()
	{
		ofstream fTest("test.txt");
		ofstream fSource("source.txt");

		for (int j = 0; j < 2; j++)
		{
			for (int i = 0; i < test[j].size(); i++)
			{
				fTest << test[j][i].point.real() << "\t" << test[j][i].point.imag() << endl;
			}
		}
		for (int j = 0; j < 2; j++)
		{
			for (int i = 0; i < source[j].size(); i++)
			{
				fSource << source[j][i].point.real() << "\t" << source[j][i].point.imag() << endl;
			}
		}

		fTest.close();
		fSource.close();
	}
private:
	void divide (vector <Item>& set1, vector <Item>& set2){
		int size = set1.size();

		// совместить с версией ћаши
		for (int i =  0; i < size; i++)
		{
			if (i % 2 == 0)
			{
				source[0].push_back(set1[i]);
				source[1].push_back(set2[i]);
			}
			else
			{
				test[0].push_back(set1[i]);
				test[1].push_back(set2[i]);
			}
		}
	}

public:	
	vector <Item> source[2],
		test[2];
};

class StandardMethod{ // эталонных образов
public:
	StandardMethod(const Set& inputSet){
		set = inputSet;
		setStandards();
		setRadii();
		findDiff();
	}

private:
	void findDiff(){
		vector<int> count(2,0);

		for(int k = 0; k < 2; ++k){
			int size = set.test[k].size();
			bool cmp = false;
			
			for(int i = 0; i < size; ++i){
				cmp = k == solve(set.test[k][i]);
				if (cmp)
				{
					count[k]++;
				}
				diff.push_back(cmp);
			}
			percent = (double)((double)count[k] / (double)size);
		}
	}
	void setStandards(){
		int size = set.source[0].size();

		for(int i = 0; i < size; ++i){
			standard[0].point += set.source[0][i].point;
		}		
		standard[0].point /= size;

		size = set.source[1].size();

		for(int i = 0; i < size; ++i){
			standard[1].point += set.source[1][i].point;
		}		
		standard[1].point /= size;
	}
	void setRadii(){
		for(int k = 0; k < 2; ++k){
			radius[k] = 0.;
			int size = set.source[k].size();
			int n = 0;

			for(int i = 0; i < size; ++i){
				n = norm(standard[k].point - set.source[k][i].point);
				radius[k] += n * n;
			}
			radius[k] = sqrt(radius[k]/size);
		}
	}
	bool solve(const Item& x){
		int k = 0;
		k = norm(x.point - standard[0].point) / radius[0];
		k -= norm(x.point - standard[1].point) / radius[1];
		return (k > 0); // если + , то 1. если - , то 0
	}

	double percent;
	Item standard[2];
	double radius[2];
	Set set;
	vector <bool> diff;
};

class NeighborMethod{ // ближайшего соседа
public:
	NeighborMethod(const Set& inputSet){
		set = inputSet;
		findDiff();
	}

private:
	void findDiff(){
		for(int k = 0; k < 2; ++k){
			int size = set.test[k].size();
			bool cmp = false;

			for(int i = 0; i < size; ++i){
				cmp = k == solve(set.test[k][i]);
				diff.push_back(cmp);
			}
		}
	}
	bool solve(const Item& x){
		Item neighbor[2];
		double d, min[2];
		int size = 0;

		for(int k = 0; k < 2; ++k){
			neighbor[k] = set.source[k].front();
			min[k] = norm(x.point - set.source[k].front().point);	
			size = set.source[k].size();
			int d = 0;

			for(int i = 1; i < size; ++i){
				d = norm(x.point - set.source[k][i].point);

				if(d < min[k]){
					min[k] = d;
					neighbor[k] = set.source[k][i];
				}
			}
		}
		bool cat = min[0] <= min[1] ?
			neighbor[0].category : neighbor[1].category;
		return cat;
	}

	Set set;
	vector <bool> diff;
};

int main(){
	const int N = 60;
	vector<int> size(2);
	size[0] = 300;
	size[1] = 600;
	vector<vector<uniform_real_distribution <double>::param_type>> options;
	options.resize(2);
	uniform_real_distribution <double>::param_type par;
	par._Init(0., 7.);
	options[0].push_back(par);
	par._Init(0., 4.);
	options[0].push_back(par);	
	par._Init(0., 2.);
	options[0].push_back(par);	
	par._Init(4., 8.);		
	options[0].push_back(par);
				
	par._Init(9., 10.);
	options[1].push_back(par);
	par._Init(0., 5.);
	options[1].push_back(par);	
	par._Init(4., 10.);
	options[1].push_back(par);	
	par._Init(5., 10.);
	options[1].push_back(par);
	


	Set set(size, options);
	set.printPoints();
	StandardMethod method1(set);
	NeighborMethod method2(set);

	system("pause");
	return 0;
}