#include "get_next_line_bonus.h"
#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>

char	*files[] = {"./get_next_line_bonus.h", "./main.c", "./get_next_line_bonus.c", "./get_next_line_utils_bonus.c"};

int main(int ac, char **av)
{
	int		fd[] = {open(files[0], O_RDONLY), open(files[1], O_RDONLY), 
	open(files[2], O_RDONLY), open(files[3], O_RDONLY)};
	int		exit[4] = {1, 1, 1, 1};
	int		i[4] = {0};
	char	*line;
	int		c;
	int		infinite_loop = 0;

	if (ac == 2 && av[1][0] == '-' && av[1][1] == 'l')
		infinite_loop = 1;
	printf("file descriptors: %d, %d, %d, %d\n", fd[0], fd[1], fd[2], fd[3]);
	while (exit[0] > 0 || exit[1] > 0 || exit[2] > 0 || exit[3] > 0)
	{
		c = rand() % 4;
		if (fd[c] != -1)
		{
			exit[c] = get_next_line(fd[c], &line);
			if (exit[c] == -1)
			{
				printf("\x1b[31m-1 error on %d %d\x1b[37m", c, fd[c]);
				return (1);
			}
			printf("%03d %d fd:%d [%s]\n", ++i[c], exit[c], fd[c], line);
			if (exit[c] == 0)
				fd[c] = -1;
			if (infinite_loop && line)
				free(line);
		}
	}
	if (infinite_loop)
	{
		printf("\x1b[32minfinite loop...\n\x1b[37m");
		while (1) ;
	}
	else
		printf("\x1b[32mdone.\n\x1b[37m");
	return (0);
}
