#pragma once

#include "header.h"

#define vector_t(type) vector_t__##type

struct vector_t(byte) {
  void* state;
  si (*append)(struct vector_t(byte)* this, byte value);
  si (*equals)(struct vector_t(byte)* this, struct vector_t(byte)* that, flag* result);
  si (*new)(struct vector_t(byte)* this);
  si (*old)(struct vector_t(byte)* this);
};

extern const struct vector_t(byte) vector_t(byte);
