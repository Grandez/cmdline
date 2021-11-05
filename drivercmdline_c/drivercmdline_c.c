#include <stdio.h>

#include "cmdline.h"

ParmDef parms[] = {
	{"output", FLAG, "1", UNCHECKED}
	,0x0
};

int main(int argc, char **argv) {
    printf("Hello World!\n");
	sCmdLine *cmdline = cmdline_create(argc,argv, parms);
	logical res  = cmdline->hashFlag("output");
	Flag **flags = cmdline->getDefaultFlags(UNCHECKED);
	if (res == UNKNOW) {
		printf("Error\n");
	}
	cmdline_delete(cmdline);
}
