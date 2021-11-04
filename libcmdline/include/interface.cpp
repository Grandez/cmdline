#include "cmdline.h"
#include "cmdline.hpp"
#include "types.h"
#include "types.hpp"
#include "cmdline_errno.h"

using namespace cmdline;

static cmdline::CmdLine* cmdLine;
sCmdLine scmdline;

void checkException(exception ex) {

}
Flag** makeFlag(Flags flags) {
    int i;
    Flag* tmp;
    Flag** res = (Flag **) malloc((flags.size() + 1) * sizeof(Flag *));
    for (i = 0; i < flags.size(); i++) {
        tmp = (Flag*)malloc(sizeof(Flag));
        tmp->name = strdup(flags[i].name);
        tmp->value = (flags[i].value) ? TRUE : FALSE;
        res[i] = tmp;
    }
    res[i] = 0x0;
    return res;
}
char cHashflag(const char* name) {
    try {
        bool b = cmdLine->hasFlag(name);
        return (b) ? '1' : '0';
    }
    catch (exception ex) {
        checkException(ex);
        return NULL;
    }
}
Flag *cGetDefaultFlags)  (logical all) {
    try {
        bool b = (all == FALSE) ? false : true;
        Flags flags = cmdLine->cGegtDefaultFlags(b);
        return makeFlag(flags);
    }
    catch (exception ex) {
        checkException(ex);
        return NULL;
    }

}
typedef struct struct_cmdline {

    Flag* (*getDefaultFlags)  (char all);
    logical(*hasOption)        (const char* name);
    logical(*isOptionMultiple) (const char* name);
} sCmdLine;


sCmdLine *create() {
    sCmdLine *ptr;

    try {
        cmdLine = new cmdline::CmdLine();
        scmdline.hashFlag = &cHashflag;

        return &scmdline;
    }
    catch (exception ex) {
        errno = ERR_CMDLINE_EXCEPTION;
        return NULL;
    }
}

/*
bool  hasFlag(const char* name);
bool  hasFlag(string name);
Flags getDefaultFlags(bool all = true);
Flags getCurrentFlags(bool all = true);
*/

// using namespace cmdline;

/*
void callMyclassSendCommandToSerialDevice(int Command, int Parameters, int DeviceId)
{
    // May need try/catch here.
    myclass->sendCommandToSerialDevice(Command, Parameters, DeviceId);
}
*/
void destroy()
{
    delete cmdLine;
}