#pragma once
#include "cmdline.hpp"

constexpr auto VERBOSE   = "verbose";
constexpr auto SUMMARY   = "summary";
constexpr auto OVERWRITE = "overwrite";
constexpr auto INPUT     = "input";
constexpr auto OUTPUT    = "output";
constexpr auto PATTERN   = "pattern";
constexpr auto EXT       = "ext";

using namespace cmdline;


#ifdef __MAIN__
 CmdLine *cmdLine = nullptr;
#else 
extern CmdLine *cmdLine;
#endif
