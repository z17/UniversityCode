#include <vector>
#include <string>

/*
to do:
+ �������� ��������� �� ����� ��-�� ��� (������ ������������ ��� ��������)
+ ��� ������� ������ ��������� !<��������>, ��� ���������
- �������� �� ������������� ��������
- ���� �������� �� ���������� - ��������� ������ � ������� ����������, ���� ������ �� ����������� - ���������� ��-�� � ���� ������
- ����� ���� ���������
+ ��������� � ������������ ���� �����
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

public:
	customClass();
	customClass(std::string, customClass *, std::vector<std::string>);
	std::string getNameClass();						// ���������� ��� 
	std::vector<std::string> getListProperties();	// ���������� ������ �������
	std::vector<std::string> getAllProperties();	// ���������� ���������� ��� �������� ������ (���� � ���� ���������)
	void printClass();								// �����
	bool findProperty(std::string);					// ����� �������� � ������ �������
	int findProperty (std::string, std::vector<std::string>);	// ���������� ����� �������� � ������� ��� -1, ���� �� ������
};

// ������ - ������ �������
struct classWrap
{
	std::vector<customClass *> massOfClasses;		// ������ ������� 

	classWrap();
	void addClass(std::string, std::string, std::vector<std::string>);	// ���������� ������
	bool loadFile(std::string);											// �������� �� �����
	void printClasses();												// ����� ���� �������
	bool isProperty(std::string, std::string);				// �������� ������������� �������� � ����������� ������
};