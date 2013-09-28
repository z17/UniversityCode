#include <stdio.h>
#include <vector>
#include <iostream>

using namespace std;

struct figure
{
	double x;
	double y;
	virtual void print()=0;

};
struct Circle: public figure
{
	Circle(double nx, double ny, double nradius) 
	{
		 x = nx;
		 y = ny;
		 radius = nradius;
	}
	double radius;
	virtual void print()
	{
		printf("Circle:\nx = %f\ny = %f\nradius = %f\n------------\n",x,y,radius);
	}
};

struct Triangle: public figure
{
	double length1;
	double length2;
	double a;
	virtual void print()
	{
		printf("Triangle:\nx = %f\ny = %f\nlength1 = %f\nlength2 = %f\na = %f\n------------\n",x,y,length1,length2);
	}
};

struct Rectangle: public figure
{
	double width;
	double height;
	virtual void print()
	{
		printf("Rectangle:\nx = %f\ny = %f\nwidth = %f\nheight = %f\n------------\n",x,y,width,height);
	}
};

struct figurePull
{
	vector<figure *> figures;

	void printAll()
	{
		int n = figures.size();
		for (int i = 0; i < n; i++)
		{
			figures[i] -> print();
			printf("\n----------\n");
		}
	}

	void newFigure()
	{
		int type;
		printf ("\n1 - circle, 2 - tr, 3 - rectangle\n");
		scanf("%d",&type);
		double x,y;
		figure *newFig = 0;
		switch ( type )
		{
		case 1:
			printf ("x,y,radius\n");
			double radius;
		//	scanf ("%f",&x);
		//	scanf ("%f",&y);
		//	scanf ("%f",&radius);
			cin >> x >> y >> radius;
			newFig = new Circle(x,y,radius);
		//	newFig -> x = x;
	//		newFig -> y = y;
	//		newFig -> radius = radius;
			figures.push_back(newFig);
			break;
		case 2:
			newFig = new Triangle;
			break;
		case 3:
			newFig = new Triangle;
			break;
		default: 
			printf("error\n");
		 }
	
	}
};

void main()
{

	figurePull a;
	a.newFigure();
	a.printAll();
}
