#pragma once

#include "bit_reader.h"
#include "header.h"
#include "reader.h"

struct reader_bit_reader_t {
  si (*new)(struct bit_reader_t* this, struct reader_t* reader, flag left_to_right);
  si (*old)(struct bit_reader_t* this);
};

extern const struct reader_bit_reader_t reader_bit_reader_t;
