/*
Ejercicio 5. Escribir un programa que, usando la llamada open, cree un fichero con los 
permisos rw-r--r-x. Comprobar el resultado y las características del fichero con la orden ls.
*/

#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>


int main(){

	umask(0132);
	int file = open("permisos645.txt", O_CREAT | O_RDONLY, 0777); //Este es nuestro caso en relación al enunciado

	if(file == -1){
		printf("No se pudo crear el fichero\n");
		return -1;
	}
	else
		printf("Creado el fichero correctamente\n");

	return 0;
}



