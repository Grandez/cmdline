/**
 * @file exceptionsValuesTest.cpp
 * @author Grandez
 * @date   09/2021
 * @brief Test invalid data passed in command line
 *
 * Type of parameter is defined in design time
 */

#include "pch.h"
#include <stdexcept>
#include <fstream>

#include "$tool.hpp"

TEST(ValuesExceptions, date) {
	tool.reset();
	Parameters  parms = { ParmOption("opt", Type::DATE) };
	tool.addArg("/opt", "nothing");
	EXPECT_THROW(CmdLine(tool.argc, tool.argv, parms), CmdLineValueException);
}
TEST(ValuesExceptions, time) {
	tool.reset();
	Parameters  parms = { ParmOption("opt", Type::TIME) };
	tool.addArg("/opt", "nothing");
	EXPECT_THROW(CmdLine(tool.argc, tool.argv, parms), CmdLineValueException);
}
TEST(ValuesExceptions, datetime) {
	tool.reset();
	Parameters  parms = { ParmOption("opt", Type::DATETIME) };
	tool.addArg("/opt", "nothing");
	EXPECT_THROW(CmdLine(tool.argc, tool.argv, parms), CmdLineValueException);
}
TEST(ValuesExceptions, timestamp) {
	tool.reset();
	Parameters  parms = { ParmOption("opt", Type::TMS) };
	tool.addArg("/opt", "nothing");
	EXPECT_THROW(CmdLine(tool.argc, tool.argv, parms), CmdLineValueException);
}
TEST(ValuesExceptions, number) {
	tool.reset();
	Parameters  parms = { ParmOption("opt", Type::NUMBER) };
	tool.addArg("/opt", "nothing");
	EXPECT_THROW(CmdLine(tool.argc, tool.argv, parms), CmdLineValueException);
}
TEST(ValuesExceptions, longnumber) {
	tool.reset();
	Parameters  parms = { ParmOption("opt", Type::LONGNUMBER) };
	tool.addArg("/opt", "nothing");
	EXPECT_THROW(CmdLine(tool.argc, tool.argv, parms), CmdLineValueException);
}
TEST(ValuesExceptions, Decimal) {
	tool.reset();
	Parameters  parms = { ParmOption("opt", Type::DECIMAL) };
	tool.addArg("/opt", "nothing");
	EXPECT_THROW(CmdLine(tool.argc, tool.argv, parms), CmdLineValueException);
}
TEST(ValuesExceptions, LongDecimal) {
	tool.reset();
	Parameters  parms = { ParmOption("opt", Type::LONGDECIMAL) };
	tool.addArg("/opt", "nothing");
	EXPECT_THROW(CmdLine(tool.argc, tool.argv, parms), CmdLineValueException);
}
TEST(ValuesExceptions, FileExists) {
	tool.reset();
	char aux[128] = "xxx";
	int size = 3;
	// Find a file name erroenous
	ifstream f(aux);
	while (f.good()) {
		aux[size++] = 'x';
		aux[size] = 0x0;
		f = ifstream(aux);
	}
	Parameters  parms = { ParmOption("opt", Type::FILE_EXISTS) };
	tool.addArg("/opt", "aux");
	EXPECT_THROW(CmdLine(tool.argc, tool.argv, parms), CmdLineValueException);
}
TEST(ValuesExceptions, DirExists) {
	tool.reset();
#ifdef _WIN32
	char path[128] = "c:\\xxx";
	char sep = '\\';
	int size = 6;
#else
	char path[128] = "/xxx";
	char sep = '/';
	int size = 4;
#endif
	bool exists = true;
	struct stat info;
	// Find a directory name erroenous
	do {
		if (stat(path, &info) != 0) {
			exists = false;
		}
		else {
			if ((info.st_mode & S_IFDIR) == 0) exists = false;
		}
		if (exists) {
			path[size++] = sep;
			memcpy(&(path[size]), "xxx", 3);
			path[size + 3] = 0x0;
			size += 3;
		}
	} while (exists);
	
	Parameters  parms = { ParmOption("opt", Type::DIR_EXISTS) };
	tool.addArg("/opt", path);
	EXPECT_THROW(CmdLine(tool.argc, tool.argv, parms), CmdLineValueException);
}


