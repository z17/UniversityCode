#include <iostream>
#include <fstream>
#include <vector>

using namespace std;

class IShapeObserver 
{   
private:
	virtual void OnChange( int pos, double x, double y ) = 0;  
};

class myObserver : IShapeObserver
{

	void OnChange(int pos, double x, double y)
	{
		cout << "change: id = " << pos << " x = " << x << " y = " << y << endl;
	}
};

struct point
{
	double x;
	double y;
	point()
	{
		x = 0;
		y = 0;
	}
	point (double _x, double _y)
	{
		x = _x;
		y = _y;
	}
};

class PointWrapper
{
	vector<point *> points;
	vector < myObserver* > Observers;

public:	
	PointWrapper()
	{
	}
	~PointWrapper()
	{
	}

	void addPoint(double x, double y)
	{
		point * newpoint = new point(x,y);
		points.push_back(newpoint);
	}
	
	void printPoints()
	{
		int n = points.size();
		for (int i = 0; i < n; i++)
		{
			cout << points[i]->x << " " << points[i]->y << endl;
		}
	}
	void pointChange(int pos, double _x, double _y)
	{
		points[pos]->x = _x;
		points[pos]->y = _y;
		for ( int i =0; i < Observers.size(); i++ ) 
		{ 
			Observers[i] -> OnChange(pos, _x,  _y); 
		} 
	}

	void RegisterObserver (myObserver* ptr_observer )
	{
		 Observers.push_back( ptr_observer ); 
	}
	void UnregisterObserver (myObserver* ptr_observer )
	{
	//	 Observers.erase ( ptr_observer ); 
	}

};

int main()
{

	ifstream f("in.txt");
	PointWrapper pull;
	myObserver * ptr_obs1 = new myObserver;	
	myObserver * ptr_obs2 = new myObserver;
	pull.RegisterObserver( ptr_obs1);
	pull.RegisterObserver( ptr_obs2);
	int n;
	f >> n;
	double x,y;
	for (int i = 0; i < n; i++)
	{
		f >> x >> y;
		pull.addPoint(x,y);
	}
	//pull.printPoints();
	pull.pointChange(2,9,9);

	f.close();
	system("pause");
	return 0;
}
