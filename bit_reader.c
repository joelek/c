#include "bit_reader.h"

static si read(struct bit_reader_t* this, flag* value) {
  (void)(this);
  (void)(value);
  FAIL_IF("default interface method called");
}

const struct bit_reader_t bit_reader_t = {
  .state = NULL,
  .read = read
};
