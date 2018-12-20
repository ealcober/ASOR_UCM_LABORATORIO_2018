#include <stdio.h>
#include <signal.h>
#include <stdlib.h>


int main(int argc, char* argv[]){
	char name[11]= "SLEEP_SECS\0";
	const char value = '9';
	setenv(&name, &value, 0);
	sigset_t set;
	sigset_t emptySet;
	sigemptyset(&emptySet);
	sigemptyset(&set);
	sigaddset(&set, SIGINT);
	sigaddset(&set, SIGTSTP);

	int sigprocmask(SIG_BLOCK, &set, &emptySet);
}