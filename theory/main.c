#include "unistd.h"
#include "stdio.h"
#include "sys/time.h"

int	main(void)
{
	struct timeval tv;
	struct timezone tz;

	gettimeofday(&tv, &tz);

	// Imprimir la fecha y hora
    printf("Seconds: %ld\n", tv.tv_sec);
    printf("Microseconds: %d\n", tv.tv_usec);

    // Imprimir información sobre la zona horaria (opcional)
    printf("Timezone: %d minutes west of UTC\n", tz.tz_minuteswest);
    printf("Daylight savings time: %d\n", tz.tz_dsttime);

	usleep(5000000);
	printf("HOLA\n");
	return (0);
}