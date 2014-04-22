#include <vector>
#include <string>

/*
to do:
+ �������� ��������� �� ����� ��-�� ��� (������ ������������ ��� ��������)
+ ��� ������� ������ ��������� !<��������>, ��� ���������
+ �������� �� ������������� ��������
+ ���� �������� �� ���������� - ��������� ������ � ������� ����������, ���� ������ �� ����������� - ���������� ��-�� � ���� ������
+ �������� ��� - ������ ��� ������� �������� ������, � �������� �� ������� ��������
+ ����� ���� ���������
+ ��������� � ������������ ���� �����
+ ������� ��� ��������� (���� ������ ������� ������ "Class: ") ��������, ���� � ���� ������� �� ������������� � ���������
+ �������������� ����� ���� ��������
+ �������� � ����� ���� ����������

*/

// ����������� ��������
template <typename T>
std::vector<T> merge(std::vector<T>& one, std::vector<T>& two); 

// ��� ������� ������
struct customClass
{
private:
	std::string name;						// ���	
	customClass * parent;					// ������ �� ��������
	std::vector<std::string> properties;	// ��������
	std::vector<std::string> content;

public:
	customClass();
	customClass(std::string, customClass *, std::vector<std::string>, std::vector<std::string>);
	std::string getNameClass();						// ���������� ��� 
	std::vector<std::string> getListProperties();	// ���������� ������ �������
	std::vector<std::string> getAllProperties();	// ���������� ���������� ��� �������� ������ (���� � ���� ���������)
	std::vector<std::string> getListContent();		// ���������� ������ �����������
	void printClass();								// �����
	bool findProperty(std::string);					// ����� �������� � ������ �������
	int findProperty (std::string, std::vector<std::string>);	// ���������� ����� �������� � ������� ��� -1, ���� �� ������
	bool setProperties(std::vector<std::string>);			// ���������� � properties �������� �� ���� ������, ���� �� ����, ����� ���������� false 
	bool setContent(std::vector<std::string>);				// ���������� � content �������� �� ���� ������, ���� �� ����, ����� ���������� false 
	std::vector<std::string> getAllParents();				// ���������� ������ ���� ���������
	void printAllParents();									// ������� ������ ���� ���������
};

// ���������, ���������� ��������� ���������
struct templateDescription
{
	std::string prefixClass;
	std::string prefixProperties;
	std::string prefixContent;
	std::string symbolInheritance;
	std::string separator;

	templateDescription();																	// ��������� ����������
	templateDescription(std::string, std::string, std::string, std::string, std::string);	// ������������� ����������
};

// ������ - ������ �������
struct classWrap
{
	std::vector<customClass *> massOfClasses;		// ������ ������� 
	templateDescription* options;

	classWrap();
	void addClass(std::string, std::string, std::vector<std::string>, std::vector<std::string>);	// ���������� ������
	bool loadFile(std::string);								// �������� �� �����
	void printClasses();									// ����� ���� �������
	bool isProperty(std::string, std::string);				// �������� ������������� �������� � ����������� ������
	int isClass(std::string);				// �������� ������������� ������. ����������: -1 - ����� �� ����������,  -2 - ����� ����������, �� �������� (������), ������ ������ � ������� massOfClasses ���� ����� ���������, �� �� �������� ����������
	void printParentsOfClass(std::string);	// ����� ������ ��������� ������
	
};
