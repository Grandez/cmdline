#include <iostream>

#include "cmdline.hpp"

using namespace cmdline;

Parameters  parms = { 
    ParmFlag("verbose",  true)  // Show progress
   ,ParmFlag("summary",  true)  // Show summary
   ,ParmFlag("overwrite")       // Not overwrite files
   ,ParmOption("input", Type::DIR_EXISTS,true)       // Input directories
   ,ParmOption("output", Type::DIR, false)       // Output directory
   ,ParmOption("ext", Type::STRING, true)              // Extension
   ,ParmOption("pattern", Type::STRING, true)              // regexp for name
};

void showHelpSimple(HelpRequested& help) {
    string flags("[?verbose] [?summary] [?overwrite]");
    string options("[/input list] [/output dir] [/ext pattern_list] [/pattern pattern_list]");
    cout << "A sample program about use parameters" << endl;
    cout << "Use: " << help.name << flags << " " << options << endl;
}
void showHelpDetail(HelpRequested& help) {
}
void showHelp(HelpRequested& help) {
    (help.detailed) ? showHelpDetail(help) : showHelpSimple(help);
}


int main(int argc, char **argv) {
    CmdLine *cmdline = nullptr;
    try {
       cmdline = CmdLine::getInstance(argc, argv,parms);
    }
    catch (HelpRequested help) { showHelp(help); } 
    catch (CmdLineException ex) {
    }

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
