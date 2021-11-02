#ifndef _WIN32
#include <stdlib.h>
#endif

#include "pch.h"
#include "$tool.hpp"

Tool tool;

#ifdef _WIN32
int setenv(const char* name, const char* value, int overwrite)
{
    int errcode = 0;
    if (!overwrite) {
        size_t envsize = 0;
        errcode = getenv_s(&envsize, NULL, 0, name);
        if (errcode || envsize) return errcode;
    }
    return _putenv_s(name, value);
}
#endif
int main(int argc, char** argv) {
	setenv("CMDLINE_TESTING", "TRUE", 1);

	::testing::InitGoogleTest(&argc, argv);
	int rc = RUN_ALL_TESTS();
#ifndef _WIN32
	unsetenv("CMDLINE_TESTING");
#endif

	return rc;
}