#pragma once
#include "types.h"

typedef struct struct_cmdline {
	logical    (*hashFlag)         (const char* name);
	Flag**    (*getDefaultFlags)  (logical all);
	logical  (*hasOption)        (const char* name);
	logical  (*isOptionMultiple) (const char* name);
} CmdLine;
#ifdef __cplusplus
extern "C" {
#endif
	CmdLine * cmdline_create(int argc, char **argv, ParmDef parms[]);

	void cmdline_delete();

#ifdef __cplusplus
}
#endif

