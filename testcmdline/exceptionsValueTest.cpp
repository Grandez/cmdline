#include "pch.h"
#include <stdexcept>

#include "$tool.hpp"

TEST(ValuesExceptions, date) {
	tool.reset();
	Parameters  parms = { ParmOption("opt", "pepe", Type::DATE) };
	CmdLine cmdline;
	EXPECT_THROW(CmdLine::getInstance(tool.argc, tool.argv, parms), CmdLineValueException);
	CmdLine::freeInstance();
}
