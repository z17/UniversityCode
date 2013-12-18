#include <stdio.h>
#include <string>
#include <iostream>
#include <fstream>
#include <vector>
using namespace std;


vector <vector <int> > swap (vector<vector<int>> s)
{
	int n1 = s.size();
	int n2 = s[0].size();
	vector<vector<int>> s2(n2,n1);

	for (int i = 0; i < n1; i++)
	{
		for (int j = 0; j < n2; j++)
		{
			s2[j][i] = s[n1-1-i][j];
		}
	}
	return s2;
}

vector <vector <int> > swapWrap(vector<vector<int>> s, int angl)
{
	int n1 = s.size();
	int n2 = s[0].size();	
	vector <vector<int> > s2;

	for (int i = 0; i < n1; i++)
	{
		if (s[i].size() != n2)
		{			
			s2.resize(1);
			s2[0].resize(1);
			s2[0][0] = -1;
			return s2;
		}
	}

	switch (angl)
	{
		case 90 :
			s2 = swap(s);
			break;
		case 180 :
			s2 = swap(s);
			s2 = swap(s2);
			break;
		case 270 :
			s2 = swap(s);
			s2 = swap(s2);
			s2 = swap(s2);
			break;
		case 360 :
			s2 = s;
			break;
		default:
			s2.resize(1);
			s2[0].resize(1);
			s2[0][0] = -1;
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
void LetsGoTest(test_func test, const char* testName, int* successCount, int* allCount) 
{
	++(*allCount);
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

	Test_Proverka(swapWrap(in,angl)==out,"ERROR");
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

	Test_Proverka(swapWrap(in,angl)==out,"ERROR");
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

	Test_Proverka(swapWrap(in,angl)==out,"ERROR");
}
void Test_360()
{
	int n = 3;
	int angl = 360;
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

	Test_Proverka(swapWrap(in,angl) == out,"ERROR");
}

void Test_IncorrectAngle()
{
	int n = 3;
	int angl = 25;
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
	vector <vector<int> > out(1,1);
	out[0][0] = -1; 

	Test_Proverka(swapWrap(in,angl) == out,"ERROR");
}

void Test_NotSquere90()
{
	int n1 = 3;
	int n2 = 2;
	int angl = 90;
	vector <vector<int> > in(n1,n2);
	int a = 1;
	for (int i = 0; i < n1; i++)
	{
		for (int j = 0; j < n2; j++)
		{
			in[i][j] = a;
			a++;
		}
	}
	vector <vector<int> > out(n2,n1);
	out[0][0] = 5;
	out[0][1] = 3;
	out[0][2] = 1;
	out[1][0] = 6;
	out[1][1] = 4;
	out[1][2] = 2;

	Test_Proverka(swapWrap(in,angl)==out,"ERROR");
}
void Test_NotSquere180()
{
	int n1 = 3;
	int n2 = 2;
	int angl = 180;
	vector <vector<int> > in(n1,n2);
	int a = 1;
	for (int i = 0; i < n1; i++)
	{
		for (int j = 0; j < n2; j++)
		{
			in[i][j] = a;
			a++;
		}
	}
	vector <vector<int> > out(n1,n2);
	out[0][0] = 6;
	out[0][1] = 5;
	out[1][0] = 4;
	out[1][1] = 3;
	out[2][0] = 2;
	out[2][1] = 1;

	Test_Proverka(swapWrap(in,angl)==out,"ERROR");
}
void Test_NotSquere270()
{
	int n1 = 3;
	int n2 = 2;
	int angl = 270;
	vector <vector<int> > in(n1,n2);
	int a = 1;
	for (int i = 0; i < n1; i++)
	{
		for (int j = 0; j < n2; j++)
		{
			in[i][j] = a;
			a++;
		}
	}
	vector <vector<int> > out(n2,n1);
	out[0][0] = 2;
	out[0][1] = 4;
	out[0][2] = 6;
	out[1][0] = 1;
	out[1][1] = 3;
	out[1][2] = 5;

	Test_Proverka(swapWrap(in,angl)==out,"ERROR");
}
void Test_NotSquere360()
{
	int n1 = 3;
	int n2 = 2;
	int angl = 360;
	vector <vector<int> > in(n1,n2);
	int a = 1;
	for (int i = 0; i < n1; i++)
	{
		for (int j = 0; j < n2; j++)
		{
			in[i][j] = a;
			a++;
		}
	}
	vector <vector<int> > out;
	out = in;
	Test_Proverka(swapWrap(in,angl)==out,"ERROR");
}

void Test_IncorrectMatrix()
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
			a++;
		}
	}
	in[0].resize(2);
	in[2].resize(5);
	vector <vector<int> > out(1,1);
	out[0][0] = -1;
	Test_Proverka(swapWrap(in,angl)==out,"ERROR");
}


void main()
{
	setlocale (LC_CTYPE,"Russian");
	int n = 3;

	vector <vector<int> > s(n,n);

	int successCount = 0;
	int allCount = 0;
	LetsGoTest(Test_90,"correct answer 90",&successCount, &allCount);
	LetsGoTest(Test_180,"correct answer 180",&successCount, &allCount);
	LetsGoTest(Test_270,"correct answer 270",&successCount, &allCount);
	LetsGoTest(Test_360,"correct answer 360",&successCount, &allCount);	
	LetsGoTest(Test_IncorrectAngle,"correct -1 answer",&successCount, &allCount);
	LetsGoTest(Test_NotSquere90,"correct NotSquere answer 90",&successCount, &allCount);
	LetsGoTest(Test_NotSquere180,"correct NotSquere answer 180",&successCount, &allCount);
	LetsGoTest(Test_NotSquere270,"correct NotSquere answer 270",&successCount, &allCount);
	LetsGoTest(Test_NotSquere360,"correct NotSquere answer 360",&successCount, &allCount);		
	LetsGoTest(Test_IncorrectMatrix,"correct IncorrectMatrix",&successCount, &allCount);	

	if(successCount == allCount) 
	{
		cout << "All tests successful" << endl;
	} 
	else 
	{
		cout << "Some tests failed" << endl;
	}

}