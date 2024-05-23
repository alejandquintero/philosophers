#include <pthread.h>
#include <stdio.h>

int	x = 2;

void	*routine2()
{
	printf("Value of x %d\n", x);
	return NULL;
}

void	*routine()
{
	x += 10;
	printf("Value of x %d\n", x);
	return NULL;
}


int main(void)
{
	int	x;
	pthread_t	td1;
	pthread_t	td2;

	pthread_create(&td1, NULL, &routine, &x);	
	pthread_create(&td2, NULL, &routine2, NULL);

	pthread_join(td1, NULL);	
	pthread_join(td2, NULL);	
}