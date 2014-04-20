#include <vector>
#include <algorithm>
#include <complex>
#include <cmath>
#include <random>
#include <utility>

using namespace std;
typedef complex <double> Point;

struct Item{
	Item(){}
	Item(double x, double y, bool cat){
		point = Point(x, y);
		category = cat;
	}
	Point point;
	bool category; // ê êàêîìó êëàññó ïğèíàäëåæèò
};

class Set{
public:
	Set(){}
	////////////////////////////////////////
	// ÇÄÅÑÜ ÏÀÄÀÅÒ. ÂÛÕÎÄ: ËÈÁÎ ÑÄÅËÀÒÜ ÄÂÀ SIZES ÄËß ÄÂÓÕ ÊËÀÑÑÎÂ, ËÈÁÎ ÄÅËÀÒÜ ÏĞßÌÎÓÃÎËÜÍÛÅ
	// ÎÁËÀÑÒÈ ÎÄÈÍÀÊÎÂÎÉ ÏËÎÙÀÄÈ
	Set(const vector<int>& sizes, const vector<vector<pair<uniform_real_distribution <double>::param_type, 
		uniform_real_distribution <double>::param_type>>>& options){
		vector<vector<Item>> sets;
		sets.resize(2);
		random_device gen;
		uniform_real_distribution <double> rndX;
		uniform_real_distribution <double> rndY;

		for(int k = 0; k < 2; ++k){
			int nrect = options[k].size();
			
			for(int i = 0; i < nrect; ++i){
				rndX.param(options[k][i].first); 
				rndY.param(options[k][i].second); // ïğÿìîóãîëüíèê

				for(int j = 0; j < sizes[i]; ++j){
					Item p(rndX(gen), rndY(gen), k);
					sets[k].push_back(p);
				}
			}
		}
		divide (sets);

		/*
			// 1 òèï
		for(int i = 0; i < 400; ++i){			
			Item p (rndX(gen), rndY(gen), 0);
			set1.push_back (p);
		}
		par._Init(0., 2.);
		rndX.param(par);
		par._Init(4., 8.);
		rndY.param(par);

		for(int i = 0; i < 200; ++i){
			Item p (rndX(gen), rndY(gen), 0);
			set1.push_back (p);
		}

		// 2 òèï
		par._Init(9., 10.);
		rndX.param(par);
		par._Init(0., 5.);
		rndY.param(par);

		for(int i = 0; i < 200; ++i){
			Item p (rndX(gen), rndY(gen), 1);
			set2.push_back (p);
		}

		par._Init(4., 10.);
		rndX.param(par);
		par._Init(5., 10.);
		rndY.param(par);

		for(int i = 0; i < 400; ++i){
			Item p (rndX(gen), rndY(gen), 1);
			set2.push_back (p);
		}
		divide (set1, set2);*/
	}
private:
	//////////////////////////////////
	// ÒÎÆÅ ÏĞÎÁËÅÌÀ ÁÛËÀ :)
	void divide (vector<vector<Item>>& sets){
		int size1 = sets[0].size();
		int size2 = sets[1].size();
		////int middle = size/2;
		//source[0].resize(2);
		//source[1].resize(2);
		//test[0].resize(2);
		//test[1].resize(2);

		//for(int i = 0; i < middle; ++i){
		//	source[0].push_back(sets[0][i]);
		//	source[1].push_back(sets[1][i]);
		//}
		//for(int i = middle; i < size; ++i){
		//	test[0].push_back(sets[0][i]);
		//	test[1].push_back(sets[1][i]);
		//}
	}

public:	
	vector <Item> source[2],
		test[2];
};

class StandardMethod{ // ıòàëîííûõ îáğàçîâ
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
		return (k > 0); // åñëè + , òî 1. åñëè - , òî 0
	}

	double percent;
	Item standard[2];
	double radius[2];
	Set set;
	vector <bool> diff;
};

class NeighborMethod{ // áëèæàéøåãî ñîñåäà
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
	size[0] = 400;
	size[1] = 200;
	vector<vector<pair<uniform_real_distribution <double>::param_type,
		uniform_real_distribution <double>::param_type>>> options;
	options.resize(2);
	uniform_real_distribution <double>::param_type par1, par2;

	par1._Init(0., 4.);
	par2._Init(0., 7.);	
	options[0].push_back(make_pair(par1, par2));

	par1._Init(4., 8.);
	par2._Init(0., 2.);	
	options[0].push_back(make_pair(par1, par2));

	par1._Init(5., 10.);
	par2._Init(4., 10.);	
	options[1].push_back(make_pair(par1, par2));

	par1._Init(0., 5.);
	par2._Init(9., 10.);	
	options[1].push_back(make_pair(par1, par2));

	Set set(size, options);
	StandardMethod method1(set);
	NeighborMethod method2(set);


	return 0;
}