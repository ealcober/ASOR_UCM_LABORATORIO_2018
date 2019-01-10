#include <dirent.h>
#include <sys/types.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/stat.h>


#define MAX_PATH 50

int main(int argc, char const *argv[])
{
    struct dirent *current;
    DIR *arg;
    struct stat buf;

    char path[MAX_PATH];
    arg = opendir(argv[1]);
    printf("contenido del directorio %s:\n", argv[1]);
    int i = 1;
    while((current = readdir(arg)) != NULL)
    {

        printf("%d. %s\t\t - tipo: ", i, current->d_name);
        sprintf(path, "%s/%s\0", argv[1], current->d_name);

        stat(path,&buf);

        switch(current->d_type)
        {
        case(DT_BLK):
            printf("block device.\t\t");
            break;

        case(DT_CHR):
            printf("character device.\t\t");
            break;

        case(DT_DIR):
            printf("directory.\t\t");
            break;

        case(DT_FIFO):
            printf("named pipe (FIFO).\t\t");
            break;

        case(DT_LNK):
            printf("symbolic link.\t\t");
            break;

        case(DT_REG):
            printf("regular file.\t\t");
            break;

        case(DT_SOCK):
            printf("UNIX domain socket.\t\t");
            break;

        default:
            printf("type could not be determined.\t\t");
            break;
        }

        printf("UID: %d\tINODO: %d\tSIZE: %d B\n", buf.st_uid, buf.st_ino, buf.st_size);



        i++;

    }
    exit(0);
}


