#include <stdio.h>
#include <unistd.h>

int main(int argc, char const *argv[])
{
	printf("Longitud máxima de argumentos: %li.\n",sysconf(_SC_ARG_MAX));
	printf("Número máximo de hijos: %li.\n",sysconf(_SC_CHILD_MAX));
	printf("Número máximo de ficheros: %li.\n",sysconf(_SC_OPEN_MAX));
	return 0;
}