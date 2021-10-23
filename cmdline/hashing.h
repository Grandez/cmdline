#pragma once

// #include "pstdint.h" /* Replace with <stdint.h> if appropriate */
#include "stdint.h" 

extern "C" unsigned long djb_hash(const char* data);
extern "C" uint32_t hsieh_hash(const char* data);

#define hash(a) djb_hash(a);
