/*
Ejercicio 4 (1,5 puntos). Cree dos tuberías con nombre (tuberia1 y tuberia2) y escriba un
programa que espere hasta que haya datos listos para leer en alguna de ellas. El programa mostrará
el nombre de la tubería desde la que se leyó y los datos leídos. El programa detectará cuándo se
cierra el extremo de escritura de una tubería (read() devuelve 0) para cerrarla y volver a abrirla.
*/

#include <sys/types.h>
#include <sys/stat.h>
#include <sys/select.h>
#include <sys/time.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdio.h>

#define MAX_BUF 20




int main(int argc, char const *argv[])
{
    int sel;
    int p1, p2;
    fd_set readset;
    mkfifo("tuberia1", 0777);
    mkfifo("tuberia2", 0777);
    char buf[MAX_BUF];

    p1 = open("tuberia1", O_RDONLY | O_NONBLOCK);
    p2 = open("tuberia2", O_RDONLY | O_NONBLOCK);

    int max = p2;
    if(p1 > p2)
        max = p1;

    while(1)
    {
        FD_ZERO(&readset);
        FD_SET(p1, &readset);
        FD_SET(p2, &readset);

        sel = select(max+1, &readset, NULL, NULL, NULL);


        int readfrom = 0;
        printf("Datos nuevos.\n");

        if (FD_ISSET(p1, &readset))
        {
            readfrom = 1;
            printf("He leido de la tubería 1");
        }
        else if (FD_ISSET(p2, &readset))
        {
            readfrom = 2;
            printf("He leido de la tubería 2");
        }

        int nbytes = read(buf, MAX_BUF, 0);
        buf[nbytes] = '\0';
        printf("%s\n", buf );



        if(readfrom == 1)
        {
            close(p1);
            p1 = open("tuberia1", O_RDONLY | O_NONBLOCK);

        }
        else if (readfrom == 2)
        {
            close(p2);
            p2 = open("tuberia2", O_RDONLY | O_NONBLOCK);
        }


    }



    return 0;
}