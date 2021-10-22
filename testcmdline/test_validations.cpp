#include "pch.h"
#include <stdexcept>
#include <regex>

#include "../cmdline/validations.h"
#include "../cmdline/cmdline_exceptions.hpp"

using namespace cmdline;
TEST(Validations, Hours) {
	EXPECT_NO_THROW(validateTime("1 1 1"));
	EXPECT_NO_THROW(validateTime("10:00:00"));


	EXPECT_THROW(validateTime("1:1:1"), CmdLineValueException);
}
TEST(Validations, Numbers) {
	EXPECT_THROW(validateNumber("p")       , CmdLineValueException);
	EXPECT_THROW(validateNumber("23:12:32"), CmdLineValueException);
	EXPECT_NO_THROW(validateNumber("1")); 
	EXPECT_NO_THROW(validateNumber("0xff"));
//	EXPECT_EQ(1, 1);
//	EXPECT_TRUE(true);
}
TEST(Validations, Decimals) {
	setlocale(LC_ALL, "spanish");  // OJO!!!!!!!!!!!!!!!!!!!!!!!!!!!!
	EXPECT_THROW(validateDecimal("p")       , CmdLineValueException);
	EXPECT_THROW(validateDecimal("23:12:32"), CmdLineValueException);
	EXPECT_THROW(validateDecimal("1.0")     , CmdLineValueException);
	EXPECT_NO_THROW(validateDecimal("1"));
	EXPECT_NO_THROW(validateDecimal("1,0"));
	setlocale(LC_ALL, "");
}
