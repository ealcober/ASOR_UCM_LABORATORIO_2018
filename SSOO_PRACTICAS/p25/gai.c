#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <stdio.h>
#include <string.h>




int main(int argc, char *argv[])
{
    //  El programa tiene 4 argumentos
    //  el argumento 0 <nombre_programa>
    //  el argumento 1 es palomitas
    //  el argumento 2 es de
    //  el argumento 3 es maiz
    //printf("%d\n",argc);
    if(argc != 2)
    {
        perror("Introduzca el host cuya conectividad quiere comprobar\n");
        return 1;
    }

    struct addrinfo hints;
    struct addrinfo *res;
    struct sockaddr *socks;
    memset(&hints, 0, sizeof(struct addrinfo));
    hints.ai_family = AF_UNSPEC; //IPv4 & IPv6
    //hints.ai_socktype = SOCK_STREAM; // SOCK_DGRAM
    hints.ai_flags = AI_PASSIVE;



    int rc = getaddrinfo(argv[1], NULL, &hints, &res);

    if (rc != 0)
    {
        printf("Error: %s\n", gai_strerror(rc));
        return -1;

    }

    /*
    struct addrinfo {
           int     ai_flags;
           int     ai_family;
           int     ai_socktype;
           int     ai_protocol;
           size_t  ai_addrlen;
           struct sockaddr *ai_addr;
           char   *ai_canonname;
           struct addrinfo *ai_next;
       };

       struct sockaddr {
    sa_family_t sa_family;  address family, AF_xxx
    char        sa_data[14];     14 bytes of protocol address
    };
    */
    //    # Los protocolos 2 y 10 son AF_INET y AF_INET6, respectivamente (ver socket.h)
    //    # Los tipos 1, 2, 3 son SOCK_STREAM, SOCK_DGRAM y SOCK_RAW, respectivamente

    for(struct addrinfo *it = res; it-> ai_next != NULL; it = it->ai_next)
    {
        char host[NI_MAXHOST];
        char serv[NI_MAXSERV];

        int a = getnameinfo(it->ai_addr, it->ai_addrlen, host, NI_MAXHOST * sizeof(char), serv,
                            sizeof(char) * NI_MAXSERV, NI_NUMERICHOST ); //| NI_NUMERICSERV);

        if(a != 0)
            printf("Error: %s\n", gai_strerror(a));
        else
            printf("%s\t%d\t%d\n", host, it->ai_addr->sa_family, it->ai_socktype);


    }

    freeaddrinfo(res);
    return 0;
}

