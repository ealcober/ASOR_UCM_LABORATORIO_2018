#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>



/*
Escribir un programa que, usando la llamada open, cree un fichero con los permisos rw-r--r-x. (645)
*/
int main(int argc, char *argv[])
{
    // argv[0] nombre programa
    // argv[1] nombre fichero a crear
    int f1 = open(argv[1], O_RDWR | O_CREAT | O_EXCL, S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH | S_IXOTH);

    if (f1 == -1)
    {
        perror("error en la creación del fichero: ¿Ya existe?");
        return 1;
    }
    else
    {
        close(f1);
        return 0;

    }


}
