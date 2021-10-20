#include <iostream>

#include "cmdline.h"

using namespace std;

std::vector<cmdline::ParmItem> flags = {
	cmdline::ParmItem("verbose", true)
};

cmdline::CmdLine cmdLine(flags);

void case01(int argc, char* argv[]) {
	try {
		cmdLine.parse(argc, argv);
	}
	catch (cmdline::HelpRequested ex) {
		cout << "Help" << endl;
	}
}

int main(int argc, char *argv[]) {
	
	std::cout << "Begin" << std::endl;
	std::cout << "Help" ;
	const char* argv2[] = { "program", "-h" };
	case01(2, (char **) argv2);
}
