#include <vector>
#include <string>

/*
to do:
+ проверка добавлено ли такое св-во уже (убрать дублирование при описании)
+ для свойств ввести отрицание !<свойство>, его приоритет
- проверка на существование родителя
- если родителя не существует - создавать объект с пустыми свойствами, если дальше он описывается - дописывать св-ва в этот объект
- вывод всех родителей
+ вынесение в заголовочный файл части
*/

// объединение массивов
template <typename T>
std::vector<T> merge(std::vector<T>& one, std::vector<T>& two); 

// для каждого класса
struct customClass
{
private:
	std::string name;						// имя	
	customClass * parent;					// ссылка на родителя
	std::vector<std::string> properties;	// свойства

public:
	customClass();
	customClass(std::string, customClass *, std::vector<std::string>);
	std::string getNameClass();						// возвращает имя 
	std::vector<std::string> getListProperties();	// возвращает список свойств
	std::vector<std::string> getAllProperties();	// рекурсивно возвращает все свойства класса (свои и всех родителей)
	void printClass();								// вывод
	bool findProperty(std::string);					// поиск свойства в списке свойств
	int findProperty (std::string, std::vector<std::string>);	// возвращает номер свойства в массиве или -1, если не найден
};

// обёртка - массив классов
struct classWrap
{
	std::vector<customClass *> massOfClasses;		// массив классов 

	classWrap();
	void addClass(std::string, std::string, std::vector<std::string>);	// добавление класса
	bool loadFile(std::string);											// загрузка из файла
	void printClasses();												// вывод всех классов
	bool isProperty(std::string, std::string);				// проверка существования свойства в определённом классе
};