#include <unistd.h>
#include <stdio.h>
#include <string.h>

#include <sys/types.h>
#include <sys/stat.h>
#include <sys/sysmacros.h>
#include <time.h>


int main(int argc, char* argv[]){

	struct stat info;
	stat(argv[1], &info);
	int longsym = strlen(argv[1])+4;
    int longhard = strlen(argv[1])+5;
	char nombreSym[longsym];
    char nombreHard[longhard];

    nombreSym[0]='\0';
    nombreHard[0]='\0';

    //sprintf(nombreSym, "%s.sym", argv[1]);
    // equivale a strcat(nombreSym, argv[1]);
    //		      strcat(nombreSym, ".sym");
    //sprintf(nombreHard, "%s.hard", argv[1]);
    // equivale a strcat(nombreHard, argv[1]);
    //            strcat(nombreHard, ".hard");
	switch(info.st_mode & S_IFMT){
        case S_IFREG:
            printf("Regular File, linking\n");
            
            sprintf(nombreSym, "%s.sym", argv[1]);
            sprintf(nombreHard, "%s.hard", argv[1]);
            
            printf("%s\n",nombreHard);puts("\n");
            printf("%s\n",nombreSym);puts("\n");
            break;
        case S_IFDIR:
            printf("Directory\n");
            break;
        case S_IFBLK:
            printf("Block Device\n");
            break;
        case S_IFCHR:
            printf("Character Device\n");
            break;
        case S_IFSOCK:
            printf("Socket\n");
            break;
        case S_IFLNK:
            printf("Symbolic Link\n");
            break;



}

return 0;
}