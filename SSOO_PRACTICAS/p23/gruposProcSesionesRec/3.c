#include <stdio.h>
#include <unistd.h>
#include <sys/time.h>
#include <sys/resource.h>
#include <sys/types.h>
#include <sys/wait.h>


int main(int argc, char* argv[]){


	int ppid;
	int pgid;
	int sid;

	char path[6]="/tmp/\0";

	int pid = fork();

	switch(pid){
		case 0: // ejecutando el hijo
			printf("rama hijo\n");
			sleep(20);
			ppid = getppid();
			pgid = getpgid(0);
			sid = getsid(0);
			setsid();
			if (chdir(path) != 0) return 1;
			printf("Directorio de trabajo del demonio: %s\n", path);
			
			printf("El pid de este proceso es: %d\n",pid);
			printf("El pid del padre de este proceo es: %d\n",ppid);
			printf("El pid del grupo de este proceo es: %d\n",pgid);
			printf("La sesión a la que pertenece este proceso es: %d\n",sid);
			break;
		case -1:
			//return 1;
			break;
		default: // ejecutando el padre, pid = pid del hijo
		//	wait(&pid);
			printf("rama pater\n");
			ppid = getppid();
			pgid = getpgid(0);
			sid = getsid(0);
			
			printf("El pid de este proceso es: %d\n",pid);
			printf("El pid del padre de este proceo es: %d\n",ppid);
			printf("El pid del grupo de este proceo es: %d\n",pgid);
			printf("La sesión a la que pertenece este proceso es: %d\n",sid);
			break;

	}

	return 0;

}