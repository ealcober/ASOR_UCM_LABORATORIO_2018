/*
Ejercicio 1. Escribir un programa que redirija la salida estándar a un fichero cuya ruta se pasa
como primer argumento. Probar haciendo que el programa escriba varias cadenas en la salida estándar.
0 - entrada
1 - salida
2 - error
*/

#include <stdio.h>
#include <unistd.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>
#include <errno.h>


int main(int argc, char const *argv[])
{
    // argv[1] ruta argumento
    if(argc < 2)
    {
        perror("Falta el argumento 1: el programa redirige la salida estándar al fichero que indique\n");
        return -1;
    }

    int fd = open(argv[1], O_CREAT | O_RDWR, 00777);
    if(fd == -1)
    {
        printf("%i - %s\n", errno, strerror(errno));
        return -1;
    }

    int ret = dup2(fd, 1);
    dup2(fd, 2);
    if(ret == -1)
    {
        perror("error duplicando el descriptor\n");
    }
    else
    {
        printf("Salida estandar dirigida al fichero %s\n", argv[1]);
        printf("Salida de error dirigida al fichero %s\n", argv[1]);
    }

    return 0;
}





