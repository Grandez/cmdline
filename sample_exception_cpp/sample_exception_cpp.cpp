
#define __MAIN__

#include "config.hpp"
#include "showinfo.hpp"

Parameters  parms { 
    ParmFlag(VERBOSE,  true)                    
   ,ParmFlag(SUMMARY,  true)                     
   ,ParmOption(FLAG,  "true", Type::BOOL,    false)
   ,ParmOption(NUMBERS,   Type::NUMBER,      true) 
   ,ParmOption(NUMBER,    Type::NUMBER,      false)
   ,ParmOption(DECIMALS,  Type::DECIMAL,     true) 
   ,ParmOption(DECIMAL,   Type::DECIMAL,     false)
   ,ParmOption(DATE,      Type::DATE,        false)
   ,ParmOption(TIME,      Type::TIME,        false)
   ,ParmOption(DATETIME,  Type::DATETIME,    false)
   ,ParmOption(TIMESTAMP, Type::TMS,         false)
   ,ParmOption(DIRIN,     Type::DIR_EXISTS,  true) 
   ,ParmOption(DIROUT,    Type::DIR,         false)
   ,ParmOption(FILEIN,    Type::FILE_EXISTS, true) 
   ,ParmOption(FILEOUT,   Type::FILE,        false) 
   ,ParmOption(CONFIG,    Type::CONFIG,      false) 
};

int main(int argc, char *argv[]) {
    cout << "Starting " << argv[0] << endl;
    try {
       cmdLine = CmdLine::getInstance(argc, argv,parms);
    }
    catch (HelpRequested *help) { 
        showHelp(help); 
    } 
    catch (CmdLineException *ex) {
        cerr << ex->what() << endl;
        cerr << "Exception type: " << ex->type << endl;
        exit(1);
    }

}
