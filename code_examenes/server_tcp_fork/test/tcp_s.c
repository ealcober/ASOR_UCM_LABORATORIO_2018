#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<netdb.h>
#include<sys/socket.h>
#include<signal.h>
#include<sys/wait.h>
#include<unistd.h>
#include<sys/types.h>

void esperar(int sig);
void conexion(int cliente);

int main(int argc, char* argv[]){

	struct sigaction sa;
	sa.sa_handler = esperar;
	sa.sa_flags = SA_RESTART;
	sigaction(SIGCHLD, &sa, NULL);

	struct addrinfo hints;
	struct addrinfo *res;
	
	memset(&hints,0,sizeof(struct addrinfo));
	hints.ai_family = AF_UNSPEC;
	hints.ai_socktype = SOCK_STREAM;
	hints.ai_flags = AI_PASSIVE;
	int rc = getaddrinfo(argv[1],argv[2], &hints, &res);
	if(rc != 0) {
		printf("Error: %s\n", gai_strerror(rc)); 
		return -1;
	}

	int sd = socket(res->ai_family,res->ai_socktype,0);
	
	bind(sd, (struct sockaddr *) res->ai_addr, res->ai_addrlen);

	listen(sd,5);

	while(1){
		char host[NI_MAXHOST];
		char serv[NI_MAXSERV];

		struct sockaddr_storage src_addr;
		socklen_t addrlen = sizeof(struct sockaddr_storage);

		//Establece conexion
		int cliente = accept(sd, (struct sockaddr *) &src_addr, &addrlen);
		getnameinfo((struct sockaddr *)&src_addr, addrlen, host, NI_MAXHOST, serv, NI_MAXSERV, NI_NUMERICHOST | NI_NUMERICSERV);

		printf("Conexion de cliente %s:%s \n", host, serv);

		pid_t pid = fork();
		switch(pid){
			case 0: //hijo
				close(sd);
				conexion(cliente);
				close(cliente);
				return 0;
			case -1: //error
				close(sd);
				close(cliente);
				break;
			default: //padre
				close(cliente);
				break;
		
		
		
		}
	
	}

	return 0;
}


void esperar(int sig){

	int status;

	wait(&status);
}

void conexion(int cliente){
	while(1){
		int nb;
		char buf[256];

		nb = recv(cliente, buf, 255,0);
		buf[nb] = '\0';
		
		//Cierre pasivo
		if(nb == 0){ 
			printf("Salgo por el 0");
			break;
		}
		printf("Mensaje: %s \n", buf);
		send(cliente, buf, nb, 0);

		if(buf[0] == 'Q' && nb == 2){
		       	printf("Salgo por la Q");
			break;
		}
	}
}
