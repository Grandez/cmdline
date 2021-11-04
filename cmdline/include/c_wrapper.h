#pragma once
#include "cmdline_ctypes.h"

#ifdef __cplusplus
extern "C" {
#endif
int cmdline_create(int argc, char** argv, ParmDef parms[]);
void cmdline_delete();

#ifdef __cplusplus
}
#endif

