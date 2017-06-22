#pragma once

#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef float fp32;
typedef double fp64;
typedef int8_t si08;
typedef int16_t si16;
typedef int32_t si32;
typedef int64_t si64;
typedef intptr_t si;
typedef uint8_t ui08;
typedef uint16_t ui16;
typedef uint32_t ui32;
typedef uint64_t ui64;
typedef uintptr_t ui;
typedef uint8_t byte;
typedef char text;
typedef bool flag;

#ifdef DEBUG
  #define FAIL_IF(trigger)                                                       \
    if (trigger) {                                                               \
      printf("[%s:%u] %s\n", __FILE__, __LINE__, #trigger);                      \
      return EXIT_FAILURE;                                                       \
    }
#else
  #define FAIL_IF(trigger)                                                       \
    if (trigger) {                                                               \
      return EXIT_FAILURE;                                                       \
    }
#endif
