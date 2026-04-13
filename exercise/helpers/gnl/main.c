#include "hlp.h"
#include <sys/stat.h>
#include <fcntl.h>

int main()
{
	int fd = open("main.c", O_RDONLY);
	t_gnl gnl = get_next_line(fd);
	if (gnl.failed )
			printf("	Failed\n");
	while (gnl.line != NULL)
	{
		if (gnl.failed )
		{
			printf("	Failed\n");
			break;
		}
		printf("%s", gnl.line);
		free(gnl.line);
		gnl = get_next_line(fd);
	}
	close(fd);
}