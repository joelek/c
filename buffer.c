#include "buffer.h"

static si get(struct buffer_t* this, ui index, byte* value) {
  (void)(this);
  (void)(index);
  (void)(value);
  FAIL_IF("default interface method called");
}

static si length(struct buffer_t* this, ui* length) {
  (void)(this);
  (void)(length);
  FAIL_IF("default interface method called");
}

static si set(struct buffer_t* this, ui index, byte value) {
  (void)(this);
  (void)(index);
  (void)(value);
  FAIL_IF("default interface method called");
}

static si set_many(struct buffer_t* this, ui offset, ARRAY_FORMAL(byte, values)) {
  (void)(this);
  (void)(offset);
  (void)(ARRAY_DATA(values));
  (void)(ARRAY_SIZE(values));
  FAIL_IF("default interface method called");
}

const struct buffer_t buffer_t = {
  .state = NULL,
  .get = get,
  .length = length,
  .set = set,
  .set_many = set_many
};
