#pragma once
#include "types.h"

typedef struct struct_cmdline {
	char    (*hashFlag)         (const char* name);
	Flag* (*getDefaultFlags)  (char all);
	logical(*hasOption)        (const char* name);
	logical(*isOptionMultiple) (const char* name);
} sCmdLine;
/*
* vector<const char*> args();


		// Options control
		const char* getOption(const char* name);
		const char* getOption(string name) { return getOption(name.c_str()); }
		vector<const char*>  getOptionValues(const char* name);
		vector<const char*>  getOptionValues(string name);

		int       getOptionNumValues(const char* name);
		int       getOptionNumValues(string name);
		Options   getDefaultOptions();
		Options   getCurrentOptions();

		template <typename T> const T         getOptionAs(T t, const char* name) {
			return getOptionAs<T>(name);
		}
		template <typename T> const T         getOptionAs(const char* name) {
			const char* value = getOption(name);
			return castByNative<T>(value);
		}
		template <typename T> const T         getOptionAs(string name) { return getOptionAs<T>(name.c_str()); }
		template <typename T> const vector<T> getOptionValuesAs(string name) { return getOptionValuesAs<T>(name.c_str()); };
		template <typename T> const vector<T> getOptionValuesAs(const char* name);
		// Definitions
	bool        hasDefinition(const char* def);
	bool        hasDefinition(string def);
	bool        isDefinitionMultiple(const char* name);
	bool        isDefinitionMultiple(string name);
	const char* getDefinition(const char* name);
	const char* getDefinition(string name);

	vector<const char*>  getDefinitionValues(const char* name);
	vector<const char*>  getDefinitionValues(string name);

*/


#ifdef __cplusplus
extern "C" {
#endif

	sCmdLine * create();
	void destroy(sCmdLine* scmdline);

#ifdef __cplusplus
}
#endif

