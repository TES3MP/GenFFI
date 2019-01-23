//
// Created by koncord on 15.01.19.
//

#pragma once

#include <stdint.h>

#ifdef X86_WIN64
#ifdef _MSC_VER
typedef unsigned __int64 RetType;
#else
typedef unsigned long long RetType;
#endif
#elif (defined __x86_64__ || defined __aarch64__) && defined __ILP32__
typedef unsigned long long RetType;
#else
typedef unsigned long RetType;
#endif

typedef unsigned long long(*ScriptFunc)();
typedef unsigned int PlayerId;

#define InvalidPID ((unsigned int) -1)

#if !(defined __cplusplus || defined _GENFFI)
typedef uint8_t bool;
#endif
