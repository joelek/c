#pragma once

#include "header.h"

struct reader_t {
  void* state;
  si (*read)(struct reader_t* this, byte* value);
};

extern const struct reader_t reader_t;
