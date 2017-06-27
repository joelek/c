#pragma once

#include "header.h"

#define vector_t(type) vector_t__##type

struct vector_t(GENERIC_TYPE) {
  void* state;
  si (*append)(struct vector_t(GENERIC_TYPE)* this, GENERIC_TYPE value);
  si (*equals)(struct vector_t(GENERIC_TYPE)* this, struct vector_t(GENERIC_TYPE)* that, flag* result);
  si (*new)(struct vector_t(GENERIC_TYPE)* this);
  si (*old)(struct vector_t(GENERIC_TYPE)* this);
};

extern const struct vector_t(GENERIC_TYPE) vector_t(GENERIC_TYPE);
