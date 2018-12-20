#include <signal.h>
#include <stdio.h>
#include <unistd.h>

int main(int argc, char*argv[]){

	int pid = fork();

	switch(pid){
		case 0: // ejecutando el hijo
			int contSIGINT = 0;
			int contSIGTSTP = 0;

			while(contSIGTSTP + contSIGINT < 10){
				
			}

			break;
		case -1:
			//return 1;
			break;
		default: // ejecutando el padre, pid = pid del hijo
			break;

	}

}