#include <iostream>
#include <vector>
#include <stdlib.h>
#include <string>
#include <map>
using namespace std;


struct object
{
	// правила формирования св-в объектов:
	// 1. св-во - слово/словосочетание, пример "propety"
	// 2. св-во - слово/словосочетание, в конце через пробел имя доп. объекта, к которому относится "propety name_object"
	// search для определения наличия свойств 1-ого типа
	// getpart для определения наличия свойств 2-ого типа и возвращения названия доп. объекта

	vector<string> options;	

	bool search(string option)
	{
		bool fl = false;
		if (this == false)	// на случай если происходит поиск в несуществующем объекте
		{
			return fl;
		}

		for (int i = 0; i < options.size(); i++)
		{
			if (options[i] == option)
			{
				fl = true;
				return fl;
			}
		}
		return fl;
	}

	string getpart(string option)
	{
		string name = "-1";
		if (this == false)	// на случай если происходит поиск в несуществующем объекте
		{
			return "-1";
		}

		for (int i = 0; i < options.size(); i++)
		{
			if (options[i].find(option) == 0)
			{
				name = options[i].substr(option.length(), options[i].length() - option.length());
			}
		}
		return name;
	}
};

void main()
{
	map <string, object *> conformity;


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

	
	conformity.insert(pair<string,object *>("c1",c1));
	conformity.insert(pair<string,object *>("c2",c2));
	conformity.insert(pair<string,object *>("c3",c3));
	conformity.insert(pair<string,object *>("sergey",sergey));
	conformity.insert(pair<string,object *>("alex",alex));	
	conformity.insert(pair<string,object *>("igor",igor));


	string comand;

	cin >> comand;
	while (comand != "exit")
	{
		
		string name;

		bool fl = false;

		// вырезаем содержимое скобок (если оно есть)
		// так определяем параметр
		name = comand.substr(comand.find("(")+1,comand.find(")")-comand.find("(")-1);

		if (comand.find("tablePC(") != string::npos)
		{
			if (conformity[name] -> search("pc") && conformity[name] -> search("ontable"))
				fl = true;
		}
		if (comand.find("notebookPC(") != string::npos)
		{
			if (conformity[name] -> search("pc") && conformity[name] -> search("portable") && conformity[name] -> search("untouchscreen"))
				fl = true;
		}
		if (comand.find("tabletPC(") != string::npos)
		{
			if (conformity[name] -> search("pc") && conformity[name] -> search("portable") && conformity[name] -> search("touchscreen"))
				fl = true;
		}
		if (comand.find("havePC(") != string::npos)
		{
			string objName = conformity[name] -> getpart("have ");
			if (conformity[objName] -> search("pc"))
				fl = true;
		}
		cout << fl << endl;
		cin >> comand;
	}
}