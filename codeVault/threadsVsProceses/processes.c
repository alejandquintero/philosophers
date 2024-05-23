#include <unistd.h>
#include <sys/wait.h>
#include <stdio.h>

int	main(void)
{
	int	pd;
	int	x;

	x = 2;
	pd = fork();
	if (pd != 0){
		x++;
	}
	printf("Value of x: %d\n", x);
	if (pd == 0){
		wait(NULL);
	}
	return (0);
}