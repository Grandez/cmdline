/*
* Funciones de utilidad de commandline 
* No acceden a la clase
*/
#include <ctype.h>
#include <cstring>

#include "config.h"
#include "commandline_aux.hpp"

#ifdef _WIN32
#pragma warning( disable : 4996 )
#endif
namespace NS2 {
bool isParameter(char c) {
	return (c == '/' || c == '+' || c == '-');
}
char getFirstCharacter(const char *arg) {
	return (arg == 0x0) ? 0x0 : arg[0];
}

bool isConfigFile (int argc, const char **argv, int idxArgument, bool sensitive) {
/*
     char tmp[64];
     char configName[64] = CMDLINE_CONFIG;
     copyParameterInUpperCase(arg, sensitive, tmp);
     copyParameterInUpperCase(configName, sensitive, configName);
     return (strcmp(tmp, configName) == 0);
*/
     return false;
}
void copyParameterInUpperCase(const char *arg, bool sensitive, char *name) {
	  strcpy(name, arg);
	  if (sensitive) {
		  for (size_t j = 0; j < strlen(arg); j++) name[j] = toupper(arg[j]);
	   }
 }
char *checkKeywordHelp(const char *arg) {
     if (strcmp(arg, "-h") == 0 ||  strcmp(arg, "--help") == 0) return (char *) "+help";
     if (strcmp(arg, "-H") == 0 ||  strcmp(arg, "--HELP") == 0) return (char *) "+HELP";
     return 0x0;
}

}