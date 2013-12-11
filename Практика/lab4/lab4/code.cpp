#include <stdio.h>
#include <string>
#include <iostream>
#include <fstream>
#include <vector>
using namespace std;


vector <vector <int> > swap (vector<vector<int>> s, int n)
{
	vector<vector<int>> s2(3,3);
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < n; j++)
		{
			s2[i][j] = s[n-j-1][i];
		}
	}
	return s2;
}

vector <vector <int> > swapWrap(vector<vector<int>> s, int n, int angl)
{
	vector <vector<int> > s2(n,n);
	s2 = s;
	switch (angl)
	{
		case 90 :
			s2 = swap(s,n);
			break;
		case 180 :
			s2 = swap(s,n);
			s2 = swap(s2,n);
			break;
		case 270 :
			s2 = swap(s,n);
			s2 = swap(s2,n);
			s2 = swap(s2,n);
			break;
	}
	return s2;

};


void printMas(vector <vector<int> >  s)
{
	int n = s.size();
	cout << endl;
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < n; j++)
		{
			cout << s[i][j] << " ";
		}
		cout << endl;
	}

}

// ----------------------------

void Test_Proverka(bool cond, const char* testMsg)
{
	if(!cond) throw testMsg;
}

typedef void (*test_func)();
void LetsGoTest(test_func test, const char* testName, int* successCount) {
	cout<<"Test - "<<testName<<" : ";
	try {
		test();
		cout<<" PASS";
		++(*successCount);
	} catch(const char* msg) { 
		cout<<" FAIL : "<<msg;
	} catch(...) { 
		cout<<" FAIL : unknown exception";
	}
	cout<<endl;
}

void Test_90()
{
	int n = 3;
	int angl = 90;
	vector <vector<int> > in(n,n);
	int a = 1;
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < n; j++)
		{
			in[i][j] = a;
			a ++;
		}
	}
	vector <vector<int> > out(n,n);
	out[0][0] = 7;
	out[0][1] = 4;
	out[0][2] = 1;
	out[1][0] = 8;
	out[1][1] = 5;
	out[1][2] = 2;
	out[2][0] = 9;
	out[2][1] = 6;
	out[2][2] = 3;

	Test_Proverka(swapWrap(in,n,angl)==out,"ERROR");
}
void Test_180()
{
	int n = 3;
	int angl = 180;
	vector <vector<int> > in(n,n);
	int a = 1;
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < n; j++)
		{
			in[i][j] = a;
			a ++;
		}
	}
	vector <vector<int> > out(n,n);
	out[0][0] = 9;
	out[0][1] = 8;
	out[0][2] = 7;
	out[1][0] = 6;
	out[1][1] = 5;
	out[1][2] = 4;
	out[2][0] = 3;
	out[2][1] = 2;
	out[2][2] = 1;

	Test_Proverka(swapWrap(in,n,angl)==out,"ERROR");
}
void Test_270()
{
	int n = 3;
	int angl = 270;
	vector <vector<int> > in(n,n);
	int a = 1;
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < n; j++)
		{
			in[i][j] = a;
			a ++;
		}
	}
	vector <vector<int> > out(n,n);
	out[0][0] = 3;
	out[0][1] = 6;
	out[0][2] = 9;
	out[1][0] = 2;
	out[1][1] = 5;
	out[1][2] = 8;
	out[2][0] = 1;
	out[2][1] = 4;
	out[2][2] = 7;

	Test_Proverka(swapWrap(in,n,angl)==out,"ERROR");
}
void Test_360()
{
	int n = 3;
	int angl = 180;
	vector <vector<int> > in(n,n);
	int a = 1;
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < n; j++)
		{
			in[i][j] = a;
			a ++;
		}
	}
	vector <vector<int> > out(n,n);
	out = in;

	Test_Proverka(swapWrap(swapWrap(in,n,angl),n,angl)==out,"ERROR");
}

void main()
{
	setlocale (LC_CTYPE,"Russian");
	int n = 3;

	vector <vector<int> > s(n,n);

	int successCount=0;
	LetsGoTest(Test_90,"correct answer 90",&successCount);
	LetsGoTest(Test_180,"correct answer 180",&successCount);
	LetsGoTest(Test_270,"correct answer 270",&successCount);
	LetsGoTest(Test_360,"correct answer 360",&successCount);

	if(4==successCount) {
		cout<<"All tests successful"<<endl;
	} else {
		cout<<"Some tests failed"<<endl;
	}
	cin >> successCount;

}