#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>

int	primes[10] = {2, 3, 5, 7, 11, 13, 17, 19, 23, 29};

void *routine(void *arg)
{
	int	index = *(int *)arg;
	printf("%d\n", primes[index]);
	free(arg);
	return NULL;
}

int	main(void)
{
	pthread_t th[10];
	int	i;

	i = 0;
	while (i < 10)
	{
		int	*a = malloc(sizeof(int));
		*a = i;
		if (pthread_create(&th[i], NULL, &routine, a) != 0)
			perror("Error creating thread\n");
		i++;
	}
	i = 0;
	while (i < 10)
	{
		if (pthread_join(th[i], NULL) != 0)
			perror("Error joining thread\n");
		i++;
	}
	return (0);
}
