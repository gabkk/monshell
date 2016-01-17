#include <unistd.h>
#include <stdio.h>

int		main(int ac, char **av)
{
	pid_t	father;

	father = fork();
	if (father > 0)
	{
		printf("father");
	}
	if (father == 0)
	{

		execve("/bin/ls", av,NULL);
	}
}
