#include <stdio.h>
extern "C" float __cdecl printpi(void);

void main()
{	

	
	printf("%f\n", printpi());
			
}