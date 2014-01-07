#include <iostream>
#include <vector>
#include <stdlib.h>
#include <string>
using namespace std;


struct object
{
	vector<string> options;
};

void main()
{
	object *c1 = new object;
	object *c2 = new object;
	object *c3 = new object;

	c1 -> options.push_back("pc");
	c2 -> options.push_back("pc");
	c3 -> options.push_back("pc");
	
	c1 -> options.push_back("ontable");
	
	c2 -> options.push_back("portable");	
	c3 -> options.push_back("portable");

	c2 -> options.push_back("untouchscreen");	
	c3 -> options.push_back("touchscreen");
	
	object *sergey = new object;	
	object *alex = new object;	
	object *igor = new object;

	sergey -> options.push_back("have c1");
	alex -> options.push_back("have c2");
	igor -> options.push_back("have c5");

	string comand;

	cin >> comand;
	
	string name;

	// вырезаем содержимое скобок (если оно есть)
	// так определяем параметр
	name = comand.substr(comand.find("(")+1,comand.find(")")-comand.find("(")-1);
	
	if (comand.find("tablePC") != string::npos)
	{
		
	}

	if (comand.find("notebookPC") != string::npos)
	{
	}

	if (comand.find("tabletPC") != string::npos)
	{
	}

	if (comand.find("havePC") != string::npos)
	{
	}
	
	cout << name << endl;
}