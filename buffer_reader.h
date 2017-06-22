#pragma once

#include "buffer.h"
#include "header.h"
#include "reader.h"

struct buffer_reader_t {
  si (*new)(struct reader_t* this, struct buffer_t* buffer);
  si (*old)(struct reader_t* this);
};

extern const struct buffer_reader_t buffer_reader_t;
