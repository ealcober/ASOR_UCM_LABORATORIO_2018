#include <time.h>
#include <stdio.h>
#include <errno.h>
//       struct tm *localtime(const time_t *timep);
/*
Eercicio 4. Escribir un programa que muestre el año usando la función localtime(2).
struct tm {
                      int     tm_sec;         /* segundos
                      int     tm_min;         /* minutos
                      int     tm_hour;        /* horas
                      int     tm_mday;        /* día del mes
                      int     tm_mon;         /* mes
                      int     tm_year;        /* año
                      int     tm_wday;        /* día de la semana
                      int     tm_yday;        /* día del año
                      int     tm_isdst;       /* cambio horario verano/invierno
              };

*/

int main()
{
    time_t timep = time(NULL);
    struct tm *t = localtime(&timep);
    printf("Año: %d\n", t->tm_year + 1900 );
    return 0;
}
