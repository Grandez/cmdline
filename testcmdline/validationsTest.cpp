#include "pch.h"
#include <stdexcept>
#include <regex>

#include "../cmdline/include/validations.h"
#include "../cmdline/include/cmdline_exceptions.hpp"

using namespace _cmdline;
using namespace cmdline;

TEST(Validations, Times_OK) {
	EXPECT_NO_THROW(validateTime("10:00:00"));
	EXPECT_NO_THROW(validateTime("01:01:01"));
	EXPECT_NO_THROW(validateTime("00:00:00"));
	EXPECT_NO_THROW(validateTime("23:59:59"));
	EXPECT_NO_THROW(validateTime("1:23:45"));
	EXPECT_NO_THROW(validateTime("23:22:0"));
	EXPECT_NO_THROW(validateTime("23:1:59"));
	EXPECT_NO_THROW(validateTime("1:1:1"));
	EXPECT_NO_THROW(validateTime("0:0:0"));
}
TEST(Validations, Times_KO) {
	EXPECT_THROW(validateTime("1 1 1"),    CmdLineValueException);
	EXPECT_THROW(validateTime("24:0:0"),   CmdLineValueException);
	EXPECT_THROW(validateTime("nada"),     CmdLineValueException);
	EXPECT_THROW(validateTime("23:60:0"),  CmdLineValueException);
	EXPECT_THROW(validateTime("0:0:60"),   CmdLineValueException);
	EXPECT_THROW(validateTime("24:-10:0"), CmdLineValueException);
	EXPECT_THROW(validateTime("23/10/05"), CmdLineValueException);
}

TEST(Validations, Dates_OK) {
	std::locale::global(std::locale("es_ES.utf8"));
	EXPECT_NO_THROW(validateDate("1/1/01"));
	EXPECT_NO_THROW(validateDate("01/01/01"));
	EXPECT_NO_THROW(validateDate("01-01-01"));
	EXPECT_NO_THROW(validateDate("29/2/2000"));
	EXPECT_NO_THROW(validateDate("29/02/2000"));
	EXPECT_NO_THROW(validateDate("31/01/2000"));
	EXPECT_NO_THROW(validateDate("28/02/2001"));
	EXPECT_NO_THROW(validateDate("28-02-2001"));
	EXPECT_NO_THROW(validateDate("29-02-2020"));
	EXPECT_NO_THROW(validateDate("31-03-2020"));
	EXPECT_NO_THROW(validateDate("30-11-2020"));
	std::locale::global(std::locale());
}
TEST(Validations, Dates_KO) {
	std::locale::global(std::locale("es_ES.utf8"));
	EXPECT_THROW(validateDate("1 1 01"),     CmdLineValueException);
	EXPECT_THROW(validateDate("31/02/01"),   CmdLineValueException);
	EXPECT_THROW(validateDate("31-4-01"),    CmdLineValueException);
	EXPECT_THROW(validateTime("0/1/2020"),   CmdLineValueException);
	EXPECT_THROW(validateTime("15/13/2020"), CmdLineValueException);
	EXPECT_THROW(validateTime("data"),       CmdLineValueException);
	EXPECT_THROW(validateTime("29/02/2021"), CmdLineValueException);
	std::locale::global(std::locale());
}
TEST(Validations, Datetimes_OK) {
	std::locale::global(std::locale("es_ES.utf8"));
	EXPECT_NO_THROW(validateDateTime("01/1/01 1:1:1"));
	EXPECT_NO_THROW(validateDateTime("01/01/01 10:11:12"));
	EXPECT_NO_THROW(validateDateTime("01-01-01   1:2:34"));
	EXPECT_NO_THROW(validateDateTime("29/2/2000 1:12:3"));
	EXPECT_NO_THROW(validateDateTime("29/02/2000 12:1:1"));
	std::locale::global(std::locale());
}
TEST(Validations, Datetimes_KO) {
	std::locale::global(std::locale("es_ES.utf8"));
	EXPECT_THROW(validateDateTime("1 1 01 1:1:1"),        CmdLineValueException);
	EXPECT_THROW(validateDateTime("31/02/01 1:1:1"),      CmdLineValueException);
	EXPECT_THROW(validateDateTime("31-4-01 1:1:1"),       CmdLineValueException);
	EXPECT_THROW(validateDateTime("0/1/2020 1:1:1"),      CmdLineValueException);
	EXPECT_THROW(validateDateTime("15/13/2020 1:1:1"),    CmdLineValueException);
	EXPECT_THROW(validateDateTime("data 1:1:1"),          CmdLineValueException);
	EXPECT_THROW(validateDateTime("29/02/2021 1:1:1"),    CmdLineValueException);
	EXPECT_THROW(validateDateTime("15-13-2020 1 1 1"),    CmdLineValueException);
	EXPECT_THROW(validateDateTime("15-13-2020 24:0:0"),   CmdLineValueException);
	EXPECT_THROW(validateDateTime("15-13-2020 nada"),     CmdLineValueException);
	EXPECT_THROW(validateDateTime("15-13-2020 23:60:0"),  CmdLineValueException);
	EXPECT_THROW(validateDateTime("15-13-2020 0:0:60"),   CmdLineValueException);
	EXPECT_THROW(validateDateTime("15-13-2020 24:-10:0"), CmdLineValueException);
	EXPECT_THROW(validateDateTime("15-13-2020 23/10/05"), CmdLineValueException);
	std::locale::global(std::locale());
}
TEST(Validations, Timestamp_OK) {
	EXPECT_NO_THROW(validateTimestamp("2001-01-01 01:01:01.000"));
	EXPECT_NO_THROW(validateTimestamp("2000-02-29 01:01:01.000"));
	EXPECT_NO_THROW(validateTimestamp("2001-02-28 01:01:01.000"));
	EXPECT_NO_THROW(validateTimestamp("2001-01-01 01:01:01.123456"));
	EXPECT_NO_THROW(validateTimestamp("2001-01-01-01:01:01.123456"));
}
TEST(Validations, Timestamp_KO) {
	EXPECT_THROW(validateTimestamp("2001-01-01 01 01 01.000"),    CmdLineValueException);
	EXPECT_THROW(validateTimestamp("2000-02-30 01:01:01.000"),    CmdLineValueException);
	EXPECT_THROW(validateTimestamp("2001-02-29 01:01:01.000"),    CmdLineValueException);
	EXPECT_THROW(validateTimestamp("2001-01-01 24:00:00.123456"), CmdLineValueException);
	EXPECT_THROW(validateTimestamp("2001-01-01-01:01:01.-12345"), CmdLineValueException);
	EXPECT_THROW(validateTimestamp("12-01-01-01:01:01.-12345"),   CmdLineValueException);
	EXPECT_THROW(validateTimestamp("123-01-01-01:01:01.-12345"),   CmdLineValueException);
}

TEST(Validations, Numbers_OK) {
	EXPECT_NO_THROW(validateNumber("1"));
	EXPECT_NO_THROW(validateNumber("-1"));
	EXPECT_NO_THROW(validateNumber("+123"));
	EXPECT_NO_THROW(validateNumber("123"));
	EXPECT_NO_THROW(validateNumber("123456"));
	EXPECT_NO_THROW(validateNumber("0xff"));
	EXPECT_NO_THROW(validateNumber("0X2f04e009")); 
	EXPECT_NO_THROW(validateNumber("0x7fffff"));
}

TEST(Validations, Numbers_KO) {
	EXPECT_THROW(validateNumber("p")       , CmdLineValueException);
	EXPECT_THROW(validateNumber("23:12:32"), CmdLineValueException);
	EXPECT_THROW(validateNumber(" "),        CmdLineValueException);
	EXPECT_THROW(validateNumber("0xfg"),     CmdLineValueException);
	EXPECT_THROW(validateNumber("--123"),    CmdLineValueException);
	EXPECT_THROW(validateNumber("-12-3"),    CmdLineValueException);
	EXPECT_THROW(validateNumber("xfa"),      CmdLineValueException);
	EXPECT_THROW(validateNumber("2f04e009"), CmdLineValueException);
}
TEST(Validations, LongNumbers_OK) {
	EXPECT_NO_THROW(validateLongNumber("1"));
	EXPECT_NO_THROW(validateLongNumber("-1"));
	EXPECT_NO_THROW(validateLongNumber("+123"));
	EXPECT_NO_THROW(validateLongNumber("123"));
	EXPECT_NO_THROW(validateLongNumber("123456"));
	EXPECT_NO_THROW(validateLongNumber("0xff"));
	EXPECT_NO_THROW(validateLongNumber("0X2f04e009"));
	EXPECT_NO_THROW(validateLongNumber("0x7fffff"));
}

TEST(Validations, LongNumbers_KO) {
	EXPECT_THROW(validateLongNumber("p"), CmdLineValueException);
	EXPECT_THROW(validateLongNumber("23:12:32"), CmdLineValueException);
	EXPECT_THROW(validateLongNumber(" "), CmdLineValueException);
	EXPECT_THROW(validateLongNumber("0xfg"), CmdLineValueException);
	EXPECT_THROW(validateLongNumber("--123"), CmdLineValueException);
	EXPECT_THROW(validateLongNumber("-12-3"), CmdLineValueException);
	EXPECT_THROW(validateLongNumber("xfa"), CmdLineValueException);
	EXPECT_THROW(validateLongNumber("2f04e009"), CmdLineValueException);
}
TEST(Validations, Decimals_OK) {
	EXPECT_NO_THROW(validateDecimal("1.23"));
	EXPECT_NO_THROW(validateDecimal("1"));
	EXPECT_NO_THROW(validateDecimal("+1"));
	EXPECT_NO_THROW(validateDecimal("-1"));
	EXPECT_NO_THROW(validateDecimal("1,0"));
	EXPECT_NO_THROW(validateDecimal("1,01"));
	EXPECT_NO_THROW(validateDecimal("+1,01"));
	EXPECT_NO_THROW(validateDecimal("-1,01"));
	EXPECT_NO_THROW(validateDecimal("-1.01"));
	EXPECT_NO_THROW(validateDecimal("1.01"));
}
TEST(Validations, Decimals_KO) {
	EXPECT_THROW(validateDecimal("p")       , CmdLineValueException);
	EXPECT_THROW(validateDecimal("23:12:32"), CmdLineValueException);
	EXPECT_THROW(validateDecimal("+-1,23")  , CmdLineValueException);
	EXPECT_THROW(validateDecimal("1 2")     , CmdLineValueException);
}
TEST(Validations, LongDecimals_OK) {
	EXPECT_NO_THROW(validateLongDecimal("1.23"));
	EXPECT_NO_THROW(validateLongDecimal("1"));
	EXPECT_NO_THROW(validateLongDecimal("+1"));
	EXPECT_NO_THROW(validateLongDecimal("-1"));
	EXPECT_NO_THROW(validateLongDecimal("1,0"));
	EXPECT_NO_THROW(validateLongDecimal("1,01"));
	EXPECT_NO_THROW(validateLongDecimal("+1,01"));
	EXPECT_NO_THROW(validateLongDecimal("-1,01"));
	EXPECT_NO_THROW(validateLongDecimal("-1.01"));
	EXPECT_NO_THROW(validateLongDecimal("1.01"));
}
TEST(Validations, LongDecimals_KO) {
	EXPECT_THROW(validateLongDecimal("p"), CmdLineValueException);
	EXPECT_THROW(validateLongDecimal("23:12:32"), CmdLineValueException);
	EXPECT_THROW(validateLongDecimal("+-1,23"), CmdLineValueException);
	EXPECT_THROW(validateLongDecimal("1 2"), CmdLineValueException);
}

#ifdef _WIN32
TEST(Validations, Directory_OK) {
	EXPECT_NO_THROW(validateDir("."));
	EXPECT_NO_THROW(validateDir(".."));
	EXPECT_NO_THROW(validateDir("c:\\windows"));
	EXPECT_NO_THROW(validateDir("c:\\program files"));
}

TEST(Validations, Directory_KO) {
	EXPECT_THROW(validateDir("\\ pepito"), CmdLineValueException);
	EXPECT_THROW(validateDir("......"),    CmdLineValueException);

}
TEST(Validations, DirectoryExists_OK) {
	EXPECT_NO_THROW(validateDir("c:\\program files"));
	EXPECT_NO_THROW(validateDir("."));
	EXPECT_NO_THROW(validateDir(".."));
	EXPECT_NO_THROW(validateDir("c:\\windows"));
	EXPECT_NO_THROW(validateDir("c:\\program files"));
}

TEST(Validations, DirectoryExists_KO) {
	EXPECT_THROW(validateDirExist("\\pepito"), CmdLineValueException);
	EXPECT_THROW(validateDirExist("......"), CmdLineValueException);

}

#endif

#if defined(unix) || defined(__unix__) || defined(__unix) || defined(__linux__)
#endif
