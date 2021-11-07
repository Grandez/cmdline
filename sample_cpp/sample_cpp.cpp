#define _CRTDBG_MAP_ALLOC
#include <stdlib.h>
#include <crtdbg.h>
// #include <vld.h>

#include <iostream>

#include "cmdline.hpp"

using namespace cmdline;

void showHelpSimple(HelpRequested* help) {
    string flags("[?verbose] [?summary] [?overwrite]");
    string options("[/input list] [/output dir] [/ext pattern_list] [/pattern pattern_list]");
    cout << "A sample program about use parameters" << endl;
    cout << "Use: " << help->name << " " << flags << " " << options << endl;
    delete help;
}
void showHelpDetail(HelpRequested* help) {
    string flags("[?verbose] [?summary] [?overwrite]");
    string options("[/input list] [/output dir] [/ext pattern_list] [/pattern pattern_list]");
    cout << "A sample program about use parameters" << endl;
    cout << "Use: " << help->name << " " << flags << " " << options << endl;
    cout << "\tverbose:" << "\t show progress information. Default: " << help->flags.at("verbose") << endl;
    cout << "\tsummary:" << "\t Print summary info after process. Default: " << help->flags.at("summary") << endl;
    cout << "\toverwrite:" << "\t Overwrite existing file?. Default: " << help->flags.at("overwrite") << endl;
    delete help;

}
void showHelp(HelpRequested *help) {
    (help->detailed) ? showHelpDetail(help) : showHelpSimple(help);
}

Parameters  parms = { 
    ParmFlag("verbose",  true)  // Show progress
   ,ParmFlag("summary",  true)  // Show summary
   ,ParmFlag("overwrite")       // Not overwrite files
   ,ParmOption("input", Type::DIR_EXISTS,true)       // Input directories
   ,ParmOption("output", Type::DIR, false)       // Output directory
   ,ParmOption("ext", Type::STRING, true)              // Extension
   ,ParmOption("pattern", Type::STRING, true)              // regexp for name
};

int main(int argc, char *argv[]) {
    _CrtMemState s1, s2, s3;
    _CrtSetDbgFlag ( _CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF );
    _crtBreakAlloc = 246;
    {
    CmdLine *cmdline = nullptr;
    try {
        
_CrtMemCheckpoint( &s1 );

       cmdline = CmdLine::getInstance(argc, argv,parms);
    }
    catch (HelpRequested *help) { 
        showHelp(help); 
        delete cmdline;
    } 
    catch (CmdLineException *ex) {
        cout << "error\n";
    }
    }
_CrtMemCheckpoint( &s2 );
if ( _CrtMemDifference( &s3, &s1, &s2) )
   _CrtMemDumpStatistics( &s3 );
    cout << "Esto seria el final\n";
}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
