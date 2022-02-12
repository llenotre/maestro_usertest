#ifndef USERTEST_H
# define USERTEST_H

int stress_test(void);

typedef struct
{
	const char *name;
	int (*func)(void);
} testsuite_t;

int file_testsuite(void);
int time_testsuite(void);
int memory_testsuite(void);

#endif
