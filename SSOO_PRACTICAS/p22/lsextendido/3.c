/*
Proyecto: Comando ls extendido

Escribir un programa que cumpla las siguientes especificaciones:
* El programa tiene un único argumento que es la ruta a un directorio. El programa debe comprobar la corrección
del argumento.
* El programa recorrerá las entradas del directorio de forma que:
   * Si es un fichero normal, escribirá el nombre.
   * Si es un directorio, escribirá el nombre seguido del carácter ‘/’
   * Si es un enlace simbólico, escribirá el nombre seguido de ‘-><fichero al que apunta>’. Usar la función
   readlink(2) y dimensionar adecuadamente el buffer de la función.
   * Si el fichero es ejecutable, escribirá el nombre seguido del carácter ‘*’
* Al final de la lista el programa escribirá el tamaño total que ocupan los ficheros (no directorios) en kilobytes.
*/

#include <stdio.h>
#include <sys/types.h>
#include <dirent.h>
#include <errno.h>
#include <sys/stat.h>
#include <unistd.h>

/*
DIR *opendir(const char *nombre);
*/

int main(int argc, char const *argv[])
{
    struct dirent *current;
    DIR *a = opendir(argv[1]);
    struct stat buf;
    int it;

    if (a == NULL)
    {
        switch(errno)
        {
        case EACCES:
            perror("Permission denied.");
            break;

        case EBADF:
            perror("fd is not a valid file descriptor opened for reading.");
            break;

        case EMFILE:
            perror("The  per - process  limit on the number of open file descriptors has been reached.");
            break;

        case ENFILE:
            perror("The system - wide limit on the  total  number  of  open  files  has  been reached.");
            break;

        case ENOENT:
            perror("Directory does not exist, or name is an empty string.");
            break;

        case ENOMEM:
            perror("Insufficient memory to complete the operation.");
            break;

        case ENOTDIR:
            perror("name is not a directory.");
            break;
        default:
            break;

        }
        return -1;
    }

    while( (current = readdir(a)) )
    {
    	char path[50];
    	sprintf(path, "%s/%s\0\n",argv[1],current->d_name);
        printf("%s: ",  current->d_name);
        it = stat(path, &buf);

        if(S_ISLNK(buf.st_mode) )printf("es un enlace simbólico\n");

        else if(S_ISREG(buf.st_mode) )printf("un fichero regular\n");

        else if(S_ISDIR(buf.st_mode) )printf("un directorio\n");

        else if(S_ISCHR(buf.st_mode) )printf("un dispositivo de caracteres\n");

        else if(S_ISBLK(buf.st_mode) )printf("un dispositivo de bloques\n");

        else if(S_ISFIFO(buf.st_mode))printf("una tubería nombrada (fifo)\n");

        else if(S_ISLNK(buf.st_mode) )printf("un enlace simbólico?\n");

        else if(S_ISSOCK(buf.st_mode))printf("un conector (socket)?\n");


    }




    return 0;
}