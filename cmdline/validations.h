#pragma once
namespace cmdline {

    void validateEntry(char* parm, char* prev);
    inline void validateNumber(char* value);
    inline void validateDecimal(char* value);
    inline void validateTime(char* value);
    _inline void validateDate(char* value);
    inline void validateDir(char* value);
    inline void validateDirExist(char* value);
    inline void validateFile(char* value);
    inline void validateFileExist(char* value);
}
