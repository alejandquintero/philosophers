#include <pthread.h>
#include <stdio.h>

void *computation(void *add)
{
	long	i;
	long 	sum;
	long 	*add_num;

	i = 0;
	sum = 0;
	add_num = (long *)add;
	while (i < 1000000000)
	{
		sum += *add_num;
		i++;
	}
	return NULL;
}

int main(void)
{
	pthread_t thread1;
	pthread_t thread2;

	long value1 = 1;
	long value2 = 2;

	printf("Antes\n");
	

	pthread_create(&thread1, NULL, &computation, &value1);
	pthread_create(&thread2, NULL, &computation, &value2);

	pthread_join(thread1, NULL);
	pthread_join(thread2, NULL);

	printf("Despues\n");
	
	// computation(&value1);
	// computation(&value2);

	return (0);
}
