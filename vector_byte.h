#pragma once

#include "header.h"

#define vector_t(type) vector_t__##type
#define vector_impl_t(type) vector_impl_t__##type

struct vector_t(byte) {
  void* state;
  si (*append)(struct vector_t(byte)* this, byte value);
};

extern const struct vector_t(byte) vector_t(byte);

struct vector_impl_t(byte) {
  si (*new)(struct vector_t(byte)* this);
  si (*old)(struct vector_t(byte)* this);
};

extern const struct vector_impl_t(byte) vector_impl_t(byte);
