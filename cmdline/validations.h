#pragma once

#include "parmitem.hpp"

namespace cmdline {
    void        validateEntry(char* parm, char* prev);
    void        validateValue(char* value, Type type);
    inline void validateNumber(char* value);
    inline void validateDecimal(char* value);
    std::vector<int> validateTime(char* value);
    std::vector<int> validateDate(char* value);
    inline void validateDir(char* value);
    inline void validateDirExist(char* value);
    inline void validateFile(char* value);
    inline void validateFileExist(char* value);
}
