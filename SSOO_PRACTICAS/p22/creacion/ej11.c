#include <unistd.h>
#include <stdio.h>
#include <string.h>

#include <sys/types.h>
#include <sys/stat.h>
#include <sys/sysmacros.h>
#include <time.h>


int main(int argc, char *argv[])
{

    struct stat info;
    stat(argv[1], &info);
    int longsym = strlen(argv[1]) + 4;
    int longhard = strlen(argv[1]) + 5;
    printf("long nombre del archivo: %d\n",strlen(argv[1]));
    char nombreSym[longsym];
    char nombreHard[longhard];

    switch(info.st_mode & S_IFMT)
    {
    case S_IFREG:
        printf("Regular File, linking\n");

        sprintf(nombreSym, "%s.sym", argv[1]);
        sprintf(nombreHard, "%s.hard", argv[1]);

        printf("%s\n", nombreHard);
        puts("\n");
        printf("%s\n", nombreSym);
        puts("\n");
        link(argv[1], nombreHard);
        symlink(argv[1], nombreSym);

        break;
    case S_IFDIR:
        printf("this program only link files. This is a Directory\n");
        break;
    case S_IFBLK:
        printf("this program only link files. This is a Block Device\n");
        break;
    case S_IFCHR:
        printf("this program only link files. This is a Character Device\n");
        break;
    case S_IFSOCK:
        printf("this program only link files. This is a Socket\n");
        break;
    case S_IFLNK:
        printf("this program only link files. This is a Symbolic Link\n");
        break;



    }

    return 0;
}

