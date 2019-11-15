#include "get_next_line.h"
#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>

int main(void)
{
	int fd[] = {open("./get_next_line.h", O_RDONLY), open("./main.c", O_RDONLY), open("./get_next_line.c", O_RDONLY)};
	int exit[3] = {1, 1, 1};
	int i[3] = {0};
	char *line;
	int c;

	printf("%d:%d:%d", fd[0], fd[1], fd[2]);
	while (exit[0] > 0 || exit[1] > 0 || exit[2] > 0)
	{
		c = rand() % 3;
		exit[c] = get_next_line(fd[c], &line);
		if (exit[c] == -1)
		{
			printf("\x1b[31m-1 error on %d %d\x1b[37m", c, fd[c]);
			return (1);
		}
		printf("%03d fd:%d [%s]\n", ++i[c], c, line);
	}
	printf("\x1b[32mdone.\n\x1b[37m");
	return (0);
}
