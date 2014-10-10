#include <iostream>
#include <fstream>
#include <vector>

using namespace std;



class IShapeObserver 
{   
public:
	virtual void OnChange( int pos, double x, double y ) = 0;  
};

class myObserver : IShapeObserver
{
public:
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
		for (int i = 0; i < points.size(); i++)
		{
			delete(points[i]);
		}
	}
	
	vector<point *> getPoints()
	{
		return points;
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
		int i = 0;
		while ( i < Observers.size() && Observers[i] != ptr_observer)
		{
			i++;
		}
		if ( i != Observers.size())
		{
			Observers.erase ( Observers.begin() + i );	
		}
	}

};

class ISaver
{
public:
	virtual void SaveData(vector<point * > &data) = 0;
	virtual ~ISaver()
	{
	}
};

class saveInFile : public ISaver
{
public:
	virtual void SaveData(vector<point * > &data)
	{
		fstream f(name);
		for(int i = 0; i < data.size(); i++)
		{
			f << data[i]->x << " " << data[i]->y << endl;
		}
		f.close();
	}
	~saveInFile()
	{
	}
	saveInFile()
	{
		name = "default.txt";
	}
	saveInFile(char* _name)
	{
		name = _name;
	}
private:
	char* name;
};


int main()
{

	ifstream f("input.txt");
	ISaver * ptr_saver = new saveInFile("out.txt");
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
	pull.UnregisterObserver(ptr_obs1);
	ptr_saver->SaveData(pull.getPoints());
	f.close();
	system("pause");
	return 0;
}
