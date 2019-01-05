#include <stdio.h>
#include <unistd.h>

int main(int argc, char const *argv[])
{
	// ejemplo para ver como funciona el paso de parámetros
	printf("numero argumentos: %d\n",argc-1);
	printf("Argumento 1: %s\n",argv[1]);
	printf("Argumento 2: %s\n",argv[2]);
	// sol al problema
	printf("Longitud máxima de argumentos: %li.\n",sysconf(_SC_ARG_MAX));
	printf("Número máximo de hijos: %li.\n",sysconf(_SC_CHILD_MAX));
	printf("Número máximo de ficheros: %li.\n",sysconf(_SC_OPEN_MAX));
	return 0;
}