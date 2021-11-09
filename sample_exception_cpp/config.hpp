#pragma once
#include <iostream>
#include "cmdline.hpp"

constexpr auto VERBOSE    = "verbose";
constexpr auto SUMMARY    = "summary";
constexpr auto FLAG       = "flag";
constexpr auto NUMBERS    = "numbers";
constexpr auto NUMBER     = "number";
constexpr auto DECIMAL    = "decimal";
constexpr auto DECIMALS   = "decimals";
constexpr auto DATE       = "date";
constexpr auto TIME       = "time";
constexpr auto DATETIME   = "datetime";
constexpr auto TIMESTAMP  = "timestamp";
constexpr auto DIRIN      = "dirIn";
constexpr auto DIROUT     = "dirOut";
constexpr auto FILEIN     = "fileIn";
constexpr auto FILEOUT    = "fileOut";
constexpr auto CONFIG     = "config";

using namespace cmdline;


#ifdef __MAIN__
 CmdLine *cmdLine = nullptr;
#else 
extern CmdLine *cmdLine;
#endif

