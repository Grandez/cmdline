#include <iostream>

#include "../cmdline/include/cmdline.hpp"

using namespace std;
using namespace cmdline;

/*
bool checkFlag() {
	const char* argv2[10] = { (char*)"drivercpp"
	, (char*)"/def1=definition1"
	};
	char** argv = &argv2;
	bool rc = false;
	std::cout << "Starting\n";

	Parameters iflags = {
	 ParmFlag("verbose")
	};
	CmdLine cmdLine = CmdLine::getInstance(2, argv, iflags);
	return !cmdLine.hasFlag("verbose");

}
*/
int main(int argc, const char* argv[]) {
	const char* opt = "opt";
	char* argv2[] = { (char *) "test" };

	Parameters  parms = { ParmOption((const char*)"opt", (const char*)"123", Type::NUMBER) };

	CmdLine cmdline = CmdLine::getInstance(1, argv2, parms);


	int res = cmdline.getOptionAs<TYPE_INT>((const char*)"opt");

	bool rc = false;
	std::cout << "Starting\n";
//	rc |= checkFlag();
	std::cout << "End\n";
	return (rc ? 1 : 0);
}

/*
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
*/
