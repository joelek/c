#pragma once

#include "header.h"

struct buffer_t {
  void* state;
  si (*get)(struct buffer_t* this, ui index, byte* value);
  si (*length)(struct buffer_t* this, ui* length);
  si (*set)(struct buffer_t* this, ui index, byte value);
  si (*set_many)(struct buffer_t* this, ui offset, ARRAY_FORMAL(byte, values));
};

extern const struct buffer_t buffer_t;
