/*
Ejercicio 4. Repetir el ejercicio anterior pero en este caso para la configuración del sistema de ficheros, 
con pathconf(3). Por ejemplo, que muestre:
+el número máximo de enlaces
+el tamaño máximo de una ruta
+el de un nombre de fichero.

*/

#include <stdio.h>
#include <unistd.h>
#include <sys/stat.h>
#include <fcntl.h>


int main(int argc, char const *argv[])
{
	// int fdesc = open("4.c", O_RDONLY); para prueba con fpathconf
	printf("el número máximo de enlaces: %li.\n",pathconf("4.c", _PC_LINK_MAX));
	printf("el tamaño máximo de una ruta: %li.\n",pathconf("4.c", _PC_PATH_MAX));
	printf("el tamaño máximo de un nombre de fichero: %li.\n",pathconf("4.c", _PC_NAME_MAX));
	return 0;
}