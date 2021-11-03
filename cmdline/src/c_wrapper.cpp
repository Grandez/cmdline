#include "errno.h"
#include "c_wrapper.h"
#include "cmdline.hpp"

#include "tools.h"

cmdline::CmdLine cmdLine;
using namespace cmdline;

cmdline::Parameters makeParameters(Parameter parms[]) {
    int i = 0;
    Parameters arr;
    Parm p;
    if (parms == 0x0) return arr;
    while (parms[i].name != 0x0) {
        bool mult = (parms[i].multiple == FALSE) ? false : true;
        if (parms[i].type == FLAG) {
            bool val = _cmdline::makeBoolean(parms[i].value);
            p = Parm(parms[i].name, val);
        }
        else {
            p = Parm(parms[i].name, parms[i].value, cmdline::Type(parms[i].type), mult);
        }
        arr.push_back(p);
        i++;
   }
    return arr;
}

    int cmdline_create(int argc, char** argv, Parameter parms[]) {
        Parameters p = makeParameters(parms);
        try {
            cmdLine = CmdLine::getInstance(argc, argv, p);
        }
        catch (CmdLineException ex) {
            errno = 33; // ERR_CMDLINE_EXCEPTION;
            return -1;
        }
        return 0;
    }
    void destroy() {
        // ~cmdline();
    }

