/*
* Funciones de utilidad de commandline 
* No acceden a la clase
*/

namespace NS2 {
bool  isParameter        (char c);
char  getFirstCharacter  (const char *arg);
bool  isConfigFile       (int argc, const char **argv, int idxArgument, bool sensitive);
char* checkKeywordHelp   (const char *arg);

void  copyParameterInUpperCase (const char *arg, bool sensitive, char *name);
char* configFileInCommandLine  (int argc, const char **argv);

}