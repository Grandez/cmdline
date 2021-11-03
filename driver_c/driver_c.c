// driver_c.cpp : This file contains the 'main' function. Program execution begins and ends there.
//
#include <stdio.h>
#include <stdlib.h>
#include "cmdline.h"
#include "cmdline_types.h"

Parameter parms[] = {
	 {"verbose", FLAG, "false", FALSE}
	,{"output",  STRING, "", FALSE}
	,0x0
};

int main(int argc, char *argv[]) {
    printf("HOla");
	create(argc, argv, parms);
}
