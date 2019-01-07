#include <sys/stat.h>
#include <stdio.h>
#include <sys/sysmacros.h>
#include <time.h>

/*
struct stat {
               dev_t     st_dev;         /* ID of device containing file
               ino_t     st_ino;         /* inode number
               mode_t    st_mode;        /* file type and mode
               nlink_t   st_nlink;       /* number of hard links
               uid_t     st_uid;         /* user ID of owner
               gid_t     st_gid;         /* group ID of owner
               dev_t     st_rdev;        /* device ID (if special file)
               off_t     st_size;        /* total size, in bytes
               blksize_t st_blksize;     /* blocksize for filesystem I/O
               blkcnt_t  st_blocks;      /* number of 512B blocks allocated

               /* Since Linux 2.6, the kernel supports nanosecond
                  precision for the following timestamp fields.
                  For the details before Linux 2.6, see NOTES.

               struct timespec st_atim;  /* time of last access
               struct timespec st_mtim;  /* time of last modification
               struct timespec st_ctim;  /* time of last status change

           #define st_atime st_atim.tv_sec      /* Backward compatibility
           #define st_mtime st_mtim.tv_sec
           #define st_ctime st_ctim.tv_sec
           };

*/

/*
* El número major y minor asociado al dispositivo
* El número de inodo del archivo
* El tipo de archivo (directorio, enlace simbólico o archivo ordinario)
* La hora en la que se accedió el fichero por última vez.
¿Qué diferencia hay entre st_mtime y st_ctime?
*/

int main(int argc, char *argv[])
{
    struct stat buf;
    char timebuf[50];
    int res = stat(argv[1], &buf);
    struct timespec lastaccess = buf.st_atim;
    struct tm *hora = localtime(&buf.st_atim.tv_sec);

    printf("Número major del dispositivo: %u\n", major(buf.st_dev));
    printf("Número minor del dispositivo: %u\n", minor(buf.st_dev));
    printf("Número de inodo del archivo: %d\n", buf.st_ino);
    printf("tipo: ");

    if (S_ISREG(buf.st_mode))
    {
        printf("regular file\n");
    }
    else if (S_ISDIR(buf.st_mode))
    {
        printf("directory\n");
    }
    else if (S_ISCHR(buf.st_mode))
    {
        printf("character device\n");
    }
    else if (S_ISBLK(buf.st_mode))
    {
        printf("block device\n");
    }
    else if (S_ISFIFO(buf.st_mode))
    {
        printf("named fifo pipe\n");
    }
    else if (S_ISLNK(buf.st_mode))
    {
        printf("sym link\n");
    }
    else if (S_ISSOCK(buf.st_mode))
    {
        printf("socket\n");
    }

	strftime(timebuf, 50, "%D",hora);
	printf("hora ultimo acceso: %s\n",timebuf);



    return 0;
}