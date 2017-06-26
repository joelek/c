#include "vector_byte.h"

static si append_dummy(struct vector_t(byte)* this, byte value) {
  (void)(this);
  (void)(value);
  FAIL_IF("default interface method called");
}

const struct vector_t(byte) vector_t(byte) = {
  .state = NULL,
  .append = append_dummy
};

static si append(struct vector_t(byte)* this, byte value) {
  (void)(this);
  (void)(value);
  return EXIT_FAILURE;
}

static const struct vector_t(byte) prototype = {
  .state = NULL,
  .append = append
};

static si new(struct vector_t(byte)* this) {
  (void)(this);
  return EXIT_FAILURE;
}

static si old(struct vector_t(byte)* this) {
  (void)(this);
  return EXIT_FAILURE;
}

const struct vector_impl_t(byte) vector_impl_t(byte) = {
  .new = new,
  .old = old
};
