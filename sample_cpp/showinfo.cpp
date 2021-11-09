#include <iostream>

#include "config.hpp"
#include "showinfo.hpp"

using namespace std;

void showHelpSimple(HelpRequested* help) {
    string flags("[?verbose] [?summary] [?overwrite]");
    string options("[/input list] [/output dir] [/ext pattern_list] [/pattern pattern_list]");
    cout << "A sample program about use parameters" << endl;
    cout << "Use: " << help->name << " " << flags << " " << options << endl;
}
void showHelpDetail(HelpRequested* help) {
    showHelpSimple(help);
    cout << "\t" << VERBOSE   << ":\t Show progress information. Default: " 
                              << std::boolalpha << help->flags.at(VERBOSE) << endl;
    cout << "\t" << SUMMARY   << ":\t Print summary info after process. Default: " 
                              << std::boolalpha << help->flags.at(SUMMARY) << endl;
    cout << "\t" << OVERWRITE << ":\t Overwrite existing file?. Default: " 
                              << std::boolalpha << help->flags.at("overwrite") << endl;
    cout << "\t" << CONFIG    << ":\t\t Configutaion file. Default: None" << endl;
    cout << "\t" << INPUT     << ":\t\t Input directories. Default: " 
                              << help->options.at(INPUT) << endl;
    cout << "\t" << OUTPUT    << ":\t\t Output directory. Default: " 
                              << help->options.at(OUTPUT) << endl;
    cout << "\t" << PATTERN   << ":\t Pattern for file names. Default: (All) " 
                              << help->options.at(PATTERN) << endl;
    cout << "\t" << EXT       << ": \t\t Pattern for extensions. Default: (All) " 
                              << help->options.at(EXT) << endl;
//    delete help;
}
void showHelp(HelpRequested *help) {
    (help->detailed) ? showHelpDetail(help) : showHelpSimple(help);
}
void printOption(Options& options, string option) {
   int num = 0;
   vector<string> values = options.at(option);

   cout << option << ":\t "; 
   for (auto str : values) {
        if (num) cout << ", ";
        cout << str;
        num++;
   }
   cout << endl;
}
void showCurrentConfig() {
    Flags   flags   = cmdLine->getCurrentFlags();
    Options options = cmdLine->getCurrentOptions();
    Options defs    = cmdLine->getDefinitions();

    cout << "Starting process ..." << endl;  

    cout << VERBOSE   << ": " << std::boolalpha << flags.at(VERBOSE)   << endl;
    cout << SUMMARY   << ": " << std::boolalpha << flags.at(SUMMARY)   << endl;
    cout << OVERWRITE << ": " << std::boolalpha << flags.at(OVERWRITE) << endl;
    
    printOption(options, CONFIG);
    printOption(options, INPUT);
    printOption(options, OUTPUT);
    printOption(options, PATTERN);
    printOption(options, EXT);

    if (defs.size() == 0) {
        cout << "There is not any definition" << endl;
    }

}

void showSummary() {
}
