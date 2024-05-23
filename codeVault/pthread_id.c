#include <pthread.h>
#include <stdio.h>
 #include <sys/syscall.h>
#include <unistd.h>

void *routine(void *ar)
{
	pthread_t	td;
	uint64_t thread_id;

	td = pthread_self();
	printf("%ul\n", td);
	pthread_threadid_np(NULL, &thread_id);
    printf("Thread ID: %llu\n", thread_id);

	return (NULL);
}

int	main(void)
{
	pthread_t	td[2];
	int	i;

	i = 0;
	while (i < 2)
	{
		pthread_create(&td[i], NULL, &routine, NULL);
		printf("%ul\n", td[i]);
		i++;
	}
	i = 0;
	while (i < 2)
	{
		pthread_join(td[i], NULL);
		i++;
	}
	return (0);
}
