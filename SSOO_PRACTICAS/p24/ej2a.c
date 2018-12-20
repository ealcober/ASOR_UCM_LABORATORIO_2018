/*
Ejercicio 2. Escribir un programa que abra la tubería con el nombre anterior ($HOME/tuberia) en modo sólo escritura,
 y escriba en ella el primer argumento del programa. En otro terminal, leer de la tubería usando un comando adecuado.
*/

#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>





int main(int argc, char const *argv[])
{
    char home[256];
    int t1;

    snprintf(home, 255, "%s/tuberia", getenv("HOME"));
    
    printf("$HOME = %s\n", home);

    if(t1 = open(home, O_WRONLY) != -1)
    {
    	write(t1, argv[1], sizeof(argv[1]) + 1);
    } else return 1;


    /* code */
    return 0;
}