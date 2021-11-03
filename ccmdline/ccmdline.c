#include <stdio.h>
#include "cmdline.h"

#include "c_wrapper.h"

int create(int argc, char** argv, ParmDef parms[]) {
	printf("hola\n");
	cmdline_create(argc, argv, parms);
	return 0;
}
void delete() {
	cmdline_delete();
}
