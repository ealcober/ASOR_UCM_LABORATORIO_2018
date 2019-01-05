#include <stdio.h>
#include <time.h>
#include <unistd.h>
#include <stdint.h> //  inttypes.h

int main(void)
{
    time_t result;

    result = time(NULL);
    printf("%ju secs since the Epoch\n",(uintmax_t)result);
    printf("%i secs since the Epoch\n",result);
    return(0);
}
