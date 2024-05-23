#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>

void	*sum()
{
	int	nbr = 10;
	int	*res;

	res = malloc(sizeof(int));
	*res =  nbr;
	return (void *)res;
}

int	main(void)
{
	pthread_t th[4];
	int	i;
	int	*res;

	i =  0;
	while (i < 4)
	{
		if (pthread_create(&th[i], NULL, &sum, NULL) != 0)
			return 1;
		i++;
	}
	i =  0;
	while (i < 4)
	{
		if (pthread_join(th[i], (void **) &res) != 0)
			return 1;
		printf("res(%d): %d\n", i, *res);
		free(res);
		i++;
	}
	return (0);
}