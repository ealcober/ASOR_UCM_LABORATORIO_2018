/*
size_t strftime(char *s, size_t max, const char *format,
                const struct tm *tm);

Ejercicio 5. Modificar el programa anterior para que imprima
la hora de forma legible, como "lunes, 29 de octubre de 2018,
10:34", usando la función strftime(3).


struct tm *localtime(const time_t *timep);

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

#include <time.h>
#include <stdio.h>
#include <errno.h>
#include <string.h>
#include <locale.h>




int main()
{
	setlocale(LC_ALL, "");
    char s[35];
    time_t timep = time(NULL);
    struct tm *t = localtime(&timep);
    size_t bytes = strftime(s, 35, "%A, %d de %B del %Y", t);

    printf("Fecha: %s\n", s);


    return 0;
}

