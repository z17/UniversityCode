#include <iostream>
#include <fstream>

#include <vector>
#include <string>
#include <stdlib.h>
#include <cstdlib>
#include <algorithm>

using namespace std;

struct customClass
{
private:
	string name;		
	customClass * parent;		// указатель на родителя
	vector<string> properties;

public:
	customClass()
	{
	}

	customClass(string nameOfClass, customClass * parentClass, vector<string> listProperties)
	{
		this -> name = nameOfClass;
		this -> properties = listProperties;
		this -> parent = parentClass;
	}

	string getNameClass()
	{
		return this -> name;
	}

	vector<string> getListProperties()
	{
		return this -> properties;
	}

	void printClass()
	{
		cout << "Class" << endl;
		cout << "Name: " << this -> name << endl;
		cout << "Properties: ";
		for (int i = 0; i < this->properties.size(); i++)
		{
			cout << properties[i];
			if (i + 1 != this->properties.size())
			{
				cout << ", ";
			}
		}
		cout << endl << "---------" << endl;
	}
	bool findProperty(string nameProperty)
	{
		bool fl = false;
		int i = 0;
		while (this->properties[i] != nameProperty && i > this->properties.size())
		{
			i++;	
		}
		if (this->properties[i] == nameProperty)
		{
			fl = true;
		}
		return fl;
	}
};

struct classWrap
{
	vector<customClass> massOfClasses;

	classWrap()
	{
	}

	void addClass(string name, string nameParent, vector<string> properties)
	{
		customClass * parent = NULL;

		if (nameParent != "")
		{
			// определяем есть ли родитель
			int i = -1;
			bool fl = false;
			do
			{
				i++;	
			}
			while (this->massOfClasses[i].getNameClass() != nameParent && i+1 < this->massOfClasses.size());
	
			if (this->massOfClasses[i].getNameClass() == nameParent)
			{
				fl = true;
			}
			
			if (fl)
			{
				parent = this->massOfClasses[i];
			}
		}

		customClass newClass(name, parent, properties);
		massOfClasses.push_back(newClass);
	}
	bool loadFile(string path)
	{
		ifstream f(path.c_str());
		string str;
		string activeClass;
		string activeProperties;
		string parentClass = "";
		while (getline(f,str))
		{
			// если нашли ключевое слово Class - выделяем его имя
			if (str.substr(0, 6) == "Class:")
			{
				activeClass = str.substr(7, str.length()-7);
			}
			// если нашли ключевое словл Properties: - выделяем и разбиваем в массив свойства, и создаём новый класс
			if (str.substr(0, 11) == "Properties:")
			{
				vector<string> parentsProperties;

				// определяем наследование
				if (activeClass.find("<") < string::npos)
				{
					parentClass = activeClass.substr(activeClass.find("<") + 2, activeClass.length() - activeClass.find("<") + 1);
					activeClass = activeClass.substr(0, activeClass.find("<") - 1);
				}


				// преобразование свойств в массив
				vector<string> newPropeties;
				activeProperties = str.substr(12, str.length()-12);
				string oneProp;
				int newPos = 0;
				while (activeProperties.find(",") < string::npos)
				{
					newPos = activeProperties.find(",");
					oneProp = activeProperties.substr(0,newPos);
					activeProperties = activeProperties.substr(newPos+2, activeProperties.length() - newPos+1);
					newPropeties.push_back(oneProp);
				}
				newPropeties.push_back(activeProperties);

				this -> addClass(activeClass, parentClass, newPropeties);
			}
		}
		f.close();
		return true;
	}

	void printClasses()
	{
		for (int i = 0; i < this->massOfClasses.size(); i++)
		{
			this->massOfClasses[i].printClass();
		}
	}

	bool isPropety(string className, string propetyName)
	{
		int i = 0;
		bool fl = false;
		while (this->massOfClasses[i].getNameClass() != className || i >= this->massOfClasses.size())
		{
			i++;	
		}
		if (this->massOfClasses[i].getNameClass() == className)
		{
			fl = this->massOfClasses[i].findProperty(propetyName);
		}
		return fl;
	}
};

void main()
{
	classWrap test;

	test.loadFile("input.txt");

	// структура команды - "Класс вопрос о свойстве"
	// ответ на команду - да/нет
	string comand;
	string nameClass;
	string nameProperty;
	getline(cin,comand);
	while (comand != "exit")
	{
		nameClass = comand.substr(0,comand.find(" "));
		nameProperty = comand.substr(comand.find(" ")+1, comand.size() - comand.find(" ") - 1);
		
		bool fl = test.isPropety(nameClass,nameProperty);
		if (fl) {
			cout << "Yes" << endl;
		} else {
			cout << "No" << endl;
		}
		getline(cin,comand);
	}
	test.printClasses();
}