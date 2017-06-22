#pragma once

#include "buffer.h"
#include "header.h"

struct ram_buffer_t {
  si (*new)(struct buffer_t* this, ui size);
  si (*old)(struct buffer_t* this);
};

extern const struct ram_buffer_t ram_buffer_t;
