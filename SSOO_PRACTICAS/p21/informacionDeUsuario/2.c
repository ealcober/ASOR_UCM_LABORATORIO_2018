#include <unistd.h>
#include <stdio.h>

int main(){
	printf("El id real del usuario es: %d\n",getuid());
	printf("El id efectivo del usuario es: %d\n",geteuid());
}