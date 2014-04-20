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
// правда я с трудом представляю как задавать "кольца". 
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
			for (int j = 0; j < params[i].size; j++)
			{
				// не очень разумно что category есть в Item, и в  тоже время для каждого класса есть отдельный массив sets
				Item p(rndX(gen), rndY(gen), params[i].category);
				sets[params[i].category].push_back(p);
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
		while (k != params1.size)
		{
			double x, y;
			x = rndX(gen);
			y = rndY(gen);
			if (x >= params1.par.first._Min && x <= params1.par.first._Max && y >= params1.par.second._Min && y <= params1.par.second._Max)
			{
				if (!(x >= params2.par.first._Min && x <= params2.par.first._Max && y >= params2.par.second._Min && y <= params2.par.second._Max))
				{
					k++;
					Item p(x, y, params1.category);
					sets[params1.category].push_back(p);
				}
			}
		}


		rndX.param(params3.par.first); 
		rndY.param(params3.par.second); 
		for (int j = 0; j < params3.size; j++)
		{
			Item p(rndX(gen), rndY(gen), params3.category);
			sets[params3.category].push_back(p);
		}


		divide (sets);
	}


	// для вывода точек на графике
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
	uniform_real_distribution <double>::param_type par1, par2;

/*	par1._Init(0., 4.);
	par2._Init(0., 7.);	
	range rectangle1(0, 400, par1, par2);
	par1._Init(4., 8.);
	par2._Init(0., 2.);	
	range rectangle2(0, 200, par1, par2);
	par1._Init(5., 10.);
	par2._Init(4., 10.);	
	range rectangle3(1, 400, par1, par2);
	par1._Init(0., 5.);
	par2._Init(9., 10.);
	range rectangle4(1, 200, par1, par2);

	vector<range> options;
	options.push_back(rectangle1);
	options.push_back(rectangle2);
	options.push_back(rectangle3);
	options.push_back(rectangle4);	
	
	
	Set set(options);
*/
	
	par1._Init(1., 9.);
	par2._Init(1., 9.);	
	range rectangle1(0, 800, par1, par2);
	par1._Init(3., 6.);
	par2._Init(3., 6.);	
	range rectangle2(0, 800, par1, par2);	
	par1._Init(4., 5.);
	par2._Init(4., 5.);	
	range rectangle3(1, 300, par1, par2);

	Set set(rectangle1, rectangle2, rectangle3);
	set.printPoints();
	StandardMethod method1(set);
	NeighborMethod method2(set);


	return 0;
}