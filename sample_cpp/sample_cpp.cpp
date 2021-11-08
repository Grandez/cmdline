// #define _CRTDBG_MAP_ALLOC
#include <iostream>
#include <stdlib.h>

#define __MAIN__

#include "config.hpp"

// CmdLine *cmdLine = nullptr;

#include "showinfo.hpp"

//#include <crtdbg.h>
// #include <vld.h>

Parameters  parms { 
    ParmFlag(VERBOSE,  true)                     // Show progress
   ,ParmFlag(SUMMARY,  true)                     // Show summary
   ,ParmFlag(OVERWRITE)                          // Not overwrite files
   ,ParmOption(INPUT,  Type::DIR_EXISTS,true)    // Input directories
   ,ParmOption(OUTPUT, Type::DIR, false)         // Output directory
   ,ParmOption(PATTERN, "*", Type::STRING, true) // regexp for file name
   ,ParmOption(EXT,     "*", Type::STRING, true) // regexp for extension
};




int main(int argc, char *argv[]) {
  //  _CrtMemState s1, s2, s3;
  //  _CrtSetDbgFlag ( _CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF );
  //  _crtBreakAlloc = 246;
    
    
    try {
        
//_CrtMemCheckpoint( &s1 );

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
//_CrtMemCheckpoint( &s2 );
//if ( _CrtMemDifference( &s3, &s1, &s2) )
//   _CrtMemDumpStatistics( &s3 );
    cout << "Esto seria el final\n";
    CmdLine::destroyInstance(cmdLine);
}
