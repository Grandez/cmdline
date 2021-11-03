#pragma once
#include "cmdline_types.h"

#ifdef __cplusplus
extern "C" {
#endif
int cmdline_create(int argc, char** argv, ParmDef parms[]);
void destroy();

#ifdef __cplusplus
}
#endif

