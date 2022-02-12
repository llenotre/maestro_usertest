#include <sys/types.h>
#include <time.h>

int test_time0(void)
{
	size_t prev = time(NULL);

	for (size_t i = 0; i < 10000000; ++i)
	{
		size_t t = time(NULL);
		if (t < prev)
			return 0;
		prev = t;
	}
	return 1;
}

int time_testsuite(void)
{
	int result = 1;

	result = result && test_time0();
	return result;
}
