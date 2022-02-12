#include <errno.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <unistd.h>

int stress_test(void)
{
	mkdir("./test", 0777);

	while (1)
	{
		printf("Starting new cycle :)\n");

		int pid = fork();
		if (pid < 0)
		{
			printf("Cannot fork :(\n");
			return 0;
		}

		if (pid == 0)
		{
			pid = getpid();

			for (size_t i = 0; i < 64; ++i)
				if (fork() == 0)
					break;

			if (pid == getpid())
			{
				int failed = 0;

				for (size_t i = 0; i < 64; ++i)
				{
					int status;
					waitpid(pid, &status, 0);

					if (WEXITSTATUS(status) != 0)
						failed = 1;
				}

				if (failed)
					printf("Cycle failed :(\n");
				exit(failed);
			}

			pid = getpid();
			char name[1024];
			sprintf(name, "./test/test%d", pid);

			printf("Open %s\n", name);
			int fd = open(name, O_CREAT | O_RDWR, S_IRWXU);
			if (fd < 0)
			{
				printf("Cannot open :( %d\n", errno);
				exit(1);
			}

			size_t total = 0;
			ssize_t len;
			while ((len = write(fd, name, sizeof(name))) > 0)
				total += len;
			if (len < 0)
				printf("Write failed: %d\n", errno);

			struct stat s;
			if (stat(name, &s) < 0)
			{
				printf("Failed to stat :( %d\n", errno);
				exit(1);
			}
			if ((size_t) s.st_size != total)
			{
				printf("Wrong size :(\n");
				exit(1);
			}

			printf("Remove %s\n", name);
			if (unlink(name) < 0)
			{
				printf("Failed to remove :( %d\n", errno);
				exit(1);
			}

			exit(0);
		}
		else
			waitpid(pid, NULL, 0);
	}
}
