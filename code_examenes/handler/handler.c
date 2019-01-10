/*
Problema 4 ​ (1.25 ptos). ​ Escribir un programa que cree un proceso hijo para ejecutar una
tarea atendiendo a la siguiente especificación:
1. El proceso padre simplemente creará el hijo y terminará su ejecución. Además imprimirá el
identificador del hijo según se muestra en el ejemplo.
2. El proceso hijo programará el envío de la señal SIGALRM después de un número de segundos
especificado por el primer argumento.
3. Suspenderá su ejecución hasta que expire la alarma. El manejador de la señal SIGALRM
imprimirá el mensaje “Ejecutando tarea programada”. ​ (0.75 puntos)
4. Finalmente ejecutará el programa especificado como segundo argumento, de forma que la
salida estándar del programa se guarde en el fichero “/tmp/examen.out”. Este fichero debe
crearse con permisos de lectura y escritura para cualquier usuario del sistema. ( ​ 0.5 puntos)
Nota: ​ Para traducir la cadena del primer argumento a un entero usar atoi(3).
Nota: ​ Resolver el problema en dos partes: (i) crear un proceso hijo que suspenda su ejecución hasta la
recepción de la señal SIGALRM y (ii) la ejecución de un proceso que redirija su salida estándar al fichero
“/tmp/examen.out”.
*/

#include <signal.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>


static void handler(int signum)
{
    printf("Efectuando tarea programada\n");
}

int main(int argc, char const *argv[])
{
    int secs = atoi(argv[1]);

    pid_t pid;

    pid = fork();

    if(pid == 0) // hijo
    {
        printf("Hijo creado Pid = %d\n", getpid());
        struct sigaction act;
        act.sa_handler = handler;
        act.sa_flags = 0;
        sigaction(SIGALRM, &act, NULL);

        alarm(secs);

        sigset_t set;
        sigemptyset(&set);
        sigsuspend(&set);
        //sigaddset(&set, SIGALRM);

        printf("hijo suspendido hasta recibir la señal ALARM\n");
        
        sigsuspend(&set);




    }
    else
    {
        exit(0);   // padre
    }
    exit(0);


}

