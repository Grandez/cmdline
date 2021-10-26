#pragma once

//#ifndef __COMMON_H__
//#define __COMMON_H__

#if defined(_WIN64)  /* Microsoft Windows (64-bit) */
    #define _strdup strdup
#endif

#if defined(_WIN32)  /* Microsoft Windows (32-bit) */
    #define strdup _strdup
#endif

#include <string>
#include <vector>
#include <iostream>
#include <utility>
#include <unordered_map>

#include "arg.hpp"
#include "tools.h"
//#endif
