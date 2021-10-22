#include <iostream>

#include "../cmdline/cmdline.h"

using namespace std;

std::vector<cmdline::ParmItem> flags = {
	 cmdline::ParmItem("output", true)
	,cmdline::ParmItem("outer", true)
};


void title(const char* str) { cout << "Testing " << str; }
bool resok(int tabs = 1) {
	for (int i = 0; i < tabs; i++) cout << "\t";
	cout << "OK" << endl;
	return false;
}
bool resko(int tabs = 1) {
	for (int i = 0; i < tabs; i++) cout << "\t";
	cout << "KO" << endl;
	return true;
}

bool case01(int argc, char* argv[]) {
	cmdline::CmdLine cmdLine(flags);
	title("-h");
	try {
		cmdLine.parse(argc, argv);
		return resko();
	}
	catch (cmdline::HelpRequested ex) {
		return resok();
	}
}
bool case02(int argc, char* argv[]) {
	cmdline::CmdLine cmdLine(flags);
	title("--help");
	try {
		cmdLine.parse(argc, argv);
		return resko();
	}
	catch (cmdline::HelpRequested ex) {
		return resok();
	}
}

bool testFlagDetect(std::vector<cmdline::ParmItem>& flags, int argc, char* argv[10]) {
	title(argv[1]);
	cmdline::CmdLine cmdLine(flags);

	try {
		cmdLine.parse(argc, argv);
		if (!cmdLine.hasFlag(argv[0])) throw invalid_argument("error");
		return resok();
	}
	catch (exception ex) {
		return resko();
	}
}
bool testFlagInvalid(std::vector<cmdline::ParmItem>& flags, int argc, char* argv[10]) {
	title(argv[1]);
	cmdline::CmdLine cmdLine(flags);

	try {
		cmdLine.parse(argc, argv);
		return resko();
	}
	catch (exception ex) {
		return resok();
	}
}

bool checkDefaultFlags(std::vector<cmdline::ParmItem>& flags, int argc, char* argv[10]) {
	title(argv[1]);
	cmdline::CmdLine cmdLine(flags);
	map<string, bool> mflags = cmdLine.getDefaultFlags();
	if (mflags.size() == flags.size()) return resok();
	return resko();
}

int main(int argc, char *argv[]) {
	char* argv2[10];
	std::cout << "Begin" << std::endl;
	argv2[1] = (char*) "default flags";

	checkDefaultFlags(flags, 2, argv2);

	argv2[1] = (char*)"+o";
	if (testFlagInvalid(flags, 2, (char**)argv2)) return 1;
/*
	argv2[1] = (char *)  "+v";
	if (testFlagDetect(flags, 2, argv2)) return 1;

	argv2[1] = (char*)"+ver";
	if (testFlagDetect(flags, 2, argv2)) return 1;

	argv2[1] = (char*)"+verbo";
	if (testFlagDetect(flags, 2, argv2)) return 1;

	argv2[1] = (char*)"+verbose";
	if (testFlagDetect(flags, 2, (char**)argv2)) return 1;


	argv2[1] = (char*) "-h";
	if (case01(2, (char**)argv2)) return 1;
	argv2[1] = (char*) "--help";
	if (case02(2, (char**)argv2)) return 1;
	*/
	return 0;
}
