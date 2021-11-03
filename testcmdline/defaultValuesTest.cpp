#include "pch.h"
/**
 * @file defaultValues.cpp
 * @author Grandez
 * @date   09/2021
 * @brief Test default values for options
 *
 * When NULL:
 *  - date, time,datetime, timestampget current date time
 *  - Directories get current working
 *  - Boolean get false
 * 
 * TEST OF DATE TIMES CAN FAIL BECAUSE CHANGES BETWEEN ESTART AND END
 */
#include "$tool.hpp"

using namespace cmdline;
TEST(DefValues, TypeDate) {
	tool.reset();
	Parameters  parms = {
		ParmOption("output", Type::DATE)
	};
	CmdLine cmdline = CmdLine(tool.argc, tool.argv, parms);
	struct tm date = cmdline.getOptionAs<TYPE_DATE>((const char *)"output");
	EXPECT_EQ(date.tm_year, tool.now.tm_year);
}
TEST(DefValues, TypeDateTime) {
	tool.reset();
	Parameters  parms = {
		ParmOption("output", Type::DATETIME)
	};
	CmdLine cmdline = CmdLine(tool.argc, tool.argv, parms);
	struct tm date = cmdline.getOptionAs<TYPE_DATE>((const char*)"output");
	EXPECT_EQ(date.tm_hour, tool.now.tm_hour);
	EXPECT_EQ(date.tm_year, tool.now.tm_year);
}
TEST(DefValues, TypeTime) {
	tool.reset();
	Parameters  parms = {
		ParmOption("output", Type::TIME)
	};
	CmdLine cmdline = CmdLine(tool.argc, tool.argv, parms);
	struct tm date = cmdline.getOptionAs<TYPE_DATE>((const char*)"output");
	EXPECT_EQ(date.tm_hour, tool.now.tm_hour);
}
TEST(DefValues, TypeString) {
	tool.reset();
	Parameters  parms = {
		ParmOption("output", Type::STRING)
	};
	CmdLine cmdline = CmdLine(tool.argc, tool.argv, parms);
	string opt = cmdline.getOptionAs<TYPE_STRING>((const char*)"output");
	EXPECT_EQ(opt.length(), 0);
}
TEST(DefValues, TypeBool) {
	tool.reset();
	Parameters  parms = {
		ParmOption("output", Type::BOOL)
	};
	CmdLine cmdline = CmdLine(tool.argc, tool.argv, parms);
	bool opt = cmdline.getOptionAs<TYPE_BOOL>((const char*)"output");
	EXPECT_FALSE(opt);
}
TEST(DefValues, TypeTimestamp) {
	tool.reset();
	Parameters  parms = {
		ParmOption("output", Type::TMS)
	};
	CmdLine cmdline = CmdLine(tool.argc, tool.argv, parms);
	const char *opt = cmdline.getOptionAs<TYPE_TMS>((const char*)"output");
	EXPECT_GT(strlen(opt), (size_t) 20);
}
TEST(DefValues, TypeDir) {
	tool.reset();
	Parameters  parms = {
		ParmOption("output", Type::DIR)
	};
	CmdLine cmdline = CmdLine(tool.argc, tool.argv, parms);
	filesystem::path opt = cmdline.getOptionAs<TYPE_DIR>((const char*)"output");
	string s = opt.string();
	EXPECT_GT(s.length(), (size_t) 0);
}
