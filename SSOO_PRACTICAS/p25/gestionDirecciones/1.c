#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

#define BUF_SIZE 500

int
main(int argc, char *argv[])
{
    struct addrinfo hints;
    struct addrinfo *result, *rp;
    int sfd, s, j;
    size_t len;
    ssize_t nread;
    char buf[BUF_SIZE];
    // comprobamos que hayamos pasado un argumento
    if (argc < 2)
    {
        fprintf(stderr, "Usage: %s host\n", argv[0]);
        exit(EXIT_FAILURE);
    }

    /* Obtain address(es) matching host/port */

    memset(&hints, 0, sizeof(struct addrinfo));
    hints.ai_family = AF_UNSPEC;    /* Allow IPv4 or IPv6 */
    // hints.ai_socktype = SOCK_DGRAM; /* Datagram socket */
    hints.ai_flags = AI_PASSIVE;

    s = getaddrinfo(argv[1], NULL, &hints, &result);
    if (s != 0)
    {
        fprintf(stderr, "getaddrinfo: %s\n", gai_strerror(s));
        exit(EXIT_FAILURE);
    }

    /* getaddrinfo() returns a list of address structures.
       Just iterate over the collection and print the info
       returned by the function.
       struct addrinfo {

               int              ai_family;
               int              ai_socktype;

               socklen_t        ai_addrlen;
               struct sockaddr *ai_addr;

           };
        struct sockaddr {
    			unsigned short sa_family;   // address family, AF_xxx
    			char sa_data[14]; // 14 bytes of protocol address
    };
        */
    j = 1;
    for (rp = result; rp != NULL; rp = rp->ai_next)
    {
        printf("%d: ", j);
        
        char host[NI_MAXHOST];
        char serv[NI_MAXSERV];

        int a = getnameinfo(rp->ai_addr, rp->ai_addrlen, host, NI_MAXHOST * sizeof(char), serv,
                            sizeof(char) * NI_MAXSERV, NI_NUMERICHOST); //| NI_NUMERICSERV);

        if(a != 0)
            printf("Error: %s\n", gai_strerror(a));
        else
            printf("%s.\t", host);


        switch(rp->ai_family)
        {
        case AF_INET:
            printf("familia : IPv4. ");
            break;
        case AF_INET6:
            printf("familia : IPv6. ");
            break;
        default:
            break;
        }

        switch(rp->ai_socktype)
        {
        case SOCK_STREAM:
            printf("Socket TCP.\n");
            break;
        case SOCK_DGRAM:
            printf("Socket UDP.\n");
            break;
        default:
        	printf("\n");

        }



        j++;

    }



    freeaddrinfo(result);           /* No longer needed */


    exit(EXIT_SUCCESS);
}
