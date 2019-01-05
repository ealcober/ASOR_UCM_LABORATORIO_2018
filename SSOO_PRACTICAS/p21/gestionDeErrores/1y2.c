#include <unistd.h>
#include <errno.h> // contiene los símbolos de error
#include <stdio.h>
#include <string.h>

int main()
{
    printf("UID inicial: %d\n", getuid());
    int res = setuid(0);
    printf("info:\n");

    printf("el error %d es EINVAL\n", EINVAL);
    printf("el error %d es EPERM\n", EPERM);
    printf("\n");
	printf("setuid devuelve %d\n", res);
    switch(res)
    {
    case(EINVAL):
        perror(strerror(EINVAL));
        break;
    case(EPERM):
        perror(strerror(EPERM));
        break;
    case(-1):
    	perror(strerror(-1)); q
        break;

    }
    printf("UID final: %d\n", getuid());
    return 0;
}