#ifndef USERTEST_H
# define USERTEST_H

typedef struct
{
	const char *name;
	int (*func)(void);
} testsuite_t;

int file_testsuite(void);
int time_testsuite(void);

#endif
