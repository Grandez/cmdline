#include <stdio.h>
#include <stdlib.h>

#include "cmdline.h"

void showDefinitions(CmdLine* ptr, int expected, char print);
void showFlags(CmdLine* ptr, int expected, char print);

ParmDef parms[] = {
	{"output", FLAG, "1", FALSE}
	,0x0
};
CmdLine* cmdline = NULL;

int main(int argc, char **argv) {
    printf("Hello World!\n");
	char *argv2[] = {
		"Program"
		,"/def1=define1"
		,"/def2=define2"
	};
	//CmdLine *cmdline = cmdline_create(argc,argv, parms);
	cmdline = cmdline_create(3,argv2, parms);
	showDefinitions(0x0, 2, 0x0);
	showFlags(0x0, 1, 0x0);
	/*
	logical res  = cmdline->hasFlag("output");
	Parameter** defs = cmdline.getDefinitions();
	Parameter *p = defs[0];
	int i = 0;
	while (defs[i]) {
		printf("%s", defs[i]->name);
		i++;
	}
	//	logical res  = cmdline->hashFlag("output");
//	Flag **flags = cmdline->getDefaultFlags(UNCHECKED);
//	if (res == UNKNOW) {
//		printf("Error\n");
//	}
*/
	cmdline_delete(cmdline);
}
void showDefinitions(CmdLine* ptr, int expected, char print) {
	printf("Checking definitions\t");
	if (ptr == NULL) ptr = cmdline ;
	Parameter** defs = ptr->getDefinitions();
	int i = 0;
	while (defs[i]) {
		if (print) printf("%s", defs[i]->name);
		i++;
	}
	if (i == expected) {
		printf("OK\n");
	} else {
		printf("KO - Expected %d - found %d\n", expected, i);
		exit(1);
	}
}
void showFlags(CmdLine* ptr, int expected, char print) {
	printf("Checking Flags\t");
	if (ptr == NULL) ptr = cmdline ;
	Flag** flags = ptr->getCurrentFlags(FALSE);
	int i = 0;
	while (flags[i]) {
		if (print) printf("%s", flags[i]->name);
		i++;
	}
	if (i == expected) {
		printf("OK\n");
	} else {
		printf("KO - Expected %d - found %d\n", expected, i);
		exit(1);
	}
}

