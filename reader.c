#include "reader.h"

static si read(struct reader_t* this, byte* value) {
  (void)(this);
  (void)(value);
  FAIL_IF("default interface method called");
}

const struct reader_t reader_t = {
  .state = NULL,
  .read = read
};
