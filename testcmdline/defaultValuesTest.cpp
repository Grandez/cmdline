#include "pch.h"
/**
 * @file defaultValues.cpp
 * @author Grandez
 * @date 9 Sep 2012
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
	Parameters  parms = {
		ParmOption("output", Type::DATE)
	};
	CmdLine cmdline = CmdLine(tool.argc, tool.argv, parms);
	struct tm date = cmdline.getOptionAs<TYPE_DATE>((const char *)"output");
	EXPECT_EQ(date.tm_year, tool.now.tm_year);
}
TEST(DefValues, TypeDateTime) {
	Parameters  parms = {
		ParmOption("output", Type::DATETIME)
	};
	CmdLine cmdline = CmdLine(tool.argc, tool.argv, parms);
	struct tm date = cmdline.getOptionAs<TYPE_DATE>((const char*)"output");
	EXPECT_EQ(date.tm_hour, tool.now.tm_hour);
	EXPECT_EQ(date.tm_year, tool.now.tm_year);
}
TEST(DefValues, TypeTime) {
	Parameters  parms = {
		ParmOption("output", Type::TIME)
	};
	CmdLine cmdline = CmdLine(tool.argc, tool.argv, parms);
	struct tm date = cmdline.getOptionAs<TYPE_DATE>((const char*)"output");
	EXPECT_EQ(date.tm_hour, tool.now.tm_hour);
}
TEST(DefValues, TypeBoolean) {
	Parameters  parms = {
		ParmOption("output", Type::BOOL)
	};
	CmdLine cmdline = CmdLine(tool.argc, tool.argv, parms);
	bool opt = cmdline.getOptionAs<TYPE_BOOL>((const char*)"output");

	EXPECT_FALSE(opt);
}
TEST(DefValues, TypeString) {
	Parameters  parms = {
		ParmOption("output", Type::STRING)
	};
	CmdLine cmdline = CmdLine(tool.argc, tool.argv, parms);
	string opt = cmdline.getOptionAs<TYPE_STRING>((const char*)"output");
	EXPECT_EQ(opt.length(), 0);
}
