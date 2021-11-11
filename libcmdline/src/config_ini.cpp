#include "config_ini.hpp"
#include "tools.hpp"

using namespace std;
namespace NS2 {
char* loadIniFile (char *file) {
    char *buffer;
    struct stat stat_buf;
    FILE * pFile;
    int size;
    int rc = stat(file, &stat_buf);
    if (rc == 0) {
        pFile = fopen (file,"rt");
        if (pFile != NULL) {
            buffer = (char *) malloc(stat_buf.st_size + 1);
            size = fread(buffer,1, stat_buf.st_size, pFile);
            if (size != stat_buf.st_size) rc = -1;
            buffer[stat_buf.st_size] = 0x0;
        } else {
            rc = -1;
        }
     }
     if (pFile) fclose(pFile);
     if (rc != 0) throw new exception("File not found ");
     return buffer;
}
unordered_map<string, string> processIniConfigFile(char *file) {
   unordered_map<string, string> values;
   string line; 
   vector<string> cmt;
   vector<string> pair;
   char *key;
   char *value;
   char *buffer = loadIniFile(file);
   vector<string> lines = tokenize(buffer, (char *) "\r[\n]?");
   for (string line : lines) {
        cmt  = tokenize(line.c_str(), "#");
        pair = tokenize(cmt[0].c_str(), "=");
        if (pair.size() != 2) continue;
        key   = trim((char *) pair[0].c_str());
        value = trim((char *) pair[1].c_str());
        values.emplace(key, value);
   }   
   free(buffer);
   return values;
}

}