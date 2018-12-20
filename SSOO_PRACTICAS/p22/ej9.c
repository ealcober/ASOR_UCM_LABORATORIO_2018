#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <stdio.h>
#include <sys/sysmacros.h>
#include <time.h>



/*
int stat(const char *pathname, struct stat *statbuf);

struct stat {
               dev_t     st_dev;         /* ID of device containing file 
               ino_t     st_ino;         /* Inode number 
               mode_t    st_mode;        /* File type and mode 
               nlink_t   st_nlink;       /* Number of hard links 
               uid_t     st_uid;         /* User ID of owner 
               gid_t     st_gid;         /* Group ID of owner 
               dev_t     st_rdev;        /* Device ID (if special file) 
               off_t     st_size;        /* Total size, in bytes 
               blksize_t st_blksize;     /* Block size for filesystem I/O 
               blkcnt_t  st_blocks;      /* Number of 512B blocks allocated 

               /* Since Linux 2.6, the kernel supports nanosecond
                  precision for the following timestamp fields.
                  For the details before Linux 2.6, see NOTES. 

               struct timespec st_atim;  /* Time of last access 
               struct timespec st_mtim;  /* Time of last modification
               struct timespec st_ctim;  /* Time of last status change 

           #define st_atime st_atim.tv_sec      /* Backward compatibility 
           #define st_mtime st_mtim.tv_sec
           #define st_ctime st_ctim.tv_sec
           
*/

int main(int argc, char* argv[]){
	
	struct stat info;
	stat(argv[1], &info);

	struct tm* tm_info;
	struct tm* tm_info2;

	char buffer[26];

	tm_info = localtime(&info.st_mtim.tv_sec);
	tm_info2 = localtime(&info.st_ctim.tv_sec);

	/*
* El número major y minor asociado al dispositivo
* El número de inodo del archivo
* El tipo de archivo (directorio, enlace simbólico o archivo ordinario)
* La hora en la que se accedió el fichero por última vez. ¿Qué diferencia hay entre st_mtime y st_ctime?
	*/
	// con info.st_dev y las macros minor y major podemos sacar estos números
	printf("ID of device containing file: %lu\n", info.st_dev);
	printf("Major Number: %d\n", major(info.st_dev));
	printf("Minor Number: %d\n", minor(info.st_dev));
	printf("Inode number: %lu\n", info.st_ino);
	printf("File type and mode: %u\n", info.st_mode);
	/*printf("Number of hard links: %lu\n", info.st_nlink);
	printf("User ID of owner: %d\n", info.st_uid);
	printf("Group ID of owner: %d\n", info.st_gid);
	printf("Device ID (if special file): %lu\n", info.st_rdev);
	printf("Total size, in bytes: %li\n", info.st_size);
	printf("Block size for filesystem I/O: %li\n", info.st_blksize);
	printf("Number of 512B blocks allocated  %li\n", info.st_blocks); 
	*/

/*
struct timespec {
    time_t   tv_sec;   //      seconds 
    long     tv_nsec;  //      nanoseconds 
}
*/
    // printf("%lld.%.9ld", (long long)ts.tv_sec, ts.tv_nsec)
	printf("Time of last modification:");
    strftime(buffer, 26, "%Y-%m-%d %H:%M:%S", tm_info);
    puts(buffer);
    printf("Time of last status change:");
    strftime(buffer, 26, "%Y-%m-%d %H:%M:%S", tm_info2);
    puts(buffer);

	//printf("Time of last modification: %lld.%.9ld\n", (long long)info.st_mtim.tv_sec, info.st_mtim.tv_nsec);  // Time of last modification
	//printf("Time of last status change: %lld.%.9ld\n", (long long)info.st_ctim.tv_sec, info.st_ctim.tv_nsec);  // Time of last status change

	return 0;

}