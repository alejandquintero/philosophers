#include <pthread.h>
#include <stdio.h>

int	c;
pthread_mutex_t mutex;

void *routine()
{
	int	i;

	i = 0;
	while (i < 10000000)
	{
		pthread_mutex_lock(&mutex);
		c++;
		pthread_mutex_unlock(&mutex);
		i++;
	}
	return NULL;
}

int	main(void)
{
	pthread_t	td1;
	pthread_t	td2;

	pthread_mutex_init(&mutex, NULL);
	
	pthread_create(&td1, NULL, &routine, NULL);
	pthread_create(&td2, NULL, &routine, NULL);

	pthread_join(td1, NULL);
	pthread_join(td2, NULL);
	
	pthread_mutex_destroy(&mutex);
	printf("C: %d\n", c);
	return (0);
}