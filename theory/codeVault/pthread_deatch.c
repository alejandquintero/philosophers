#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>

void* thread_function(void* arg) {
    printf("Hilo en ejecución\n");
    printf("%d", *(unsigned int*)arg );
    printf("g\n");
    sleep(*(unsigned int*)arg); // Simula alguna operación que lleva tiempo
    printf("Hilo terminado\n");
    return NULL;
}

int main() {
    pthread_t thread[3];
    int	i;

	i = 0;
	while (i < 3)
	{
		if (i == 0){
			if (pthread_create(&thread[i], NULL, &thread_function, &i) != 0) {
				perror("Error al crear el hilo");
				exit(EXIT_FAILURE);
			}
			// Desprender el hilo
			if (pthread_detach(thread[i]) != 0) {
				perror("Error al desprender el hilo");
				exit(EXIT_FAILURE);
			}
		}
		else{
			pthread_create(&thread[i], NULL, &thread_function, NULL);
		}
		i++;
	}
	i = 0;
	while (i < 2)
	{
		if (i != 0){
			pthread_join(thread[i], NULL);
		}
		i++;
	}


	while (1){

	}


    // // El hilo principal continúa su ejecución
    // printf("Hilo principal continúa ejecutándose\n");
    // sleep(4); // Espera suficiente tiempo para que el hilo termine
    // printf("Hilo principal termina\n");
    
    return 0;
}
