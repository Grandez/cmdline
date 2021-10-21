#include <iostream>

#include "cmdline.h"

using namespace std;

std::vector<cmdline::ParmItem> flags = {
	cmdline::ParmItem("verbose", true)
};

cmdline::CmdLine cmdLine(flags);

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
	title("--help");
	try {
		cmdLine.parse(argc, argv);
		return resko();
	}
	catch (cmdline::HelpRequested ex) {
		return resok();
	}
}
bool case03(int argc, char* argv[]) {
	title("verbose");
	try {
		cmdLine.parse(argc, argv);
		if (!cmdLine.hasFlag("verbose")) throw invalid_argument("error");
		return resok();
	}
	catch (exception ex) {
		return resko();
	}
}

int main(int argc, char *argv[]) {
	const char* argv2[10];
	std::cout << "Begin" << std::endl;
	argv2[1] = "-h";
	if (case01(2, (char**)argv2)) return 1;
	argv2[1] = "--help";
	if (case02(2, (char**)argv2)) return 1;
	argv2[1] = "+verbose";
	if (case03(2, (char**)argv2)) return 1;
	return 0;
}
