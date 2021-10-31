#include "pch.h"

#include "_global.hpp"
TEST(Types, STRING) {
	tool.reset();
	const char* opt = "opt";

	Parameters  parms = { ParmOption((const char*)"opt", (const char*)"123", Type::STRING) };
	CmdLine cmdline = CmdLine::getInstance(tool.argc, tool.argv, parms);
	string res = cmdline.getOptionAs<CMD_STRING>((const char*)"opt");
	EXPECT_EQ(res, "123");
	CmdLine::freeInstance();
}
TEST(Types, string) {
	tool.reset();
	const char* opt = "opt";

	Parameters  parms = { ParmOption((const char*)"opt", (const char*)"123", Type::STRING) };
	CmdLine cmdline = CmdLine::getInstance(tool.argc, tool.argv, parms);
	string res = cmdline.getOptionAs<string>((const char*)"opt");
	EXPECT_EQ(res, "123");
	CmdLine::freeInstance();
}
TEST(Types, char) {
	tool.reset();
	const char* opt = "opt";

	Parameters  parms = { ParmOption((const char*)"opt", (const char*)"123", Type::STRING) };
	CmdLine cmdline = CmdLine::getInstance(tool.argc, tool.argv, parms);
	char * res = cmdline.getOptionAs<char *>((const char*)"opt");
	EXPECT_EQ(strcmp(res, "123"), 0);
	CmdLine::freeInstance();
}
TEST(Types, NUMBER) {
	tool.reset();
	const char* opt = "opt";

	Parameters  parms = { ParmOption((const char *)"opt", (const char*)"123", Type::NUMBER)};
	CmdLine cmdline = CmdLine::getInstance(tool.argc, tool.argv, parms);
	long res = cmdline.getOptionAs<CMD_NUMBER>((const char*)"opt");
	EXPECT_EQ(res,123);
	CmdLine::freeInstance();
}
TEST(Types, LONG) {
	tool.reset();
	const char* opt = "opt";

	Parameters  parms = { ParmOption((const char*)"opt", (const char*)"123", Type::NUMBER) };
	CmdLine cmdline = CmdLine::getInstance(tool.argc, tool.argv, parms);
	long res = cmdline.getOptionAs<CMD_LONG>((const char*)"opt");
	EXPECT_EQ(res, 123);
	CmdLine::freeInstance();
}
TEST(Types, INT) {
	tool.reset();
	const char* opt = "opt";

	Parameters  parms = { ParmOption((const char*)"opt", (const char*)"123", Type::NUMBER) };
	CmdLine cmdline = CmdLine::getInstance(tool.argc, tool.argv, parms);
	int res = cmdline.getOptionAs<CMD_INT>((const char*)"opt");
	EXPECT_EQ(res, 123);
	CmdLine::freeInstance();
}
TEST(Types, long) {
	tool.reset();
	const char* opt = "opt";

	Parameters  parms = { ParmOption((const char*)"opt", (const char*)"123", Type::NUMBER) };
	CmdLine cmdline = CmdLine::getInstance(tool.argc, tool.argv, parms);
	long res = cmdline.getOptionAs<long>((const char*)"opt");
	EXPECT_EQ(res, 123);
	CmdLine::freeInstance();
}
TEST(Types, int) {
	tool.reset();
	const char* opt = "opt";

	Parameters  parms = { ParmOption((const char*)"opt", (const char*)"123", Type::NUMBER) };
	CmdLine cmdline = CmdLine::getInstance(tool.argc, tool.argv, parms);
	int res = cmdline.getOptionAs<long>((const char*)"opt");
	EXPECT_EQ(res, 123);
	CmdLine::freeInstance();
}
TEST(Types, DECIMAL) {
	tool.reset();
	const char* opt = "opt";

	Parameters  parms = { ParmOption((const char*)"opt", (const char*)"123.456", Type::DECIMAL) };
	CmdLine cmdline = CmdLine::getInstance(tool.argc, tool.argv, parms);
	double res = cmdline.getOptionAs<CMD_DECIMAL>((const char*)"opt");
	EXPECT_DOUBLE_EQ(res, 123.456f);
	CmdLine::freeInstance();
}
TEST(Types, FLOAT) {
	tool.reset();
	const char* opt = "opt";

	Parameters  parms = { ParmOption((const char*)"opt", (const char*)"123.456", Type::DECIMAL) };
	CmdLine cmdline = CmdLine::getInstance(tool.argc, tool.argv, parms);
	float res = cmdline.getOptionAs<CMD_FLOAT>((const char*)"opt");
	EXPECT_FLOAT_EQ(res, 123.456f);
	CmdLine::freeInstance();
}
TEST(Types, float) {
	tool.reset();
	const char* opt = "opt";

	Parameters  parms = { ParmOption((const char*)"opt", (const char*)"123.456", Type::DECIMAL) };
	CmdLine cmdline = CmdLine::getInstance(tool.argc, tool.argv, parms);
	float res = cmdline.getOptionAs<float>((const char*)"opt");
	EXPECT_FLOAT_EQ(res, 123.456f);
	CmdLine::freeInstance();
}
TEST(Types, DATE) {
	std::locale::global(std::locale("es_ES.utf8"));
	tool.reset();
	const char* opt = "opt";

	Parameters  parms = { ParmOption((const char*)"opt", (const char*)"01/02/2021", Type::DATE) };
	CmdLine cmdline = CmdLine::getInstance(tool.argc, tool.argv, parms);
	struct tm res = cmdline.getOptionAs<CMD_DATE>((const char*)"opt");
	EXPECT_EQ(res.tm_mday, 2);
	CmdLine::freeInstance();
	std::locale::global(std::locale());
}
TEST(Types, TIME) {
	std::locale::global(std::locale("es_ES.utf8"));
	tool.reset();
	const char* opt = "opt";

	Parameters  parms = { ParmOption((const char*)"opt", (const char*)"01:02:03", Type::TIME) };
	CmdLine cmdline = CmdLine::getInstance(tool.argc, tool.argv, parms);
	struct tm res = cmdline.getOptionAs<CMD_TIME>((const char*)"opt");
	EXPECT_EQ(res.tm_min, 2);
	CmdLine::freeInstance();
	std::locale::global(std::locale());
}
TEST(Types, DATETIME) {
	std::locale::global(std::locale("es_ES.utf8"));
	tool.reset();
	const char* opt = "opt";

	Parameters  parms = { ParmOption((const char*)"opt", (const char*)"2021-10-11 01:02:03", Type::DATETIME) };
	CmdLine cmdline = CmdLine::getInstance(tool.argc, tool.argv, parms);
	struct tm res = cmdline.getOptionAs<CMD_DATETIME>((const char*)"opt");
	EXPECT_EQ(res.tm_min, 2);
	EXPECT_EQ(res.tm_mon, 9);
	CmdLine::freeInstance();
	std::locale::global(std::locale());
}

TEST(Types, TMS) {
	std::locale::global(std::locale("es_ES.utf8"));
	tool.reset();
	const char* opt = "opt";

	Parameters  parms = { ParmOption((const char*)"opt", (const char*)"2021-10-11 01:02:03.456", Type::TMS) };
	CmdLine cmdline = CmdLine::getInstance(tool.argc, tool.argv, parms);
	char *tms = cmdline.getOptionAs<CMD_TMS>((const char*)"opt");
	struct tm res;
	EXPECT_EQ(res.tm_min, 2);
	EXPECT_EQ(res.tm_mon, 9);
	CmdLine::freeInstance();
	std::locale::global(std::locale());
}
