#include <iostream>
#include <memory>
#include "../cmdline/cmdline.h"
#include "../cmdline/hashmap.hpp"
#include "../cmdline/parmitem.hpp"

#include "../cmdline/tools.h"
using namespace std;
using namespace cmdline;

std::vector<cmdline::ParmItem> flags = {
	 cmdline::ParmItem("output", true)
	,cmdline::ParmItem("outer", true)
};

void printTitle(string txt) {
	char title[41];
	memset(title, ' ', 40);
	title[40] = 0x0;
	memcpy(title, &(txt[0]), txt.length());
	cout << title;
}
bool printRC(bool res) {
	std::string t = (res) ? "OK" : "KO";
	std::cout << "\t" << t << std::endl;
	return res;
}
bool testSplitParameter(string title, char *value, int expected) {
	std::vector<std::string> res;
	bool rc = false;
	bool rc2 = false;

	printTitle(title);
	res = splitParameter(value);
	rc |=  printRC(res.size() == expected);
	return rc;
}
bool testTextInput() {
	bool rc = false;
	std::cout << "Testing text input" << std::endl;

	rc |= testSplitParameter("Un parametro",   (char*)"test1"             , 1);
	rc |= testSplitParameter("Dos parametros", (char*)"test1,test2"       , 2);
	return rc;
}

bool failingGoogleTest() {
	bool rc = false;
	std::cout << "estos test fallan en google test" << std::endl;
	rc |= testTextInput();
	return rc;
}

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
	unordered_map<string, bool> mflags = cmdLine.getDefaultFlags();
	if (mflags.size() == flags.size()) return resok();

	return resko();
}

int main(int argc, char *argv[]) {
	bool rc = false;
	cout << "Starting\n";

	rc |= failingGoogleTest();
	/*
	char data[] = "test1,test2";
	std::vector<std::string> res = splitParameter(data);
	char* argv2[10];
	std::cout << "Begin" << std::endl;
	argv2[1] = (char*) "default flags";
	cmdline::CmdLine cmdLine(flags);
	
	HashMap<std::string> *hmap = new HashMap<std::string>();
	cmdline::ParmItem item1 = cmdline::ParmItem("pepe2");

	hmap->insert(item1.name, std::make_unique<ParmItem>(item1));
	
	checkDefaultFlags(flags, 2, argv2);

	argv2[1] = (char*)"+o";
	if (testFlagInvalid(flags, 2, (char**)argv2)) return 1;

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
