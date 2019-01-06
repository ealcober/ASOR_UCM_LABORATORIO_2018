#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>


int main()
{

    mode_t prevMask = umask(0027);
    int file = open("permisos750.txt", O_CREAT | O_RDONLY, 0777); //Este es nuestro caso en relación al enunciado

    if(file == -1)
    {
        printf("No se pudo crear el fichero\n");
        return -1;
    }
    else
        printf("Creado el fichero correctamente\n");
    umask(prevMask);
    return 0;
}



