#include <stdio.h>
extern "C" {
	#pragma warning(push)
	#pragma warning(disable:4996)
	#include "vs_patch_tap.h"
	#include "tap.h"
	#ifdef TAP_COMPILE
		#include "vs_patch_tap.c"
		#include "tap.c"
	#endif
	#pragma warning(pop)
}
