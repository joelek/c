#include "vector_GENERIC_TYPE.h"

static si append_dummy(struct vector_t(GENERIC_TYPE)* this, GENERIC_TYPE value) {
  (void)(this);
  (void)(value);
  FAIL_IF("default interface method called");
}

const struct vector_t(GENERIC_TYPE) vector_t(GENERIC_TYPE) = {
  .state = NULL,
  .append = append_dummy
};

static si append(struct vector_t(GENERIC_TYPE)* this, GENERIC_TYPE value) {
  (void)(this);
  (void)(value);
  return EXIT_FAILURE;
}

static const struct vector_t(GENERIC_TYPE) prototype = {
  .state = NULL,
  .append = append
};

static si new(struct vector_t(GENERIC_TYPE)* this) {
  (void)(this);
  return EXIT_FAILURE;
}

static si old(struct vector_t(GENERIC_TYPE)* this) {
  (void)(this);
  return EXIT_FAILURE;
}

const struct vector_impl_t(GENERIC_TYPE) vector_impl_t(GENERIC_TYPE) = {
  .new = new,
  .old = old
};
