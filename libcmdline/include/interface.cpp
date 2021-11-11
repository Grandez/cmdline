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

static NS1::CmdLine* _cmdLine = nullptr;
static CmdLine* _pCmdLine = NULL;

template <typename T> void * checkException(T& ex) {
    /*
    if      constexpr (is_same<T, NS1::HelpRequested>::ex)                      errno = ECMDLINE_HELP;
    else if constexpr (is_same<T, NS1::HelpDetailedRequested>::ex)              errno = ECMDLINE_HELP_DETAIL;
    else if constexpr (is_same<T, NS1::CmdLineNotFoundException>::ex)           errno = ECMDLINE_NOTFND;
    else if constexpr (is_same<T, NS1::CmdLineInvalidTypeException>::ex)        errno = ECMDLINE_INVTYPE;
    else if constexpr (is_same<T, NS1::CmdLineParameterException>::ex)          errno = ECMDLINE_INVPARM;
    else if constexpr (is_same<T, NS1::CmdLineValueException>::ex)              errno = ECMDLINE_INVVALUE;
    else if constexpr (is_same<T, NS1::CmdLineDuplicateArgumentException>::ex)  errno = ECMDLINE_DUP;
    else                                                                    errno = ECMDLINE;
    */
        errno = ECMDLINE;
    return NULL;
}
// Magic numbers are: 1-Flag, 2-Option, 3-Define
logical     hasValue(int target, const char* name) {
    bool b;
    try {
        switch (target) {
                case 1: b = _cmdLine->hasFlag(name); break;
                case 2: b = _cmdLine->hasOption(name); break;
                case 3: b = _cmdLine->hasDefinition(name); break;
        }
        return (b) ? TRUE : FALSE;
    }
    catch (exception ex) {
        checkException(ex);
        return MISSING;
    }
}
logical     isMultiple(bool option, const char* name) {
    bool b;
    try {
        b = (option) ? _cmdLine->isOptionMultiple(name) 
                     : _cmdLine->isDefinitionMultiple(name);
        return (b) ? TRUE : FALSE;
    }
    catch (exception ex) {
        checkException(ex);
        return MISSING;
    }
}
NS1::Parameters makeParameters(ParmDef cparms[]) {
    vector <NS1::Parameter> parms;
    ParmDef* cp = cparms;
    while (cp->name) {
        bool b = (cp->multiple == TRUE) ? "1" : "0";
        NS1::Type t = NS1::Type(cp->type);
        parms.push_back(NS1::Parameter(cp->name, cp->value, t, b));
        cp++;
    }
    return parms;
}
const char** _makeArray(vector<const char *> data) {
    int i = 0;
    try {
        char** res = (char**)malloc((data.size() + 1) * sizeof(char*));
        for (i = 0; i < data.size(); i++) res[i] = strdup(data[i]);
        res[i] = 0x0;
        return (const char **) res;
    }
    catch (exception ex) {
        errno = ECMDLINE_NOMEM;
        return NULL;
    }
}
const char** _makeArray(vector<string> data) {
    int i = 0;
    try {
        char** res = (char**)malloc((data.size() + 1) * sizeof(char*));
        for (i = 0; i < data.size(); i++) res[i] = (char *) strdup(data[i].c_str());
        res[i] = 0x0;
        return (const char **) res;
    }
    catch (exception ex) {
        errno = ECMDLINE_NOMEM;
        return NULL;
    }
}

Parameter** _makeArrayParameter(NS1::Options data) {
    Parameter** parms = NULL;
    Parameter*  tmp   = NULL;
    try {
        parms = (Parameter **) malloc((data.size() + 1) * sizeof(Parameter *));
        int i = 0;
        for (auto it : data) {
            tmp = (Parameter *) malloc(sizeof(Parameter));
            tmp->name = strdup(it.first.c_str());
            tmp->size = (int) it.second.size();
            tmp->values = _makeArray(it.second);
            parms[i++] = tmp;
        }
        parms[i] = 0x0;
    }
    catch (exception ex) {
        errno = ECMDLINE_NOMEM;
        return NULL;
    }
    return parms;
}
const char* getValue(bool option, const char* name) {
    const char* res;
    try {
        res = (option) ? _cmdLine->getOption(name)
                       : _cmdLine->getDefinition(name);
        return res;
    }
    catch (exception ex) {
        return (const char *) checkException(ex);
    }
}
int getNumValues(bool option, const char* name) {
    int res;
    try {
        res = (option) ? _cmdLine->getOptionNumValues(name)
                       : _cmdLine->getDefinitionNumValues(name);
         return res;
    }
    catch (exception ex) {
        checkException(ex);
        return -1;
    }
}

const char** getAllValues(bool option, const char* name) {
    vector<const char *> res;
    try {
        res = (option) ? _cmdLine->getOptionValues(name)
                       : _cmdLine->getDefinitionValues(name);
        return _makeArray(res);
    }
    catch (exception ex) {
        return (const char**)checkException(ex);
    }
}
Parameter** _getOptions  (bool def) {
    Parameter **parms = NULL;
    NS1::Options opts;
    
    try {
        if (!def) {
            opts = _cmdLine->getCurrentOptions();
        } else {
            for (auto it: _cmdLine->getDefaultOptions()) {
                vector<string> v;
                v.push_back(it.second);
                opts.emplace(it.first, v);
            }
        }
        return _makeArrayParameter(opts);
    }
    catch (exception ex) {
        return (Parameter**) checkException(ex);
    }

    try {
        parms = (Parameter **) malloc((opts.size() + 1) * sizeof(Parameter *));
        int i = 0;
        for (auto it : opts) {
            i++;
        }
        parms[i] = 0x0;
    }
    catch (exception ex) {
        errno = ECMDLINE_NOMEM;
        return NULL;
    }

}

Flag** makeFlags(NS1::Flags flags) {
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
        tmp->value = (it.second) ? TRUE : FALSE;
        res[i++] = tmp;
    }
    res[i] = 0x0;
    return res;
}

logical      cHasFlag            (const char* name) { return hasValue(1, name); }
logical      cHasOption          (const char* name) { return hasValue(2, name); }
logical      cHasDefine          (const char* name) { return hasValue(3, name); }
logical      cIsOptionMultiple   (const char* name) { return isMultiple   (true, name); }
logical      cIsDefineMultiple   (const char* name) { return isMultiple   (false, name); }
int          cGetOptionNumValues (const char* name) { return getNumValues(true, name); }
int          cGetDefineNumValues (const char* name) { return getNumValues(false, name); }
const char*  cGetOption          (const char* name) { return getValue     (true, name); }
const char*  cGetDefine          (const char* name) { return getValue     (false, name); }
const char** cGetOptionValues    (const char* name) { return getAllValues (true, name); }
const char** cGetDefineValues    (const char* name) { return getAllValues (false, name); }

Flag **cGetDefaultFlags  (logical active) {
    try {
        bool b = (active == TRUE) ? false : true;
        NS1::Flags flags = _cmdLine->getDefaultFlags(b);
        return makeFlags(flags);
    }
    catch (exception ex) {
        return (Flag **) checkException(ex);
    }
}
Flag **cGetCurrentFlags  (logical active) {
    try {
        bool b = (active == TRUE) ? false : true;
        NS1::Flags flags = _cmdLine->getCurrentFlags(b);
        return makeFlags(flags);
    }
    catch (exception ex) {
        return (Flag **) checkException(ex);
    }
}
Parameter** cGetDefaultOptions  () {
    return _getOptions(true);
}
Parameter** cGetCurrentOptions  () {
    return _getOptions(false);
}
Parameter** cGetDefinitions  () {
    NS1::Options defs = _cmdLine->getDefinitions();
    return _makeArrayParameter(defs);
}

extern "C" CmdLine*  cmdline_create(int argc, const char** arg, ParmDef cparms[]) {
    if (_pCmdLine != nullptr) return _pCmdLine;
    NS1::Parameters parms = makeParameters(cparms);
    try {
        _cmdLine = new NS1::CmdLine(argc, arg, parms);

        _pCmdLine = (CmdLine*)malloc(sizeof(CmdLine));
        _pCmdLine->hasFlag            = &cHasFlag;
        _pCmdLine->hasOption          = &cHasOption;
        _pCmdLine->hasDefine          = &cHasDefine;
        _pCmdLine->getOption          = &cGetOption;
        _pCmdLine->getDefine          = &cGetDefine;
        _pCmdLine->getOptionValues    = &cGetOptionValues;
        _pCmdLine->getDefineValues    = &cGetDefineValues;
        _pCmdLine->getOptionNumValues = &cGetOptionNumValues;
        _pCmdLine->getDefineNumValues = &cGetDefineNumValues;

        _pCmdLine->isOptionMultiple  = &cIsOptionMultiple;
        _pCmdLine->isDefineMultiple  = &cIsDefineMultiple;
        _pCmdLine->getDefaultFlags   = &cGetDefaultFlags; 
	    _pCmdLine->getDefaultOptions = &cGetDefaultOptions; 
	    _pCmdLine->getCurrentOptions = &cGetCurrentOptions; 
	    _pCmdLine->getDefinitions    = &cGetDefinitions; 
//        memcpy(&_ppCmdLine, _pCmdLine, sizeof(cCmdLine));
        return _pCmdLine;
    }
    catch (exception ex) {
        return (CmdLine *) checkException(ex);
    }
}
extern "C" void cmdline_delete(CmdLine *cmdline) {
    std::cout << "delete\n";
}
