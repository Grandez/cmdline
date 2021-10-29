#pragma once

#include <filesystem>
#include <locale>

// #include "parmitem.hpp"

using namespace std;

namespace _cmdline {
    void        validateEntry     (const char* parm, const char* prev);
    void        validateValue     (const char* value, Type type);
    long        validateNumber    (const char* value);
    double        validateDecimal   (const char* value);
    filesystem::path        validateDir       (const char* value);
    filesystem::path        validateDirExist  (const char* value);
    filesystem::path        validateFile      (const char* value);
    filesystem::path        validateFileExist (const char* value);
    struct tm *validateTime      (const char* value);
    struct tm* validateDate      (const char* value, int fmt = -1);
    struct tm* validateDateTime  (const char* value);
    vector<int> validateTimestamp (const char* value);
    template <typename T>
    T        getValue(const char* value, Type type);

}
