#include "vector_byte.h"

struct state_t {
  byte* data;
  ui size;
  ui used;
};

static si dummy_append(struct vector_t(byte)* this, byte value) {
  (void)(this);
  (void)(value);
  FAIL_IF("default interface method called");
}

static si dummy_equals(struct vector_t(byte)* this, struct vector_t(byte)* that, flag* result) {
  (void)(this);
  (void)(that);
  (void)(result);
  FAIL_IF("default interface method called");
}

const struct vector_t(byte) vector_t(byte) = {
  .state = NULL,
  .append = dummy_append,
  .equals = dummy_equals
};

static si append(struct vector_t(byte)* this, byte value) {
  FAIL_IF(this == NULL);
  struct state_t* state = this->state;
  FAIL_IF(state == NULL);
  if (state->used >= state->size) {
    ui size = (state->size << 1);
    byte* memory = realloc(state, sizeof(struct state_t) + size*sizeof(byte));
    FAIL_IF(memory == NULL);
    this->state = state = (struct state_t*)(memory);
    state->data = (byte*)(memory + sizeof(struct state_t));
    state->size = size;
  }
  state->data[state->used++] = value;
  return EXIT_SUCCESS;
}

static si equals(struct vector_t(byte)* this, struct vector_t(byte)* that, flag* result) {
  FAIL_IF(this == NULL);
  struct state_t* this_state = this->state;
  FAIL_IF(this_state == NULL);
  FAIL_IF(that == NULL);
  struct state_t* that_state = that->state;
  FAIL_IF(that_state == NULL);
  FAIL_IF(result == NULL);
  if (this_state->used != that_state->used) {
    *result = 0;
    return EXIT_SUCCESS;
  }
  for (ui i = 0; i < this_state->used; i++) {
    if (this_state->data[i] != that_state->data[i]) {
      *result = 0;
      return EXIT_SUCCESS;
    }
  }
  *result = 1;
  return EXIT_SUCCESS;
}

static const struct vector_t(byte) prototype = {
  .state = NULL,
  .append = append,
  .equals = equals
};

static si new(struct vector_t(byte)* this) {
  FAIL_IF(this == NULL);
  struct state_t* state = this->state;
  FAIL_IF(state != NULL);
  ui size = 8;
  byte* memory = malloc(sizeof(struct state_t) + size*sizeof(byte));
  FAIL_IF(memory == NULL);
  *this = prototype;
  this->state = state = (struct state_t*)(memory);
  state->data = (byte*)(memory + sizeof(struct state_t));
  state->size = size;
  state->used = 0;
  return EXIT_SUCCESS;
}

static si old(struct vector_t(byte)* this) {
  FAIL_IF(this == NULL);
  struct state_t* state = this->state;
  FAIL_IF(state == NULL);
  free(state);
  this->state = NULL;
  return EXIT_SUCCESS;
}

const struct vector_impl_t(byte) vector_impl_t(byte) = {
  .new = new,
  .old = old
};
