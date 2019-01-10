#include <sys/types.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/socket.h>
#include <netdb.h>
#include <sys/wait.h>



#define BUF_SIZE 500

int
main(int argc, char *argv[])
{
    struct addrinfo hints;
    struct addrinfo *result, *rp;
    int sfd, s;

    socklen_t peer_addr_len;

    char buf[BUF_SIZE];
    int n;
    pid_t pid;
    char host[NI_MAXHOST], port[NI_MAXSERV];


    if (argc != 3)
    {
        fprintf(stderr, "Usage: %s host port\n", argv[0]);
        exit(EXIT_FAILURE);
    }

    memset(&hints, 0, sizeof(struct addrinfo));
    hints.ai_family = AF_UNSPEC;    /* Allow IPv4 or IPv6 */
    hints.ai_socktype = SOCK_STREAM; /* TCP socket */
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
    int sd;
    for (rp = result; rp != NULL; rp = rp->ai_next)
    {
        sfd = socket(rp->ai_family, rp->ai_socktype,
                     0);
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

    /* Read datagrams and echo them back to sender */
    listen(sfd,5);

    while (1)
    {
        char host[NI_MAXHOST];
        char serv[NI_MAXSERV];
        int nread;
        struct sockaddr peer_addr;
        peer_addr_len = sizeof(struct sockaddr);

        int acceptConn = accept(sfd, (struct sockaddr *)&peer_addr, &peer_addr_len);
        getnameinfo((struct sockaddr *)&peer_addr, peer_addr_len, host, NI_MAXHOST, serv, NI_MAXSERV, NI_NUMERICHOST | NI_NUMERICSERV);



        nread = recv(acceptConn, buf, BUF_SIZE, 0);
        if (nread == -1)
            continue;               /* Ignore failed request */

        /* Request accepted*/

        pid = fork();

        if ( pid == -1 )
        {
            perror( "fork() failed" );
            close(acceptConn);
            close(sfd);
            return EXIT_FAILURE;
        }

        if ( pid > 0 )
        {
            /* parent closes the new client socket, the child process will handle that connection */
            close( acceptConn );
            /* we wait for child finalization */
            wait(&pid);
            return 0;

        }
        else /* pid == 0, we're on child process code */
        {
            do
            {

                printf( "CHILD %d: Blocked on recv()\n", getpid() );

                /* recv() will block until we receive data (n > 0)
                    or there's an error (n == -1)
                     or the client closed the socket (n == 0) */
                n = recv( acceptConn, buf, BUF_SIZE, 0 );
                s = getnameinfo((struct sockaddr *) &peer_addr,
                                peer_addr_len, host, NI_MAXHOST,
                                port, NI_MAXSERV, NI_NUMERICSERV);

                if ( n == -1 )
                {
                    perror( "recv() failed" );
                    return EXIT_FAILURE;
                }
                else if ( n == 0 )
                {
                    printf( "CHILD %d: Rcvd 0 from %s:%s; closing socket...\n",
                            getpid(), host, port );
                }
                else /* n > 0 */
                {
                    buf[n] = '\0';    /* assume this is text data */
                    printf( "CHILD %d: Rcvd message from %s:%s.\n", getpid(), host, port);

                    /* send same message back to the client */
                    s = sendto( acceptConn, buf, BUF_SIZE, 0, NULL, 0 );

                  
                }
            }
            while ( n > 0 );

            printf( "CHILD %d: exiting...\n", getpid() );
            close( sfd );
            exit( EXIT_SUCCESS );
        }
    }



}

