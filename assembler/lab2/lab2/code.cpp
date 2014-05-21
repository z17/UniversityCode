#include <iostream>
#include <iomanip>


extern "C" void __cdecl fdcttest(float *a, float *b,  unsigned int n);
extern "C" void __cdecl idcttest(float *a, float *b,  unsigned int n);

extern "C" void __cdecl fdct(float*a, float*b,  unsigned int n);
extern "C" void __cdecl idct(float*a, float*b,  unsigned int n);

extern "C" void __cdecl fdcttest_s(float*a, float*b,  unsigned int n);
extern "C" void __cdecl idcttest_s(float*a, float*b,  unsigned int n);


using namespace std;

int main()
{
	const unsigned int n = 2;
	float in[n*8*8] = {
		-16342, 2084, -10049, 10117, 2786, -659, -4905, 12975,
		 10579, 8081, -10678, 11762, 6898, 444, -6422, -15892,
		-13388, -4441, -11556, -10947, 16008, -1779, -12481, -16230,
		-16091, -4001, 1038, 2333, 3335, 3512, -10936, 5343,
		-1612, -4845, -14514, 3529, 9284, 9916, 652, -6489,
		 12320, 7428, 14939, 13950, 1290, -11719, -1242, -8672,
		 11870, -9515, 9164, 11261, 16279, 16374, 3654, -3524,
		-7660, -6642, 11146, -15605, -4067, -13348, 5807, -14541,

		
		-16342, 2084, -10049, 10117, 2786, -659, -4905, 12975,
		 10579, 8081, -10678, 11762, 6898, 444, -6422, -15892,
		-13388, -4441, -11556, -10947, 16008, -1779, -12481, -16230,
		-16091, -4001, 1038, 2333, 3335, 3512, -10936, 5343,
		-1612, -4845, -14514, 3529, 9284, 9916, 652, -6489,
		 12320, 7428, 14939, 13950, 1290, -11719, -1242, -8672,
		 11870, -9515, 9164, 11261, 16279, 16374, 3654, -3524,
		-7660, -6642, 11146, -15605, -4067, -13348, 5807, -14541,
	};

	float out2[n*8*8];
	float out3[n*8*8];
	float outi2[n*8*8];
	float outi3[n*8*8];



//	fdcttest_s(*in, *out2, n);
	fdct(in, out3, n);
	
	idct(out3, outi2, n);
	idcttest_s(out3, outi3, n);

	int q = 0;
	for (int k = 0; k < n; k++)
	{
		for (int i = 0; i < 8; i++)
		{
			for (int j = 0; j < 8; j++)
			{
				cout << setprecision(5) << outi2[q] << "\t\t";
				q++;
			}
			cout << endl;
		}
		cout << endl;
	}
	cout << endl;
	q = 0;
	for (int k = 0; k < n; k++)
	{
		for (int i = 0; i < 8; i++)
		{
			for (int j = 0; j < 8; j++)
			{
				cout << setprecision(5) << outi3[q] << "\t\t";
				q++;
			}
			cout << endl;
		}
		cout << endl;
	}


	system("pause");
	return 0;

}
