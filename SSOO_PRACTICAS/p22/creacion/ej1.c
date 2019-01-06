/*
Ejercicio 1. Escribir un programa que redirija la salida estándar a un fichero cuya ruta se pasa como primer argumento.
Probar haciendo que el programa escriba varias cadenas en la salida estándar.

Type 	 Symbol
standard input 	0<
standard output 1>
standard error 	2>

*/


#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>


int main(int argc, char *argv[])
{

    //	El programa tiene 4 argumentos
    //	el argumento 0 es ./ej1
    //	el argumento 1 es palomitas
    //	el argumento 2 es de
    //	el argumento 3 es maiz

    int f1 = 0;
    // comprobar nº de argumentos correcto


    if (argc != 2)
    {
        perror("El primer argumento ha de ser la ruta del fichero al que quiere redirigir la salida estándar\n");
        return 1;
    }
    // comprobar si archivo existe
    if( access( argv[1], F_OK ) != -1 )
    {
        char *respuesta = "x";
        while(respuesta != "s" || respuesta != "c")
        {
            printf("El archivo ya existe, desea (s)obreescribirlo o (c)ontinuar al final? (s/c)\n");
            gets(&respuesta);
            if(respuesta = "s")
            {
                if(unlink(argv[1]) != 0)
                {
                    perror("error borrando el archivo para sobreescribirlo\n");
                    return -1;
                }
                else
                {
                    int f1 = creat(argv[1], S_IRWXU | S_IRWXG | S_IRWXO);
                    dup2(1, f1);
                    printf("salida estándar 1 redirigida al fichero\n");
                    printf("salida estándar 1 redirigida al fichero\n");
                    printf("salida estándar 1 redirigida al fichero\n");
                    printf("salida estándar 1 redirigida al fichero\n");
                    close(f1);
                    return 0;

                }

            }
            else if(respuesta = "c")
            {

                f1 = open(argv[1], O_CREAT, S_IRWXU | S_IRWXG | S_IRWXO);
                dup2(1, f1);
                lseek(f1, 0, SEEK_END);
                printf("salida estándar 1 redirigida al fichero\n");
                printf("salida estándar 1 redirigida al fichero\n");
                printf("salida estándar 1 redirigida al fichero\n");
                printf("salida estándar 1 redirigida al fichero\n");

            }


        }
        close(f1);
        return 0;

    }
    else
    {
        // file doesn't exist
        int f1 = creat(argv[1], S_IRWXU | S_IRWXG | S_IRWXO);
        dup2(1, f1);
        printf("salida estándar 1 redirigida al fichero\n");
        printf("salida estándar 1 redirigida al fichero\n");
        printf("salida estándar 1 redirigida al fichero\n");
        printf("salida estándar 1 redirigida al fichero\n");
        close(f1);
        return 0;

    }

    close(f1);
    return 0;

}
