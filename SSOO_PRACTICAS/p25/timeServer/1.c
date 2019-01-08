#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <stdio.h>
#include <string.h>
#include <stdio.h>
#include <time.h>




int main(int argc, char *argv[])
{

    if(argc != 3)
    {
        perror("Usage: ./1 host port\n");
        return 1;
    }

    struct addrinfo hints;
    struct addrinfo *res;
    struct sockaddr *socks;
    memset(&hints, 0, sizeof(struct addrinfo));
    hints.ai_family = AF_INET; //IPv4 & IPv6
    hints.ai_socktype = SOCK_DGRAM;
    hints.ai_flags = AI_PASSIVE;



    int rc = getaddrinfo(argv[1], argv[2], &hints, &res);

    if (rc != 0)
    {
        printf("Error: %s\n", gai_strerror(rc));
        return -1;

    }

    int sockIn = socket(res->ai_family, res->ai_socktype, res->ai_protocol);;

    bind(sockIn, res->ai_addr, res->ai_addrlen);

    freeaddrinfo(res);

    char hora[25];
    char fecha[50];
    time_t tiempo ;
    struct tm *tm;
    while(1)
    {

        int nb;
        char buffer[256]; //16 bytes para udp
        struct sockaddr src_addr;
        socklen_t addrlen = sizeof(struct sockaddr);
        nb = recvfrom(sockIn, buffer, 255, 0, (struct sockaddr *)&src_addr, &addrlen);

        buffer[nb] = '\0';

        char host[NI_MAXHOST];
        char serv[NI_MAXSERV];

        int a = getnameinfo(&src_addr, addrlen, host, NI_MAXHOST * sizeof(char), serv,
                            sizeof(char) * NI_MAXSERV, NI_NUMERICHOST | NI_NUMERICSERV);

        if(a != 0)
            printf("Error: %s\n", gai_strerror(a));

        // sacar la hora del sistema



        /*

        struct tm {
               int tm_sec;    /* Seconds (0-60)
               int tm_min;    /* Minutes (0-59)
               int tm_hour;   /* Hours (0-23)
               int tm_mday;   /* Day of the month (1-31)
               int tm_mon;    /* Month (0-11)
               int tm_year;   /* Year - 1900
               int tm_wday;   /* Day of the week (0-6, Sunday = 0)
               int tm_yday;   /* Day in the year (0-365, 1 Jan = 0)
               int tm_isdst;  /* Daylight saving time
           };
        */

        tiempo = time(NULL);
        tm = localtime(&tiempo);

        sprintf(hora, "%d:%d:%d\n\0", tm->tm_hour, tm->tm_min, tm->tm_sec);
        sprintf(fecha, "%d/%d/%d\n\0", tm->tm_mday, tm->tm_mon + 1, tm->tm_year + 1900);
        switch(buffer[0])
        {
        case 't':
            sendto(sockIn, hora, strlen(hora), 0, (struct sockaddr *)&src_addr, addrlen);
            break;
        case 'd':
            sendto(sockIn, fecha, strlen(fecha), 0, (struct sockaddr *)&src_addr, addrlen);
            break;
        case 'q':
            sendto(sockIn, "discconnected\n\0", strlen("discconnected\n\0"), 0, (struct sockaddr *)&src_addr, addrlen);
            return 0;
            break;
        default:
            break;

        }



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

    //for(struct addrinfo *it = res; it-> ai_next != NULL; it = it->ai_next)






    return 0;
}

