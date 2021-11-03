#pragma once
#ifndef __CMDLINE_CTYPES__
#define __CMDLINE_CTYPES__


typedef enum _Type {
	STRING, CHAR, BOOL,
	NUMBER, DECIMAL, LONGNUMBER, LONGDECIMAL,
	DATE, TIME, DATETIME, TMS,
	DIR, DIR_EXISTS, FILES, FILE_EXISTS,
	FLAG
} Type;
 typedef enum _logical { FALSE, TRUE } logical;

typedef enum { DEFAULT, ENV, CMDLINE, CODE, AUTO } Source;

typedef struct _option {
	const char* name;
	const char** values;
} Option;

typedef struct _Parameter {
	const char* name;
	Type type;
	char* value;
	logical multiple;
} Parameter;

#endif
