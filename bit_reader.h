#pragma once

#include "header.h"

struct bit_reader_t {
  void* state;
  si (*read)(struct bit_reader_t* this, flag* value);
};

extern const struct bit_reader_t bit_reader_t;
