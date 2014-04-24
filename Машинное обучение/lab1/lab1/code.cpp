#include <vector>
#include <algorithm>
#include <complex>
#include <cmath>
#include <random>
#include <utility>
#include <fstream>

using namespace std;
typedef complex <double> Point;

struct Item{
	Item(){}
	Item(double x, double y, bool cat){
		point = Point(x, y);
		category = cat;
	}
	Point point;
	bool category; // к какому классу принадлежит
};

// спец. структура для адекватной и удобной передачи параметров в конструктор set
// включает в себя id класса, кол-во точек, и границы области (прямоугольники)
struct range
{
	int category;
	int size;
	pair<uniform_real_distribution <double>::param_type, uniform_real_distribution <double>::param_type> par;

	range(){}

	range(int _category, int _size, uniform_real_distribution <double>::param_type _par1, uniform_real_distribution <double>::param_type _par2)
	{
		category = _category;
		size = _size;
		par = make_pair(_par1, _par2);
	}
};


class Set{
public:
	Set(){}

	// так по-моему меньше путаницы с параметрами
	Set(vector<range> params)
	{
		vector<vector<Item>> sets;
		sets.resize(2);
		random_device gen;
		uniform_real_distribution <double> rndX;
		uniform_real_distribution <double> rndY;
		for (int i = 0; i < params.size(); i++)
		{
			rndX.param(params[i].par.first); 
			rndY.param(params[i].par.second); 
			int coutError = 0;
			for (int j = 0; j < params[i].size; j++)
			{
				int k = params[i].category;
			/*	if (coutError < params[i].size / 10)	внесение 10% ошибок
				{
					coutError++;
					if (k == 0)
						k = 1;
					else
						k = 0;
				}*/
				Item p(rndX(gen), rndY(gen), k);
				sets[k].push_back(p);
			}
		}
		divide (sets);
	}

	// для колец, первый - внешний прямоугольник, второй - внутренний, size берётся из первого
	// третий - область другого класса
	Set(range params1, range params2, range params3)
	{
		vector<vector<Item>> sets;
		sets.resize(2);
		random_device gen;
		uniform_real_distribution <double> rndX;
		uniform_real_distribution <double> rndY;
		uniform_real_distribution <double>::param_type par1, par2;
		pair<uniform_real_distribution <double>::param_type, uniform_real_distribution <double>::param_type> par;
		par1._Init(0., 10.);
		par2._Init(0., 10.);	
		par = make_pair(par1, par2);
		int k = 0;
		rndX.param(par.first); 
		rndY.param(par.second); 

		int coutError = 0;

		while (k != params1.size)
		{
			double x, y;
			x = rndX(gen);
			y = rndY(gen);
			if (x >= params1.par.first._Min && x <= params1.par.first._Max && y >= params1.par.second._Min && y <= params1.par.second._Max)
			{
				if (!(x >= params2.par.first._Min && x <= params2.par.first._Max && y >= params2.par.second._Min && y <= params2.par.second._Max))
				{

					int cat = params1.category;
					if (coutError < params1.size / 10) //	внесение 10% ошибок
					{
						coutError++;
						if (cat == 0)
							cat = 1;
						else
							cat = 0;
					}


					k++;
					Item p(x, y, cat);
					sets[cat].push_back(p);
				}
			}
		}


		rndX.param(params3.par.first); 
		rndY.param(params3.par.second); 
		coutError = 0;

		for (int j = 0; j < params3.size; j++)
		{
			int cat = params3.category;
			if (coutError < params3.size / 10)	// внесение 10% ошибок
			{
				coutError++;
				if (cat == 0)
					cat = 1;
				else
					cat = 0;
			}
			
			Item p(rndX(gen), rndY(gen), cat);
			sets[cat].push_back(p);
		}


		divide (sets);
	}


	// для вывода точек на графике
	void printPoints()
	{
		ofstream fTest1("test1.txt");
		ofstream fTest2("test2.txt");
		ofstream fSource1("source1.txt");
		ofstream fSource2("source2.txt");

		for (int j = 0; j < 2; j++)
		{
			for (int i = 0; i < test[j].size(); i++)
			{
				if (j==0)
					fTest1 << test[j][i].point.real() << "\t" << test[j][i].point.imag() << endl;
				else
					fTest2 << test[j][i].point.real() << "\t" << test[j][i].point.imag() << endl;
			}
		}
		for (int j = 0; j < 2; j++)
		{
			for (int i = 0; i < source[j].size(); i++)
			{
				if (j==0)
					fSource1 << source[j][i].point.real() << "\t" << source[j][i].point.imag() << endl;
				else
					fSource2 << source[j][i].point.real() << "\t" << source[j][i].point.imag() << endl;
			}
		}

		fTest1.close();
		fSource1.close();
		fTest2.close();
		fSource2.close();
	}
private:
	void divide (vector<vector<Item>>& sets){

		// j % 2 == 0 - из-за этого условия половина идёт в тестовую, половина в основную 
		for (int i = 0; i < sets.size(); i++)
		{
			for (int j = 0; j < sets[i].size(); j++)
			{
				if (j % 2 == 0)
				{
					source[i].push_back(sets[i][j]);
				}
				else
				{
					test[i].push_back(sets[i][j]);
				}
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
	//	vector<int> count(2,0);
		int count = 0;

		ofstream f1("StandardMethod_class1.txt");
		ofstream f2("StandardMethod_class2.txt");

		int sizeAll = 0;

		for(int k = 0; k < 2; ++k){
			int size = set.test[k].size();
			sizeAll += size;
			bool cmp = false;
			
			for(int i = 0; i < size; ++i){
				cmp = k == solve(set.test[k][i]);
				if (solve(set.test[k][i]) == false)
				{
					f1 << set.test[k][i].point.real() << "\t" << set.test[k][i].point.imag() << endl;
				}
				if (solve(set.test[k][i]) == true)
				{
					f2 << set.test[k][i].point.real() << "\t" << set.test[k][i].point.imag() << endl;
				}

				if (cmp)
				{
				//	count[k]++;
					count++;
				}
				diff.push_back(cmp);
			}
			
		//	percent = (double)((double)count[k] / (double)size);
		}
		
		percent = (double)((double)count / (double)sizeAll);
		
		
		f1.close();
		f2.close();
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
		
		ofstream f1("NeighborMethod_class1.txt");
		ofstream f2("NeighborMethod_class2.txt");

		int sizeAll = 0;
		int count = 0;

		for(int k = 0; k < 2; ++k){
			int size = set.test[k].size();
			sizeAll += size;
			bool cmp = false;

			for(int i = 0; i < size; ++i){
				cmp = k == solve(set.test[k][i]);

				if (solve(set.test[k][i]) == false)
				{
					f1 << set.test[k][i].point.real() << "\t" << set.test[k][i].point.imag() << endl;
				}
				if (solve(set.test[k][i]) == true)
				{
					f2 << set.test[k][i].point.real() << "\t" << set.test[k][i].point.imag() << endl;
				}

				diff.push_back(cmp);

				if (cmp)
				{
					count++;
				}
			}
		}
		
		percent = (double)((double)count / (double)sizeAll);

		f1.close();
		f2.close();
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

	double percent;
	Set set;
	vector <bool> diff;
};

int main(){

	const int N = 60;
	uniform_real_distribution <double>::param_type par1, par2;
	
	
	par1._Init(0., 4.);
	par2._Init(0., 7.);	
	range rectangle1(0, 100, par1, par2);
	par1._Init(4., 8.);
	par2._Init(0., 2.);	
	range rectangle2(0, 50, par1, par2);

	par1._Init(5., 10.);
	par2._Init(4., 10.);	
	range rectangle3(1, 100, par1, par2);
	par1._Init(0., 5.);
	par2._Init(9., 10.);
	range rectangle4(1, 50, par1, par2);

	vector<range> options;
	options.push_back(rectangle1);
	options.push_back(rectangle2);
	options.push_back(rectangle3);
	options.push_back(rectangle4);	
	
	Set set(options);
	
	/*
	par1._Init(1., 9.);
	par2._Init(1., 9.);	
	range rectangle1(0, 200, par1, par2);
	par1._Init(2., 7.);
	par2._Init(2., 7.);	
	range rectangle2(0, 200, par1, par2);	
	par1._Init(3.5, 5.5);
	par2._Init(3.5, 5.5);	
	range rectangle3(1, 200, par1, par2);

	Set set(rectangle1, rectangle2, rectangle3);*/


	set.printPoints();
	StandardMethod method1(set);
	NeighborMethod method2(set);

	return 0;
}