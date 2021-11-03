#pragma once
#include "cmdline_types.h"

#ifdef __cplusplus
extern "C" {
#endif
int cmdline_create(int argc, char** argv, Parameter parms[]);
void destroy();

#ifdef __cplusplus
}
#endif

