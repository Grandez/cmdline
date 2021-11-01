#include "pch.h"
#include <stdexcept>

#include "_global.hpp"

TEST(DefaultValuesExceptions, date) {
	tool.reset();
	Parameters  parms = { ParmOption("opt", "pepe", Type::DATE) };
	CmdLine cmdline;
	EXPECT_THROW(CmdLine::getInstance(tool.argc, tool.argv, parms), CmdLineValueException);
	CmdLine::freeInstance();
}
TEST(DefaultValuesExceptions, time) {
	tool.reset();
	Parameters  parms = { ParmOption("opt", "pepe", Type::TIME) };
	CmdLine cmdline;
	EXPECT_THROW(CmdLine::getInstance(tool.argc, tool.argv, parms), CmdLineValueException);
	CmdLine::freeInstance();
}
TEST(DefaultValuesExceptions, datetime) {
	tool.reset();
	Parameters  parms = { ParmOption("opt", "pepe", Type::DATETIME) };
	CmdLine cmdline;
	EXPECT_THROW(CmdLine::getInstance(tool.argc, tool.argv, parms), CmdLineValueException);
	CmdLine::freeInstance();
}
TEST(DefaultValuesExceptions, timestamp) {
	tool.reset();
	Parameters  parms = { ParmOption("opt", "pepe", Type::TMS) };
	CmdLine cmdline;
	EXPECT_THROW(CmdLine::getInstance(tool.argc, tool.argv, parms), CmdLineValueException);
	CmdLine::freeInstance();
}
TEST(DefaultValuesExceptions, number) {
	tool.reset();
	Parameters  parms = { ParmOption("opt", "pepe", Type::NUMBER) };
	CmdLine cmdline;
	EXPECT_THROW(CmdLine::getInstance(tool.argc, tool.argv, parms), CmdLineValueException);
	CmdLine::freeInstance();
}
TEST(DefaultValuesExceptions, decimal) {
	tool.reset();
	Parameters  parms = { ParmOption("opt", "pepe", Type::DECIMAL) };
	CmdLine cmdline;
	EXPECT_THROW(CmdLine::getInstance(tool.argc, tool.argv, parms), CmdLineValueException);
	CmdLine::freeInstance();
}
TEST(DefaultValuesExceptions, long_number) {
	tool.reset();
	Parameters  parms = { ParmOption("opt", "pepe", Type::LONGNUMBER) };
	CmdLine cmdline;
	EXPECT_THROW(CmdLine::getInstance(tool.argc, tool.argv, parms), CmdLineValueException);
	CmdLine::freeInstance();
}
TEST(DefaultValuesExceptions, long_decimal) {
	tool.reset();
	Parameters  parms = { ParmOption("opt", "pepe", Type::LONGDECIMAL) };
	CmdLine cmdline;
	EXPECT_THROW(CmdLine::getInstance(tool.argc, tool.argv, parms), CmdLineValueException);
	CmdLine::freeInstance();
}