#include <iostream>
#include <fstream>
#include <algorithm>
#include <vector>
#include <string>
#include <stdlib.h>
#include <cstdlib>

#include "head.h"

using namespace std;

template <typename T>
vector<T> merge(vector<T>& one, vector<T>& two)
{
	vector<T> res;

	res = one;

	for (int i = 0; i < two.size(); i++)
	{
		res.push_back(two[i]);
	}

	return res;
}

template <typename T>
vector<T> merge(T& one, vector<T>& two)
{
	vector<T> res;

	res = two;

	res.insert(res.begin(), one);
	return res;
}


customClass::customClass()
{
}

customClass::customClass(string nameOfClass, customClass * parentClass, vector<string> listProperties)
{
	this -> name = nameOfClass;
	this -> properties = listProperties;
	this -> parent = parentClass;
}

string customClass::getNameClass()
{
	return this -> name;
}

vector<string> customClass::getListProperties()
{
	return this -> properties;
}

vector<string> customClass::getAllParents()
{
	vector<string> result;

	if (this != NULL)
	{
		if (this->parent != NULL)
		{
			result = merge(this->getNameClass(),this->parent->getAllParents());
		}
		else
		{
			result.push_back(this->getNameClass());
		}
	}
	return result;
}

void customClass::printAllParents()
{
	vector<string> parents = this->getAllParents();
	for (int i = 0; i < parents.size(); i++)
	{
		cout << parents[i];
		if (i != parents.size() -1)
		{
			cout << " < ";
		}
	}
	cout << endl;
}

vector<string> customClass::getAllProperties()
{
	vector<string> allProperties;
	if (this != NULL)
	{
		if (this->parent != NULL)
		{
			allProperties = merge(this->properties,this->parent->getAllProperties());
		}
		else
		{
			allProperties = this->properties;
		}
	}
	
	// �������� �� ���������� ������ ���������� �������
	int i = 0;
	while (i < allProperties.size())
	{
		if (allProperties[i][0] == '!')
		{
			string invProperty = allProperties[i].substr(1,allProperties[i].size()-1);
			int nPos = this->findProperty(invProperty,allProperties);
			if (nPos >= 0 && nPos > i)
			{
				// �������� !<��������> � <��������>
				allProperties.erase(allProperties.begin()+nPos);
				allProperties.erase(allProperties.begin()+i);
				i--;
				i--;
			}
			if  (nPos < i)
			{
				// �������� !<��������> ���� ��� ������� ������ ������� <��������>
				allProperties.erase(allProperties.begin()+i);
				i--;
			}
		}
		i++;
	}
	return allProperties;
}

void customClass::printClass()
{
	cout << "Class" << endl;
	cout << "Name: " << this -> name << endl;
	cout << "Properties: ";
	vector<string> currentProperties;
	currentProperties = this -> getAllProperties();			
	for (int i = 0; i < currentProperties.size(); i++)
	{
		cout << currentProperties[i];
		if (i + 1 != currentProperties.size())
		{
			cout << ", ";
		}
	}
	cout << endl << "---------" << endl;
}

bool customClass::findProperty(string nameProperty)
{
	bool fl = false;
	vector<string> allPropertes = this->getAllProperties();
	
	int i = -1;		
	do
	{
		i++;	
	}
	while (allPropertes[i] != nameProperty && i+1 < allPropertes.size());
	if (allPropertes[i] == nameProperty)
	{
		fl = true;
	}
	return fl;
}

int customClass::findProperty (string nameProperty, vector<string> list)
{
	int i = -1;		
	do
	{
		i++;	
	}
	while (list[i] != nameProperty && i+1 < list.size());

	if (list[i] != nameProperty)
	{
		i = -1;
	}
	return i;
}

bool customClass::setProperties(vector<string> newProperties)
{
	bool fl = false;
	if (this->properties.size() == 0)
	{
		this->properties = newProperties;
		fl = true;
	}
	return fl;
}

classWrap::classWrap()
{
}

int classWrap::isClass(string nameClass)
{
	int result = -1;

	if (this->massOfClasses.size() != 0)	// ���� � ������� ���� ���-�� ����
	{
		int i = -1;
		do
		{
			i++;	
		}
		while (this->massOfClasses[i]->getNameClass() != nameClass && i+1 < this->massOfClasses.size());

		if (this->massOfClasses[i]->getNameClass() == nameClass)
		{
			if (this->massOfClasses[i]->getAllProperties().size() == 0)
			{
				result = i;
			}
			else
			{
				result = -2;
			}
		}
	}

	return result;
}

void classWrap::addClass(string name, string nameParent, vector<string> properties)
{
	int posClass = this->isClass(name);
	if (posClass == -2)
	{
		// ���� ����� ����������, � ����������� - ������
		cout << "ERROR: duplicate description object" << endl;
		exit(EXIT_FAILURE);
	}
	if (posClass == -1)
	{
		// ���� ������ ������ �� ������������
		customClass * parent = NULL;
		if (nameParent != "")
		{
			// ���������� ���� �� ��������
			bool fl = false;
			int i = -1;
			if (this->massOfClasses.size() != 0)	// ���� � ������� ���� ���-�� ����
			{			
				do
				{
					i++;	
				}
				while (this->massOfClasses[i]->getNameClass() != nameParent && i+1 < this->massOfClasses.size());

				if (this->massOfClasses[i]->getNameClass() == nameParent)
				{
					fl = true;
				}
			}
			
			if (fl)
			{
				parent = this->massOfClasses[i];
			}
			else
			{
				// ���� �������� ��� ������, �� �� ������ - �������� ��������
				vector<string> parentProperties;
				
				this->addClass(nameParent, "", parentProperties);
				parent = this->massOfClasses[this->massOfClasses.size()-1];
			}
		}

		// �������� ������������ �������. ���� ���� ������������ - �������
		vector<string> test = merge(properties, parent->getAllProperties());
		int lenght = properties.size();
		int i = 0;
		while (i < lenght)
		{
			int k = 0;
			for (int j = 0; j < test.size(); j++)
			{
				if (test[i] == test[j])
				{
					k++;
				}
			}
			if (k > 1)
			{
				test.erase(test.begin() + i);
				lenght--;
			}
			else
			{
				i++;
			}
			properties.assign(test.begin(), test.begin()+lenght);
		}

		customClass *newClass = new customClass(name, parent, properties);
		massOfClasses.push_back(newClass);
	}
	else
	{
		// ���� ����� ����������, �� ������,���������� ����� ��-�� � ����
		this->massOfClasses[posClass]->setProperties(properties);
	}
}

bool classWrap::loadFile(string path)
{
	ifstream f(path.c_str());
	string str;
	string activeClass;
	string activeProperties;
	string parentClass = "";
	while (getline(f,str))
	{
		// ���� ����� �������� ����� Class - �������� ��� ���
		if (str.substr(0, 6) == "Class:")
		{
			activeClass = str.substr(7, str.length()-7);
		}
		// ���� ����� �������� ����� Properties: - �������� � ��������� � ������ ��������, � ������ ����� �����
		if (str.substr(0, 11) == "Properties:")
		{
			parentClass = "";	// ��������� ����������� ��������
			vector<string> parentsProperties;
			// ���������� ������������
			if (activeClass.find("<") < string::npos)
			{
				parentClass = activeClass.substr(activeClass.find("<") + 2, activeClass.length() - activeClass.find("<") + 1);
				activeClass = activeClass.substr(0, activeClass.find("<") - 1);
			}

			// �������������� ������� � ������
			vector<string> newPropeties;
			if (str.length() > 11)
			{
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
			}
			this -> addClass(activeClass, parentClass, newPropeties);
		}
	}
	f.close();
	return true;
}

void classWrap::printClasses()
{
	for (int i = 0; i < this->massOfClasses.size(); i++)
	{
		this->massOfClasses[i]->printClass();
	}
}

bool classWrap::isProperty(string className, string propetyName)
{
	bool fl = false;
	if (this -> massOfClasses.size() != 0 )
	{
		int i = -1;
		do
		{
			i++;	
		}
		while (this->massOfClasses[i]->getNameClass() != className && i+1 < this->massOfClasses.size());

		if (this->massOfClasses[i]->getNameClass() == className)
		{
			fl = this->massOfClasses[i]->findProperty(propetyName);
		}
	}
	return fl;
}
void classWrap::printParentsOfClass(string className)
{
	if (this -> massOfClasses.size() != 0 )
	{
		int i = -1;
		do
		{
			i++;	
		}
		while (this->massOfClasses[i]->getNameClass() != className && i+1 < this->massOfClasses.size());

		if (this->massOfClasses[i]->getNameClass() == className)
		{
			this->massOfClasses[i]->printAllParents();
		}
	}
}

void main()
{
	setlocale (LC_CTYPE,"Russian");

	classWrap test;

	test.loadFile("input2.txt");

	// ��������� ������� - "����� ������ � ��������"
	// ����� �� ������� - ��/���
	string comand;
	string nameClass;
	string nameProperty;
	cout << "������� �������" << endl;
	cout << "\tprintall\t- ������� ��" << endl;
	cout << "\tprint <class>\t- ������� ��������� ������" << endl;
	cout << "\texit\t- �����" << endl;
	cout << "\t<���_������> <��� ��������>\t- ������ ������������� �������� � ������" << endl;
	getline(cin,comand);
	while (comand != "exit")
	{
		bool flComand = false;
		if (comand == "printall" && !flComand)
		{
			test.printClasses();
			flComand = true;
		}
		if (comand.find("print ") < string::npos && !flComand)
		{
			string className = comand.substr(6,comand.length()-6);
			test.printParentsOfClass(className);
			flComand = true;
		}
		if (!flComand)
		{
			nameClass = comand.substr(0,comand.find(" "));
			nameProperty = comand.substr(comand.find(" ")+1, comand.size() - comand.find(" ") - 1);
			
			bool fl = test.isProperty(nameClass,nameProperty);
			if (fl) {
				cout << "Yes" << endl;
			} else {
				cout << "No" << endl;
			}
		}
		getline(cin,comand);
	}	
}