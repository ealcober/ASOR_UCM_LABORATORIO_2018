#include <sys/types.h>
#include <pwd.h>
#include <stdio.h>
/*
Ejercicio 3. Modificar el programa anterior para que muestre además el nombre de usuario,
el directorio home y la descripción del usuario.
*/
int main(){
	struct passwd *p;

	p = getpwuid(1000);

	printf("nombre de usuario: %s\ndirectorio home: %s\ndescripción del usuario: %s\n",p->pw_name,p->pw_dir,p->pw_gecos);

	return 0;

}