#pragma once
#if defined(_WIN64)  /* Microsoft Windows (64-bit) */
    #define _strdup strdup
#endif

#if defined(_WIN32)  /* Microsoft Windows (32-bit) */
    #define strdup _strdup
#endif

