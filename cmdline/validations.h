#pragma once

#include <locale>

#include "parmitem.hpp"

using namespace std;

namespace cmdline {
    void        validateEntry     (const char* parm, const char* prev);
    void        validateValue     (const char* value, Type type);
    void        validateNumber    (const char* value);
    void        validateDecimal   (const char* value);
    void        validateDir       (const char* value);
    void        validateDirExist  (const char* value);
    void        validateFile      (const char* value);
    void        validateFileExist (const char* value);
    vector<int> validateTime      (const char* value);
    vector<int> validateDate      (const char* value, int fmt = -1);
    vector<int> validateDateTime  (const char* value);
    vector<int> validateTimestamp (const char* value);
}
