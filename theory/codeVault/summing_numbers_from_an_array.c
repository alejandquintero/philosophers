#include <pthread.h>
#include <stdlib.h>
#include <stdio.h>



int	primes[10] = {2, 3, 5, 7, 11, 13, 17, 19, 23, 29};

void *routine(void *ar)
{
	int	i;
	int	index;
	int	sum;

	i = 0;
	sum = 0;
	index = *(int *)ar;
	while (i < 5)
	{
		sum += primes[i + index];
		i++;
	}
	printf("Local sum: %d\n", sum);
	*(int *)ar = sum;
	return (ar);
}

int	main(void)
{
	pthread_t th[2];
	int	i;
	int	global_sum;

	i = 0;
	global_sum = 0;
	while (i < 2)
	{
		int *start = malloc(sizeof(int));
		*start = 5 * i;
		if (pthread_create(&th[i], NULL, &routine, start) != 0)
			perror("Error creating thread");
		i++;
	}
	i = 0;
	while (i < 2)
	{
		int	*res;
		if (pthread_join(th[i], (void **)&res) != 0)
			perror("Error joining thread");
		global_sum += *res;
		free(res);
		i++;
	}
	printf("The sum is: %d\n", global_sum);
	return (0);	
}
