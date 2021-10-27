#pragma once
#ifndef __TYPES__
   #define __TYPES__

enum class Type { STRING, NUMBER, DECIMAL, DATE, TIME, DATETIME, TMS, DIR, DIR_EXISTS, FILE, FILE_EXISTS, FLAG, DEFINE };
   enum class Source { DEFAULT, ENV, CMDLINE, AUTO };

   #define strdup(a) myStrdup(a)
#endif

