#include "ram_buffer.h"

struct state_t {
  byte* data;
  ui size;
};

static si get(struct buffer_t* this, ui index, byte* value) {
  FAIL_IF(this == NULL);
  struct state_t* state = this->state;
  FAIL_IF(state == NULL);
  FAIL_IF(value == NULL);
  FAIL_IF(index >= state->size);
  *value = state->data[index];
  return EXIT_SUCCESS;
}

static si length(struct buffer_t* this, ui* length) {
  FAIL_IF(this == NULL);
  struct state_t* state = this->state;
  FAIL_IF(state == NULL);
  FAIL_IF(length == NULL);
  *length = state->size;
  return EXIT_SUCCESS;
}

static si set(struct buffer_t* this, ui index, byte value) {
  FAIL_IF(this == NULL);
  struct state_t* state = this->state;
  FAIL_IF(state == NULL);
  FAIL_IF(index >= state->size);
  state->data[index] = value;
  return EXIT_SUCCESS;
}

static const struct buffer_t prototype = {
  .state = NULL,
  .get = get,
  .length = length,
  .set = set
};

static si new(struct buffer_t* this, ui size) {
  FAIL_IF(this == NULL);
  struct state_t* state = this->state;
  FAIL_IF(state != NULL);
  byte* memory = malloc(sizeof(struct state_t) + size);
  FAIL_IF(memory == NULL);
  *this = prototype;
  this->state = state = (struct state_t*)(memory);
  state->data = (byte*)(memory + sizeof(struct state_t));
  memset(state->data, 0, size);
  state->size = size;
  return EXIT_SUCCESS;
}

static si old(struct buffer_t* this) {
  FAIL_IF(this == NULL);
  struct state_t* state = this->state;
  FAIL_IF(state == NULL);
  free(state);
  this->state = NULL;
  return EXIT_SUCCESS;
}

const struct ram_buffer_t ram_buffer_t = {
  .new = new,
  .old = old
};
