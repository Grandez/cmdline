#pragma once
#ifndef __CMDLINE_H__
#define __CMDLINE_H__
#include "cmdline_types.h"

int  create(int argc, char** argv, Parameter parms[]);
void delete();

char          hasFlag(const char* name);
char          getDefaultFlags();
char          hasOption(const char* name);
char          isOptionMultiple(const char* name);
const char*   getOption(const char* name);
const char**  getOptionValues(const char* name);
char          getOptionNumValues(const char* name);
Parameter**   getDefaultOptions();
Parameter**   getCurrentOptions();
char          hasDefinition(const char* def);
char          isDefinitionMultiple(const char* name);
const char *  getDefinition(const char* name);
const char**  getDefinitionValues(const char* name);

Type          getType(const char name);

struct tm*      toTm         (const char* name);
struct tm**     toTmAll      (const char* name);
int             toInt        (const char* name);
int**           toIntAll     (const char* name);
long            toLong       (const char* name);
long**          toLongAll    (const char* name);
unsigned int    toUint       (const char* name);
unsigned int**  toUintAll    (const char* name);
unsigned long   toUlong      (const char* name);
unsigned long** toUlongAll   (const char* name);
float           toFloat      (const char* name);
float**         toFloatAll   (const char* name);
double          toDouble     (const char* name);
double**        toDoubleAll  (const char* name);
char *          toTimestamp  (const char* name);
#endif


