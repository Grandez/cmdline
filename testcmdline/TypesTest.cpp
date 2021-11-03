#include "pch.h"

#include "$tool.hpp"

TEST(Types, STRING) {
	tool.reset();
	const char* opt = "opt";

	Parameters  parms = { ParmOption(opt, (const char*)"123", Type::STRING) };
	CmdLine cmdline = CmdLine(tool.argc, tool.argv, parms);
	string res = cmdline.getOptionAs<TYPE_STRING>(opt);
	CmdLine::freeInstance();
	EXPECT_EQ(res, "123");
}
TEST(Types, string) {
	tool.reset();
	const char* opt = "opt";

	Parameters  parms = { ParmOption(opt, (const char*)"123", Type::STRING) };
	CmdLine cmdline = CmdLine(tool.argc, tool.argv, parms);
	string res = cmdline.getOptionAs<string>(opt);
	EXPECT_EQ(res, "123");
}
TEST(Types, char) {
	tool.reset();
	const char* opt = "opt";

	Parameters  parms = { ParmOption(opt, (const char*)"123", Type::STRING) };
	CmdLine cmdline = CmdLine(tool.argc, tool.argv, parms);
	char * res = cmdline.getOptionAs<char *>(opt);
	EXPECT_EQ(strcmp(res, "123"), 0);
}
TEST(Types, NUMBER) {
	tool.reset();
	const char* opt = "opt";

	Parameters  parms = { ParmOption(opt, (const char*)"123", Type::NUMBER)};
	CmdLine cmdline = CmdLine(tool.argc, tool.argv, parms);
	long res = cmdline.getOptionAs<TYPE_NUMBER>(opt);
	EXPECT_EQ(res, 123);
}
TEST(Types, LONG) {
	tool.reset();
	const char* opt = "opt";

	Parameters  parms = { ParmOption(opt, (const char*)"123", Type::NUMBER) };
	CmdLine cmdline = CmdLine(tool.argc, tool.argv, parms);
	long res = cmdline.getOptionAs<TYPE_LONG>(opt);
	EXPECT_EQ(res, 123);
}
TEST(Types, INT) {
	tool.reset();
	const char* opt = "opt";

	Parameters  parms = { ParmOption(opt, (const char*)"123", Type::NUMBER) };
	CmdLine cmdline = CmdLine(tool.argc, tool.argv, parms);
	int res = cmdline.getOptionAs<TYPE_INT>(opt);
	EXPECT_EQ(res, 123);
}
TEST(Types, long) {
	tool.reset();
	const char* opt = "opt";

	Parameters  parms = { ParmOption((const char*)"opt", (const char*)"123", Type::NUMBER) };
	CmdLine cmdline = CmdLine(tool.argc, tool.argv, parms);
	long res = cmdline.getOptionAs<long>(opt);
	EXPECT_EQ(res, 123);
}
TEST(Types, int) {
	tool.reset();
	const char* opt = "opt";

	Parameters  parms = { ParmOption(opt, (const char*)"123", Type::NUMBER) };
	CmdLine cmdline = CmdLine(tool.argc, tool.argv, parms);
	int res = cmdline.getOptionAs<long>(opt);
	EXPECT_EQ(res, 123);
}
TEST(Types, DECIMAL) {
	tool.reset();
	const char* opt = "opt";

	Parameters  parms = { ParmOption(opt, (const char*)"123.456", Type::DECIMAL) };
	CmdLine cmdline = CmdLine(tool.argc, tool.argv, parms);
	double res = cmdline.getOptionAs<TYPE_DECIMAL>("opt");
	EXPECT_DOUBLE_EQ(res, 123.456f);
}
TEST(Types, FLOAT) {
	tool.reset();
	const char* opt = "opt";

	Parameters  parms = { ParmOption((const char*)"opt", (const char*)"123.456", Type::DECIMAL) };
	CmdLine cmdline = CmdLine(tool.argc, tool.argv, parms);
	float res = cmdline.getOptionAs<TYPE_FLOAT>((const char*)"opt");
	EXPECT_FLOAT_EQ(res, 123.456f);
}
TEST(Types, float) {
	tool.reset();
	const char* opt = "opt";

	Parameters  parms = { ParmOption((const char*)"opt", (const char*)"123.456", Type::DECIMAL) };
	CmdLine cmdline = CmdLine(tool.argc, tool.argv, parms);
	float res = cmdline.getOptionAs<float>((const char*)"opt");
	EXPECT_FLOAT_EQ(res, 123.456f);
}
TEST(Types, DATE) {
	std::locale::global(std::locale("es_ES.utf8"));
	tool.reset();
	const char* opt = "opt";

	Parameters  parms = { ParmOption((const char*)"opt", (const char*)"01/02/2021", Type::DATE) };
	CmdLine cmdline = CmdLine(tool.argc, tool.argv, parms);
	struct tm res = cmdline.getOptionAs<TYPE_DATE>((const char*)"opt");
	std::locale::global(std::locale());
	EXPECT_EQ(res.tm_mday, 1);
}
TEST(Types, TIME) {
	std::locale::global(std::locale("es_ES.utf8"));
	tool.reset();
	const char* opt = "opt";

	Parameters  parms = { ParmOption((const char*)"opt", (const char*)"01:02:03", Type::TIME) };
	CmdLine cmdline = CmdLine(tool.argc, tool.argv, parms);
	struct tm res = cmdline.getOptionAs<TYPE_TIME>((const char*)"opt");
	std::locale::global(std::locale());
	EXPECT_EQ(res.tm_min, 2);
}
TEST(Types, DATETIME) {
	tool.reset();
	const char* opt = "opt";

	Parameters  parms = { ParmOption((const char*)"opt", (const char*)"2021-10-11 01:02:03", Type::DATETIME) };
	CmdLine cmdline = CmdLine(tool.argc, tool.argv, parms);
	struct tm res = cmdline.getOptionAs<TYPE_DATETIME>((const char*)"opt");
	EXPECT_EQ(res.tm_min, 2);
	EXPECT_EQ(res.tm_mon, 9);
}

TEST(Types, TMS) {
	tool.reset();
	const char* opt = "opt";

	Parameters  parms = { ParmOption((const char*)"opt", (const char*)"2021-10-11 01:02:03.456", Type::TMS) };
	CmdLine cmdline = CmdLine::getInstance(tool.argc, tool.argv, parms);
	char *tms = cmdline.getOptionAs<TYPE_TMS>((const char*)"opt");
	CmdLine::freeInstance();
	EXPECT_GT((int) strlen(tms), 20);
}
