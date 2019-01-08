/*
Hacer un programa que muestre el identificador de proceso, de proceso padre, de grupo de procesos y de sesión. 
Mostrar además el número de archivos que puede abrir el proceso y el directorio de trabajo actual.
*/

#include <stdio.h>
#include <unistd.h>
#include <sys/time.h>
#include <sys/resource.h>


int main(int argc, char* argv[]){



	struct rlimit rlim;
	int limit = getrlimit(RLIMIT_NOFILE, &rlim);
	char dir[35]="";
	if(getcwd(dir, 35)==NULL) return 1; 

	int pid = getpid();
	int ppid = getppid();
	int pgid = getpgid(0);
	int sid = getsid(0);


	printf("límite actual de ficheros que puede abrir este proceso:%li\n",rlim.rlim_cur); /* Límite actual */
	printf("límite máximo de ficheros que puede abrir este proceso:%li\n",rlim.rlim_max); /* Límite máximo */
	printf("El directorio de trabajo del proceso es: %s\n",dir);
	printf("El pid de este proceso es: %d\n",pid);
	printf("El pid del padre de este proceo es: %d\n",ppid);
	printf("El pid del grupo de este proceo es: %d\n",pgid);
	printf("La sesión a la que pertenece este proceso es: %d\n",sid);



	return 0;
}

