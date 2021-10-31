#include "pch.h"

#include "_global.hpp"

TEST(Defines, Define_01) {
	tool.reset();
	int argc = tool.addArg("/def1=define1");
	Parameters  parms;
	CmdLine cmdline = CmdLine::getInstance(tool.argc, tool.argv, parms);
	EXPECT_NO_THROW(cmdline.hasDefinition("def1"));
	CmdLine::freeInstance();
}
TEST(Defines, Define_02) {
	tool.reset();
	int argc = tool.addArg("/def1=define1");
	argc = tool.addArg("/def2=define2");
	Parameters  parms;
	CmdLine cmdline = CmdLine::getInstance(tool.argc, tool.argv, parms);
	EXPECT_NO_THROW(cmdline.hasDefinition("def1"));
	EXPECT_NO_THROW(cmdline.hasDefinition("def2"));
	CmdLine::freeInstance();
}
TEST(Defines, Define_03) {
	tool.reset();
	int argc = tool.addArg("/def1=define1");
	argc = tool.addArg("/def1=define2");
	Parameters  parms;
	CmdLine cmdline = CmdLine::getInstance(tool.argc, tool.argv, parms);
	EXPECT_NO_THROW(cmdline.hasDefinition("def1"));
	CmdLine::freeInstance();
}
TEST(Defines, Define_04) {
	tool.reset();
	int argc = tool.addArg("/def1=define1");
	argc = tool.addArg("/def2=define21,define22,define23");
	Parameters  parms;
	CmdLine cmdline = CmdLine::getInstance(tool.argc, tool.argv, parms);
	EXPECT_NO_THROW(cmdline.hasDefinition("def1"));
	EXPECT_NO_THROW(cmdline.hasDefinition("def2"));
	CmdLine::freeInstance();
}
TEST(Defines, Define_05) {
	tool.reset();
	int argc = tool.addArg("/def1=\"define 1\"");
	argc = tool.addArg("/def2=define21,define22,define23");
	Parameters  parms;
	CmdLine cmdline = CmdLine::getInstance(tool.argc, tool.argv, parms);
	EXPECT_NO_THROW(cmdline.hasDefinition("def1"));
	EXPECT_NO_THROW(cmdline.hasDefinition("def2"));
	CmdLine::freeInstance();
}
TEST(Defines, Define_KO_1) {
	tool.reset();
	int argc = tool.addArg("/define1");
	Parameters  parms;
	EXPECT_THROW(CmdLine::getInstance(tool.argc, tool.argv, parms), CmdLineException);
	CmdLine::freeInstance();
}
TEST(Defines, Define_KO_2) {
	tool.reset();
	int argc = tool.addArg("/= define1");
	Parameters  parms;
	EXPECT_THROW(CmdLine::getInstance(tool.argc, tool.argv, parms), CmdLineParameterException);
	CmdLine::freeInstance();
}
TEST(Defines, Define_KO_3) {
	tool.reset();
	int argc = tool.addArg("/def1=define1=define2");
	Parameters  parms;
	EXPECT_THROW(CmdLine::getInstance(tool.argc, tool.argv, parms), CmdLineParameterException);
	CmdLine::freeInstance();
}
TEST(Defines, Vector_1) {
	tool.reset();
	int argc = tool.addArg("/def1=define1");
	Parameters  parms;
	CmdLine cmdline = CmdLine::getInstance(tool.argc, tool.argv, parms);
	EXPECT_EQ(strcmp(cmdline.getDefinition("def1"), "define1"), 0);
	CmdLine::freeInstance();
}
TEST(Defines, Vector_2) {
	tool.reset();
	int argc = tool.addArg("/def1=define1,define2");
	Parameters  parms;
	CmdLine cmdline = CmdLine::getInstance(tool.argc, tool.argv, parms);
	EXPECT_TRUE(cmdline.isDefinitionMultiple("def1"));
	CmdLine::freeInstance();
}
TEST(Defines, Vector_3) {
	tool.reset();
	int argc = tool.addArg("/def1=define1,define2");
	Parameters  parms;
	CmdLine cmdline = CmdLine::getInstance(tool.argc, tool.argv, parms);
	vector<const char*> defs = cmdline.getDefinitionValues("def1");
	EXPECT_EQ(strcmp(defs[0], "define1"), 0);
	CmdLine::freeInstance();
}
