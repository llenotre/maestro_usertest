#include <fcntl.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>

#include <stdio.h>
#include <errno.h>

int test_open0(void)
{
	int fd = open("test", O_CREAT | O_RDWR, S_IRWXU);
	if (fd < 0)
		return 0;

	const char *str = "Hello world!\n";
	size_t len = strlen(str);
	ssize_t l = write(fd, str, len);
	if (l != (ssize_t) len)
	{
		close(fd);
		return 0;
	}

	lseek(fd, 0, SEEK_SET);

	char buff[128];
	l = read(fd, buff, len);
	if (l != (ssize_t) len)
	{
		printf("bleh %zd %zd %i", len, l, fd);
		close(fd);
		return 0;
	}
	if (memcmp(str, buff, len) != 0)
	{
		close(fd);
		return 0;
	}

	return 1;
}

int file_testsuite(void)
{
	int result = 1;

	result = result && test_open0();
	return result;
}
