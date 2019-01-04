#include <errno.h> // contiene los símbolos de error
#include <stdio.h>
#include <string.h>
#include <unistd.h>

int main(){
	int i=0;
	for (i=0;i<256;i++)
		printf("%d: %s\n",i, strerror(i));

	return 0;
}