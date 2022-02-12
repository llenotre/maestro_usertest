#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int test_malloc0(void)
{
	for (size_t i = 0; i < 1024 * 1024; ++i)
	{
		void *ptr;
		if (!(ptr = malloc(i)))
		{
			printf("Allocation of size %zu failed\n", i);
			return 0;
		}

		memset(ptr, 42, i);
		free(ptr);
	}

	return 1;
}

int memory_testsuite(void)
{
	int result = 1;

	result = result && test_malloc0();
	return result;
}
