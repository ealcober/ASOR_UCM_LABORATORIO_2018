/*
Ejercicio 2. Escribir un programa que consulte y muestre en pantalla el estado del cerrojo sobre un fichero.
El programa mostrará el estado del cerrojo (bloqueado, desbloqueado). Además:
* Si está desbloqueado, fijará un cerrojo de escritura y escribirá la hora actual.
  Después suspenderá su ejecución durante 30 segundos (función sleep) y a continuación liberará el cerrojo.

* Si el cerrojo está bloqueado terminará el programa.

El programa no deberá modificar el contenido del fichero si no tiene el cerrojo.

struct flock {
               ...
               short l_type;    /* Type of lock: F_RDLCK,
                                   F_WRLCK, F_UNLCK
               short l_whence;  /* How to interpret l_start:
                                   SEEK_SET, SEEK_CUR, SEEK_END
               off_t l_start;   /* Starting offset for lock
               off_t l_len;     /* Number of bytes to lock
               pid_t l_pid;     /* PID of process blocking our lock
                                   (set by F_GETLK and F_OFD_GETLK)
               ...
           };


*/

#include <stdio.h>
#include <fcntl.h>
#include <errno.h>
#include <string.h>
#include <unistd.h>
#include <time.h>
#include <sys/time.h>



int main(int argc, char const *argv[])
{
    // abrimos el archivo
    int op = open(argv[1], O_RDONLY);
    if(op == -1)
    {
        perror("error abriendo\n");
        return -1;
    }

    // tratamos de coger la info actual del cerrojo
    struct flock lock;
    lock.l_type = F_UNLCK;
    lock.l_whence = SEEK_SET;
    lock.l_start = 0;
    lock.l_len = 0;
    int res = fcntl(op, F_GETLK, &lock);
    /*if(res == -1)
    {
        printf("error cogiendo la info del cerrojo\n");
        return -1;
    }*/
    printf("Tipo de cerrojo: ");
    if (lock.l_type == F_RDLCK) // De lectura o compartido
    {
        printf("De lectura o compartido\n");
    }
    else if (lock.l_type == F_WRLCK) // De escritura o exclusivo
    {
        printf("De escritura o exclusivo\n");
    }
    else if (lock.l_type == F_UNLCK)
    {

        /*
        struct timeval {
               long    tv_sec;         /* segundos
               long    tv_usec;        /* microsegundos
        };

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
        printf("Cerrojo desbloqueado\n");


        time_t tim = time(NULL);

        struct tm *tm = localtime(&tim);

        char fecha[22];
        sprintf(fecha, "%d:%d:%d - %d/%d/%d", tm->tm_hour, tm->tm_min, tm->tm_sec, tm->tm_mday, tm->tm_mon, tm->tm_year);

        //procedo a bloquear
        struct flock myLock;
        myLock.l_type = F_WRLCK;
        myLock.l_whence = SEEK_SET;
        myLock.l_start = 0;
        myLock.l_len = 22;
        myLock.l_pid = getpid();
        res = fcntl(op, F_SETLK, &myLock);

        if (res == -1)
        {
            perror("error bloqueando el cerrojo\n");
            return -1;
        }

        res = fcntl(op, F_GETLK, &lock);
        if (lock.l_pid == getpid()) // tenemos el cerrojo
        {
            write(op, fecha, 22);
            sleep(30);

            myLock.l_type = F_UNLCK;
            myLock.l_whence = SEEK_SET;
            myLock.l_start = 0;
            myLock.l_len = 22;
            fcntl(op, F_SETLK, &myLock);

        }









    }


    return 0;
}
