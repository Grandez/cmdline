#pragma once
/*
#ifndef __TYPES__
#define __TYPES__
typedef enum { FLAG, STRING, NUMBER, DECIMAL, DATE, TIME, DATETIME, TMS, DIR, DIR_EXISTS, FILE, FILE_EXISTS } Type;

enum Source { DEFAULT, ENV, CMDLINE, AUTO };

typedef struct _parmitem {
	const char* name;
	Type type;
	const char* value;   // default value
	bool multiple;   // Allow multiple values?
} parmItem;

#endif
#ifdef __cplusplus
extern "C"
{
#endif
	int  cmdlineInit(int parmc, parmItem parms[]);
	void cmdlineEnd();
	int parse(int argc, const char* argv[]);
#ifdef __cplusplus
}
#endif
*/
