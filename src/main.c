#include <stdio.h>

#include "usertest.h"

int main()
{
#ifdef STRESS_TEST
	return !stress_test();
#else
	testsuite_t testsuites[] = {
		{"file", file_testsuite},
		{"time", time_testsuite},
	};
	int failed = 0;

	for (size_t i = 0; i < sizeof(testsuites) / sizeof(testsuites[0]); ++i)
	{
		printf("Running test suite `%s` ... ", testsuites[i].name);

		if (testsuites[i].func())
			printf("OK :)\n");
		else
		{
			printf("Failed :(\n");
			failed = 1;
		}
	}
	return failed;
#endif
}
