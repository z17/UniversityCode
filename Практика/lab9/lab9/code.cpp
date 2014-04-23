#include <iostream>

using namespace std;

struct myClass
{
	int val;
	myClass()
	{
		val = 0;
	}
};

// shared_ptr
template <typename T>
class shared_ptr
{
	T *obj;
	int *count;

	public:
	shared_ptr()
	{ 
		count = new int;
		*count = 0;
	}
	shared_ptr(T *_obj)
	{ 
		count = new int;
		*count = 1;
		obj = _obj;
	}
	~shared_ptr() 
	{	
		*count--;
		if(*count == 0) 
		{
			delete count;
			delete obj;
		}
	}

	T* operator->() 
	{ 
		return obj; 
	}

	T& operator* () 
	{ 
		return *obj; 
	}

	 shared_ptr & operator = (const shared_ptr<T> & _obj)
	 {
		obj = _obj.obj;
		count = _obj.count;
		*count++;
		return *this;
	 }
};


int main()
{
	shared_ptr<myClass> p1(new myClass);
	shared_ptr<myClass> p2;
	p1 -> val = 5;
	p2 = p1;
	

	return 0;
}