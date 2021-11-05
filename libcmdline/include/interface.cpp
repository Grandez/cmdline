#include <iostream>
#include "cmdline.hpp"
#include "cmdline.h"
#include "cmdline_exceptions.hpp"
#include "cmdline.h"
#include "types.h"
#include "types.hpp"
#include "interface.hpp"
#include "cmdline_errno.h"
#include "tools.hpp"

#ifdef _WIN32
// Pointer is not null
// Theres is enoguh space
// it is enum becauase is C
#pragma warning(disable : 26812 6011 6386)
#endif

static cmdline::CmdLine* _cmdLine = nullptr;
static CmdLine* _pCmdLine = nullptr;

template <typename T> void * checkException(T& ex) {
    /*
    if      constexpr (is_same<T, cmdline::HelpRequested>::ex)                      errno = ECMDLINE_HELP;
    else if constexpr (is_same<T, cmdline::HelpDetailedRequested>::ex)              errno = ECMDLINE_HELP_DETAIL;
    else if constexpr (is_same<T, cmdline::CmdLineNotFoundException>::ex)           errno = ECMDLINE_NOTFND;
    else if constexpr (is_same<T, cmdline::CmdLineInvalidTypeException>::ex)        errno = ECMDLINE_INVTYPE;
    else if constexpr (is_same<T, cmdline::CmdLineParameterException>::ex)          errno = ECMDLINE_INVPARM;
    else if constexpr (is_same<T, cmdline::CmdLineValueException>::ex)              errno = ECMDLINE_INVVALUE;
    else if constexpr (is_same<T, cmdline::CmdLineDuplicateArgumentException>::ex)  errno = ECMDLINE_DUP;
    else                                                                    errno = ECMDLINE;
    */
        errno = ECMDLINE;
    return NULL;
}
cmdline::Parameters makeParameters(ParmDef cparms[]) {
    vector <cmdline::Parm> parms;
    ParmDef *cp = cparms;
    while (cp->name) {
        bool b = (cp->multiple == CHECKED) ? "1" : "0";
        cmdline::Type t = cmdline::Type(cp->type);
        parms.push_back(cmdline::Parm(cp->name, cp->value, t, b));
        cp++;
    }

    /*
    
    int i = 0;
    ParmDef *pp = *cparms;
    while (pp) {
        bool b = (cparms[i]->multiple == TRUE) ? "1" : "0";
        cmdline::Type t = cmdline::Type(cparms[i]->type);
        parms.push_back(cmdline::Parm(cparms[i]->name, cparms[i]->value,t,b));
        i++;
    }
    */
    return parms;
}
Flag** makeFlags(cmdline::Flags flags) {
    int i = 0;
    Flag* tmp;
    Flag** res = (Flag**)malloc((flags.size() + 1) * sizeof(Flag*));
    for (auto it : flags) {
        tmp = (Flag*)malloc(sizeof(Flag));
        if (!tmp) {
            errno = ECMDLINE_NOMEM;
            return NULL;
        }
        tmp->name = strdup(it.first.c_str());
        tmp->value = (it.second) ? CHECKED : UNCHECKED;
        res[i++] = tmp;
    }
    res[i] = 0x0;
/*
    for (i = 0; i < flags.size(); i++) {

        
        tmp->value = (flags[i].value) ? TRUE : FALSE;
        res[i] = tmp;
    }
    */
//    res[i] = 0x0;
    return res;
}

logical cHashflag(const char* name) {
    try {
        bool b = _cmdLine->hasFlag(name);
        return (b) ? CHECKED : UNCHECKED;
    }
    catch (exception ex) {
        checkException(ex);
        return UNKNOW;
    }
}
Flag **cGetDefaultFlags  (logical all) {
    try {
        bool b = (all == CHECKED) ? false : true;
        cmdline::Flags flags = _cmdLine->getDefaultFlags(b);
        return makeFlags(flags);
    }
    catch (exception ex) {
        return (Flag **) checkException(ex);
    }
}

extern "C" CmdLine * cmdline_create(int argc, char** arg, ParmDef cparms[]) {
    if (_pCmdLine != nullptr) return _pCmdLine;
    cmdline::Parameters parms = makeParameters(cparms);
    try {
        _cmdLine = new cmdline::CmdLine(argc, arg, parms);
        _pCmdLine = (CmdLine*)malloc(sizeof(CmdLine));
        _pCmdLine->hashFlag = &cHashflag;
        _pCmdLine->getDefaultFlags = &cGetDefaultFlags;

        return _pCmdLine;
    }
    catch (exception ex) {
        return (CmdLine *) checkException(ex);
    }
}
extern "C" void cmdline_delete() {
    std::cout << "delete\n";
}
