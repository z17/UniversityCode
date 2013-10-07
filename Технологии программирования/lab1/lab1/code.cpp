#include <stdio.h>
#include <vector>
#include <iostream>
#include <clocale>
#include <fstream>

using namespace std;

struct figure
{
	double x;
	double y;
	virtual void print()=0;

};

struct Circle: public figure
{
	double radius;
	
	Circle(double nx, double ny, double nradius) 
	{
		 x = nx;
		 y = ny;
		 radius = nradius;
	}
	virtual void print()
	{
		cout << "Circle:\n";
		cout << "x = " << x << "\n";
		cout << "y = " << y << "\n";
		cout << "radius = " << radius << "\n";
	}
};

struct Triangle: public figure
{

	double z;
	
	Triangle(double nx, double ny, double nz) 
	{
		x = nx;
		y = ny;
		z = nz;
		}
	virtual void print()
	{
		cout << "Triangle:\n";
		cout << "x = " << x << "\n";
		cout << "y = " << y << "\n";
		cout << "z = " << z << "\n";
	}
};

struct Rectangle: public figure
{
	double z;
	double q;
	
	Rectangle(double nx, double ny, double nz, double nq)
	{
		x = nx;
		y = ny;
		z = nz;
		q = nq;
	}
	virtual void print()
	{
		cout << "Rectangle:\n";
		cout << "x = " << x << "\n";
		cout << "y = " << y << "\n";
		cout << "z = " << z << "\n";
		cout << "q = " << q << "\n";
	}
};

struct figurePull
{
	vector<figure *> figures;

	void printAll()
	{
		int n = figures.size();
		ofstream out ("out.txt");
		for (int i = 0; i < n; i++)
		{
			figures[i] -> print();
			cout << "\n";
		}
	}

	void newFigure()
	{
		int type;
		cin >> type;
		double x,y,z,q;
		figure *newFig = 0;
		switch ( type )
		{
		case 1:
			cin >> x >> y >> q;
			newFig = new Circle(x,y,q);
			figures.push_back(newFig);
			break;
		case 2:
			cin >> x >> y >> z;
			newFig = new Triangle(x,y,z);
			figures.push_back(newFig);
			break;
		case 3:
			cin >> x >> y >> z >> q;
			newFig = new Rectangle(x,y,z,q);
			figures.push_back(newFig);
			break;
		default: 
			cout << "error\n";
		 }
	}
	void newFigure(int type, double x, double y, double z, double q)	// для теста1
	{
		figure *newFig = 0;
		switch ( type )
		{
		case 1:
			newFig = new Circle(x,y,q);
			figures.push_back(newFig);
			break;
		case 2:
			newFig = new Triangle(x,y,z);
			figures.push_back(newFig);
			break;
		case 3:
			newFig = new Rectangle(x,y,z,q);
			figures.push_back(newFig);
			break;
		default: 
			cout << "error\n";
		 }
	}
};

void main()
{	
	/* тест 1
	figurePull a;
	freopen("out.txt", "w", stdout);
	a.newFigure(1,1,1,1,1);
	a.newFigure(2,1,2,1,0);
	a.newFigure(3,3,1,2,4);
	a.printAll();
	*/

	/* тест 2
	figurePull a;
	freopen("in.txt", "r", stdin);
	a.newFigure();
	a.newFigure();
	a.newFigure();
	a.printAll();
	*/
}
