// #define _CRTDBG_MAP_ALLOC
#include <iostream>
#include <stdlib.h>

#define __MAIN__

#include "config.hpp"
#include "showinfo.hpp"

//#include <crtdbg.h>
// #include <vld.h>

Parameters  parms { 
    ParmFlag(VERBOSE,  true)                     // Show progress
   ,ParmFlag(SUMMARY,  true)                     // Show summary
   ,ParmFlag(OVERWRITE)                          // Not overwrite files
   ,ParmOption(CONFIG, Type::CONFIG,true)        // Input directories
   ,ParmOption(INPUT,  Type::DIR_EXISTS,true)    // Input directories
   ,ParmOption(OUTPUT, Type::DIR, false)         // Output directory
   ,ParmOption(PATTERN, "*", Type::STRING, true) // regexp for file name
   ,ParmOption(EXT,     "*", Type::STRING, true) // regexp for extension
};




int main(int argc, char *argv[]) {
    try {
       cmdLine = CmdLine::getInstance(argc, argv,parms);
    }
    catch (HelpRequested *help) { 
        showHelp(help); 
        delete cmdLine;
    } 
    catch (CmdLineException *ex) {
        cerr << ex->what() << endl;
        exit(1);
    }
    
    if (cmdLine->hasFlag(VERBOSE)) showCurrentConfig();

    if (cmdLine->hasFlag(SUMMARY)) showSummary();
    CmdLine::destroyInstance(cmdLine);
}


//_CrtMemCheckpoint( &s2 );
//if ( _CrtMemDifference( &s3, &s1, &s2) )
//   _CrtMemDumpStatistics( &s3 );
