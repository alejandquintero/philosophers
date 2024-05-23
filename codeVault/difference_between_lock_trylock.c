#include <pthread.h>
#include <stdio.h>
#include <unistd.h>

int	c;
pthread_mutex_t mutex;

/*With lock, threads wait*/
/*void *routine()
{
	pthread_mutex_lock(&mutex);
	printf("Got lock\n");
	sleep(1);
	pthread_mutex_unlock(&mutex);
	return NULL;
}*/

/*With trylock, threads do not wait.*/
void *routine()
{
	if (pthread_mutex_trylock(&mutex) == 0){
		printf("Got lock\n");
		sleep(1);
		pthread_mutex_unlock(&mutex);
	}else{
		printf("Busy\n");
	}
	return NULL;
}

int main(void)
{
	pthread_t threads[4];
	int	total_threads;
	int	i;

	i = 0;
	total_threads = 4;
	pthread_mutex_init(&mutex, NULL);
	while (i < total_threads)
	{
		if (pthread_create(&threads[i], NULL, &routine, NULL) != 0)
			return 1;
		i++;
	}
	i = 0;
	while (i < total_threads)
	{
		if (pthread_join(threads[i], NULL) != 0)
			return 2;
		i++;
	}
	pthread_mutex_destroy(&mutex);
	return (0);
}