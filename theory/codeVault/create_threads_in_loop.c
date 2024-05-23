#include <pthread.h>
#include <stdio.h>

int	c;
pthread_mutex_t mutex;

void *routine()
{
	int	i;

	i = 0;
	while (i < 1000000)
	{
		pthread_mutex_lock(&mutex);
		c++;
		pthread_mutex_unlock(&mutex);
		i++;
	}
	return NULL;
}

int main(void)
{
	pthread_t threads[8];
	int	total_threads;
	int	i;

	i = 0;
	total_threads = 8;
	pthread_mutex_init(&mutex, NULL);
	while (i < total_threads)
	{
		if (pthread_create(&threads[i], NULL, &routine, NULL) != 0)
			return 1;
		printf("Thread %d has started\n", i);
		i++;
	}
	i = 0;
	while (i < total_threads)
	{
		if (pthread_join(threads[i], NULL) != 0)
			return 2;
		printf("Thread %d has finished execution\n", i);
		i++;
	}
	pthread_mutex_destroy(&mutex);
	printf("Value of c: %d\n", c);
	return (0);
}