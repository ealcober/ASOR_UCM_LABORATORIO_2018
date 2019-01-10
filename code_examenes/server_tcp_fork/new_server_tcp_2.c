/*
Ejercicio 3 (1,5 puntos). Escriba un programa servidor TCP que escuche en una dirección (IPv4 o
IPv6 en cualquier formato) y puerto dados como argumentos. El servidor devolverá lo que el cliente
le envíe y será capaz de atender a varios clientes a la vez. En cada conexión, el servidor imprimirá la
dirección y el puerto del cliente, así como el PID del proceso que la atiende. Finalmente, el servidor
gestionará adecuadamente la finalización de los procesos hijo que cree.
*/


#include <sys/types.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/socket.h>
#include <netdb.h>
#include <sys/wait.h>
#include <pthread.h>



#define BUF_SIZE 500

int
main(int argc, char *argv[])
{
    struct addrinfo hints;
    struct addrinfo *result, *rp;
    int sfd, s, a;
    pid_t pid;
    struct sockaddr_storage peer_addr;
    socklen_t peer_addr_len;
    ssize_t nread;
    char buf[BUF_SIZE];

    if (argc != 3)
    {
        fprintf(stderr, "Usage: %s host port\n", argv[0]);
        exit(EXIT_FAILURE);
    }

    memset(&hints, 0, sizeof(struct addrinfo));
    hints.ai_family = AF_UNSPEC;    /* Allow IPv4 or IPv6 */
    hints.ai_socktype = SOCK_STREAM; /* Datagram socket */
    hints.ai_flags = AI_PASSIVE;    /* For wildcard IP address */


    s = getaddrinfo(argv[1], argv[2], &hints, &result);
    if (s != 0)
    {
        fprintf(stderr, "getaddrinfo: %s\n", gai_strerror(s));
        exit(EXIT_FAILURE);
    }


    /* getaddrinfo() returns a list of address structures.
                Try each address until we successfully bind(2).
                If socket(2) (or bind(2)) fails, we (close the socket
                and) try the next address. */

    for (rp = result; rp != NULL; rp = rp->ai_next)
    {
        sfd = socket(rp->ai_family, rp->ai_socktype,
                     rp->ai_protocol);
        if (sfd == -1)
            continue;

        if (bind(sfd, rp->ai_addr, rp->ai_addrlen) == 0)
            break;                  /* Success */

        close(sfd);
    }

    if (rp == NULL)                 /* No address succeeded */
    {
        fprintf(stderr, "Could not bind\n");
        exit(EXIT_FAILURE);
    }

    freeaddrinfo(result);           /* No longer needed */

    /* fork */
    listen(sfd, 5);
    int i = 0;
    pid_t pids[5];
    while (i < 5)
    {
        ssize_t nbytes;
        char host[NI_MAXHOST];
        char service[NI_MAXSERV];

        /*
        int accept(int socket, struct sockaddr *restrict address,
             socklen_t *restrict address_len);
        */
        // en a tenemos el socket de la conexión entrante y en peer_addr los datos de la conexión.
        a = accept(sfd, (struct sockaddr *) &peer_addr, &peer_addr_len);
        s = getnameinfo((struct sockaddr *) &peer_addr,
                        peer_addr_len, host, NI_MAXHOST,
                        service, NI_MAXSERV, NI_NUMERICSERV | NI_NUMERICHOST);



        pids[i] = fork();
        switch(pids[i])
        {
        case -1:
            return -1;
            break;
        case 0: //hijo
            
            sprintf(buf, "%d Connection received from %s with src_port = %s, by process #%d\0\n", i, host, service, pids[i]);
            send(a, buf, BUF_SIZE, 0);
            recv(a, buf, BUF_SIZE, 0);
            switch(buf[0])
            {
            case 'q':
                close(a);
                pthread_exit(0);
                break;
            default:
                break;

            }


            break;
        default://padre
            //wait(&pid);
            printf("Connection received from %s with src_port = %s, by process #%d", host, service, pids[i]);
            i++;

            break;
        }







    }
    int j;
    for(j = 0; j < 5; j++)
        wait(&pids[j]);
    printf("Todos los hijos han terminado.\n");

    close(a);
    close(sfd);
    return(0);

}

/*
peer_addr_len = sizeof(struct sockaddr_storage);
        nread = recvfrom(sfd, buf, BUF_SIZE, 0,
                         (struct sockaddr *) &peer_addr, &peer_addr_len);
        if (nread == -1)
            continue;               /* Ignore failed request

        char host[NI_MAXHOST], service[NI_MAXSERV];

        s = getnameinfo((struct sockaddr *) &peer_addr,
                        peer_addr_len, host, NI_MAXHOST,
                        service, NI_MAXSERV, NI_NUMERICSERV);
        if (s == 0)
            printf("Received %zd bytes from %s:%s\n",
                   nread, host, service);
        else
            fprintf(stderr, "getnameinfo: %s\n", gai_strerror(s));

        if (sendto(sfd, buf, nread, 0,
                   (struct sockaddr *) &peer_addr,
                   peer_addr_len) != nread)
            fprintf(stderr, "Error sending response\n");
*/