/*Ejercicio 3. Escribir un programa que bloquee las señales SIGINT y SIGTSTP.
Después de bloquearlas el programa debe suspender su ejecución con la llamada sleep() un número de segundos que se obtendrán
de la variable de entorno SLEEP_SECS. Después de despertar de la llamada sleep(), el proceso debe informar de si se recibió
la señal SIGINT y/o SIGTSTP. En este último caso, debe desbloquearla con lo que el proceso se detendrá y podrá ser reanudado
en la shell (imprimir una cadena antes de finalizar el programa para comprobar este comportamiento).*/

// FALTA COMPROBAR POR QUÉ SOLO CUENTA 1 SEÑAL DE CADA UNA
#include <signal.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

volatile int contint = 0;
volatile int conttstp = 0;

void handlerSIGINT(int a)
{
    contint++;

}



void handlerSIGTSTP(int a)
{
    conttstp++;
}

int main(int argc, char const *argv[])
{
    struct sigaction varINT;
    struct sigaction varTSTP;
    varTSTP.sa_sigaction = &handlerSIGTSTP;
    varTSTP.sa_flags = SA_RESTART;
    varINT.sa_sigaction = &handlerSIGINT;
    varTSTP.sa_flags = SA_RESTART;
    sigaction(SIGTSTP, &varTSTP, NULL);
    sigaction(SIGINT, &varINT, NULL);

    sigset_t setBloqueadas;
    sigset_t setPendientes;
    sigemptyset(&setBloqueadas);
    sigemptyset(&setPendientes);
    sigaddset(&setBloqueadas, SIGINT);
    sigaddset(&setBloqueadas, SIGTSTP);

    if (sigprocmask(SIG_BLOCK, &setBloqueadas, NULL) == -1)
        return -1;
    else
    {
        char *p;
        if(p = getenv("SLEEP_SECS=20") == NULL)
            if(setenv("SLEEP_SECS", "20", 1) != -1)
            {
                p = getenv("SLEEP_SECS");
                int numsecs = atoi(p);
                sleep(numsecs);
                sigpending(&setPendientes);
                if (sigismember(&setPendientes, SIGTSTP))
                {
                    printf("me han mandado TSTP\n");
                    sigprocmask(SIG_UNBLOCK, &setBloqueadas, NULL);
                    printf("después de la señal\n");
                    //sigdelset(&set, SIGTSTP);
                }
                printf("se supone que me desbloqueo aquí\n");
            }





    }
    printf("He recibido %d señales SIGTSTP\n",conttstp);
    printf("He recibido %d señales SIGINT\n",contint);

    return 0;


}