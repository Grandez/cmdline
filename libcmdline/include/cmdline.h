#pragma once
#include "types.h"

typedef struct struct_cmdline {
	logical      (*hasFlag)            (const char* name);
	logical      (*hasOption)          (const char* name);
	logical      (*hasDefine)          (const char* name);
	logical      (*isOptionMultiple)   (const char* name);
	logical      (*isDefineMultiple)   (const char* name);
	logical      (*getFlag)            (const char* name);
	int          (*getOptionNumValues) (const char* name);
	int          (*getDefineNumValues) (const char* name);
	const char*  (*getOption)          (const char* name);
	const char*  (*getDefine)          (const char* name);
	const char** (*getOptionValues)    (const char* name);
	const char** (*getDefineValues)    (const char* name);
	Flag**       (*getDefaultFlags)    (logical active);
	Flag**       (*getCurrentFlags)    (logical active);
	Parameter**  (*getDefaultOptions)();
	Parameter**  (*getCurrentOptions)();
	Parameter**  (*getDefinitions)   ();

} CmdLine;
#ifdef __cplusplus
extern "C" {
#endif
	CmdLine *cmdline_create(int argc, const char **argv, ParmDef parms[]);

	void cmdline_delete(CmdLine *cmdline);

#ifdef __cplusplus
}
#endif

