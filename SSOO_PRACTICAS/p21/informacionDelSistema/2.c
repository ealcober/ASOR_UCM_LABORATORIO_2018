#include <sys/utsname.h>
#include <errno.h>
#include <stdio.h>
#include <string.h>

int main()
{
    struct utsname buf;

    switch(uname(&buf))
    {
    case -1:
        perror(strerror(-1));
        break;
    case EFAULT:
        perror(strerror(EFAULT));
        break;
    default:
    	printf("%s, %s, %s, %s, %s, %s.\n", buf.sysname, buf.nodename, buf.release, buf.version, buf.machine, buf.__domainname);
        break;
    }

    return 0;
}

