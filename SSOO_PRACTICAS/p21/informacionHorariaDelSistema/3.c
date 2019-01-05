#include <sys/time.h>
#include <stdio.h>
//        int gettimeofday(struct timeval *restrict tp, void *restrict tzp);
/*
Ejercicio 3. Escribir un programa que mida, en microsegundos usando la función gettimeofday(2),
lo que tarda un bucle que incrementa una variable un millón de veces.
*/

int main()
{

    struct timeval *t;
    int i = 0;
    gettimeofday(t, NULL);
    long inicio = t->tv_usec;
    printf("inicio:%li\n", inicio);
    // medicion inicial
    for(i = 0; i < 10000000; i++);
    // medición final
    gettimeofday(t, NULL);
    long final = t->tv_usec;
    printf("final:%li\n", final);

    long res = final - inicio;
    printf("%li microsegundos\n", res);
    return 0;


}

