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

customClass::customClass(string nameOfClass, customClass * parentClass, vector<string> listProperties, vector<string> listContent)
{
	this -> name = nameOfClass;
	this -> properties = listProperties;
	this -> content = listContent;
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

vector<string> customClass::getListContent()
{
	return this -> content;
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
	cout << "-- Class --" << endl;
	cout << "Name: " << this -> name << endl;
	vector<string> currentProperties;
	currentProperties = this -> getAllProperties();		
	if (currentProperties.size() > 0)
	{
		cout << "Properties: ";	
		for (int i = 0; i < currentProperties.size(); i++)
		{
			cout << currentProperties[i];
			if (i + 1 != currentProperties.size())
			{
				cout << ", ";
			}
		}
		cout << endl;
	}
	vector<string> currentContent;
	currentContent = this -> getListContent();	
	//currentProperties = this -> getAllProperties();		// �������� ��� �������	
	if (currentContent.size() > 0)
	{
		cout << "Content: ";
		for (int i = 0; i < currentContent.size(); i++)
		{
			cout << currentContent[i];
			if (i + 1 != currentContent.size())
			{
				cout << ", ";
			}
		}
		cout << endl;
	}
	cout << endl;
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
	if (newProperties.size() == 0)
	{
		fl = true;
	}
	return fl;
}

bool customClass::setContent(vector<string> newContent)
{
	bool fl = false;
	if (this->content.size() == 0)
	{
		this->content = newContent;
		fl = true;
	}
	if (newContent.size() == 0)
	{
		fl = true;
	}
	return fl;
}


classWrap::classWrap()
{	
	this -> options = new templateDescription;
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
			if (this->massOfClasses[i]->getListProperties().size() > 0 && this->massOfClasses[i]->getListContent().size() > 0)
			{
				result = -2;
			}
			else
			{
				result = i;
			}

		/*	if (this->massOfClasses[i]->getListProperties().size() == 0 ||)
			{
				result = i;
			}
			else
			{
				result = -2;
			}
		*/
		}
	}

	return result;
}

void classWrap::addClass(string name, string nameParent, vector<string> properties, vector<string> content)
{
	int posClass = this->isClass(name);
	if (posClass == -2)
	{
		// ���� ����� ����������, � ����������� - ������
		cout << "ERROR: duplicate description object" << endl;
		exit(EXIT_FAILURE);
	}

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
			vector<string> emptyVector;
			
			this->addClass(nameParent, "", emptyVector, emptyVector);
			parent = this->massOfClasses[this->massOfClasses.size()-1];
		}
	}

	// �������� ������������ �������. ���� ���� ������������ - �������
	// ��� content �������� ������������ �� �����
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

	if (posClass == -1)
	{
		// ���� ������ ������ �� ������������		
		customClass *newClass = new customClass(name, parent, properties, content);
		massOfClasses.push_back(newClass);
	}
	else
	{
		// ���� ����� ����������, �� ������, ���������� ����� ��-�� � ���������� � ����
		bool flag1, flag2;
		flag1 = this->massOfClasses[posClass]->setProperties(properties);
		flag2 = this->massOfClasses[posClass]->setContent(content);
		if (!flag1 || !flag2)
		{
			cout << "ERROR: duplicate description object" << endl;
			exit(EXIT_FAILURE);
		}
	}
}

bool classWrap::loadFile(string path)
{
	ifstream f(path.c_str());
	string str;
	string activeClass;
	string activeProperties;
	string activeContent;
	string parentClass = "";
	vector<string> emptyVector;
	while (getline(f,str))
	{

		// ���� ����� �������� ����� ������ - �������� ��� ��� � ������ �����
		// ����������� ������ �� ���������� ��������� ����� ������ ��������� � �������� ������
		if (str.substr(0, this->options->prefixClass.length()) == this->options->prefixClass)
		{
			parentClass = "";	// ��������� ����������� ��������

			activeClass = str.substr(this->options->prefixClass.length(), str.length()- this->options->prefixClass.length());
			// ���������� ������������
			if (activeClass.find(this->options->symbolInheritance) < string::npos)
			{
				int pos = activeClass.find(this->options->symbolInheritance);
				int lengthSymbol = this->options->symbolInheritance.length();

				parentClass = activeClass.substr(pos + lengthSymbol, activeClass.length() - pos - lengthSymbol);
				activeClass = activeClass.substr(0, pos);
			}

			this -> addClass(activeClass, parentClass, emptyVector, emptyVector);
		}

		// ���� ����� �������� ����� ������� - �������� � ��������� � ������ ��������, � ������ ����� �����
		if (str.substr(0, this->options->prefixProperties.length()) == this->options->prefixProperties)
		{
			// �������������� ������� � ������
			vector<string> newPropeties;
			int lPrefix = this->options->prefixProperties.length();
			if (str.length() > lPrefix)
			{
				activeProperties = str.substr(lPrefix, str.length() - lPrefix);
				string oneProp;
				int newPos = 0;
				while (activeProperties.find(this->options->separator) < string::npos)
				{
					newPos = activeProperties.find(this->options->separator);
					oneProp = activeProperties.substr(0,newPos);
					activeProperties = activeProperties.substr(newPos + this->options->separator.length(), activeProperties.length() - newPos);
					newPropeties.push_back(oneProp);
				}
				newPropeties.push_back(activeProperties);
			}
			this -> addClass(activeClass, parentClass, newPropeties, emptyVector);
		}		

		// ���� ����� �������� ����� �������� - �������� � ��������� � ������ ��������, � ������ ����� �����
		if (str.substr(0, this->options->prefixContent.length()) == this->options->prefixContent)
		{
			// �������������� ������� � ������
			vector<string> newContent;			
			int lPrefix = this->options->prefixContent.length();
			if (str.length() > 11)
			{
				activeContent = str.substr(lPrefix, str.length()-lPrefix);
				string oneCont;
				int newPos = 0;
				while (activeContent.find(this->options->separator) < string::npos)
				{
					newPos = activeContent.find(this->options->separator);
					oneCont = activeContent.substr(0,newPos);
					activeContent = activeContent.substr(newPos + this->options->separator.length(), activeContent.length() - newPos);
					newContent.push_back(oneCont);
				}
				newContent.push_back(activeContent);
			}
			this -> addClass(activeClass, parentClass, emptyVector, newContent);
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
		else
		{
			cout << "class not found" << endl;
		}
	}
}

templateDescription::templateDescription()
{
	this->prefixClass = "Class: ";
	this->prefixProperties = "Properties: ";
	this->prefixContent = "Content: ";
	this->symbolInheritance = " < ";
	this->separator = ", ";
/*	
input3.txt
	this->prefixClass = "!";
	this->prefixProperties = "?";
	this->prefixContent = "-";
	this->symbolInheritance = "*";
	this->separator = "^";
*/
}

templateDescription::templateDescription(string prefix1, string prefix2, string prefix3, string symbol, string sep)
{
	this->prefixClass = prefix1;
	this->prefixProperties = prefix2;
	this->prefixContent = prefix3;
	this->symbolInheritance = symbol;
	this->separator = sep;
}

void main()
{
	setlocale (LC_CTYPE,"Russian");

	classWrap test;
	test.loadFile("input.txt");

	string comand;
	string nameClass;
	string nameProperty;
	cout << "������� �������" << endl;
	cout << "\tprintall\t- ������� ��" << endl;
	cout << "\tprintTree <class>\t- ������� ��������� ������" << endl;
	cout << "\texit\t- �����" << endl;
	cout << "\tproperty <���_������> <��� ��������>\t- ������ ������������� �������� � ������" << endl;
	getline(cin,comand);
	while (comand != "exit")
	{
		bool flComand = false;
		if (comand == "printall" && !flComand)
		{
			test.printClasses();
			flComand = true;
		}
		if (comand.find("printTree ") == 0 && !flComand)
		{
			string className = comand.substr(10,comand.length()-10);
			test.printParentsOfClass(className);
			flComand = true;
		}
		if (comand.find("property ") == 0 && !flComand)
		{
			comand = comand.substr(9,comand.length()-9);
			nameClass = comand.substr(0,comand.find(" "));
			nameProperty = comand.substr(comand.find(" ")+1, comand.size() - comand.find(" ") - 1);
			
			bool fl = test.isProperty(nameClass,nameProperty);
			if (fl) {
				cout << "Yes" << endl;
			} else {
				cout << "No" << endl;
			}
			flComand = true;
		}
		if (!flComand)
		{
			cout << "unknown command" << endl;
		}
		getline(cin,comand);
	}	
}