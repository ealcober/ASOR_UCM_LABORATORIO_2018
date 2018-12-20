/*

Ejercicio 1. Crear otra tubería con nombre (ej. tuberia2). Escribir un programa que espere hasta que haya datos listos
para leer en alguna de ellas. El programa debe indicar la tubería desde la que se leyó y mostrar los datos leídos.
consideraciones:
Para optimizar las operaciones de lectura usar un buffer (ej. de 256 bytes).
Usar read() para leer de la tubería y gestionar adecuadamente la longitud de los caracteres leídos.
Normalmente, la apertura de la tubería para lectura se bloqueará hasta que se abra para escritura
    (ej. con echo 1 > tuberia). Para evitarlo, usar la opción O_NONBLOCK en open().
Cuando un escritor termina y cierra la tubería, select() considerará el descriptor siempre listo para lectura
(para detectar el fin de fichero) y no se bloqueará. En este caso, hay que cerrar la tubería y volver a abrirla.


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
    char buffer[256] = "";
    int t1, t2;
    int max = 0;

    t1 = open("../tuberia", O_RDONLY | O_NONBLOCK);
    t2 = open("../tuberia2", O_RDONLY | O_NONBLOCK);

    max = t1;

    if (t2 > t1)
    {
        max = t2;
    }

    while(1)
    {
        int rfd = 0;
        fd_set rfds;
        FD_ZERO(&rfds);
        FD_SET(t1, &rfds);
        FD_SET(t2, &rfds);

        int rc = select(max + 1, &rfds, NULL, NULL, NULL);

        if (rc == 0) // ERROR, TIMEOUT, SIGNAL
        {
            continue;
        }

        if(FD_ISSET(t1, &rfds))
            rfd = t1;
        else if(FD_ISSET(t2, &rfds))
            rfd = t2;
        else
            continue; // NO LLEGARA

        int cr = read(rfd, &buffer, sizeof(buffer));

        if(cr == 0)
        {
            if(FD_ISSET(t1, &rfds)){
                close(t1);
                t1 = open("../tuberia", O_RDONLY | O_NONBLOCK);

            }
            else if(FD_ISSET(t2, &rfds)){
                close(t2);
                t2 = open("../tuberia2", O_RDONLY | O_NONBLOCK);
            }
            else
                continue; // NO LLEGARA

        }

        buffer[cr] = '\0';

        printf("%s", buffer );



    }



    return 0;
}