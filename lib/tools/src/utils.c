#include <tools/utils.h>

void die(char *s,int ex){
	perror(s);
	exit(ex);
}
