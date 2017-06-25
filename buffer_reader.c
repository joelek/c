#include "buffer_reader.h"

struct state_t {
  struct buffer_t* buffer;
  ui index;
};

static si read(struct reader_t* this, byte* value) {
  FAIL_IF(this == NULL);
  struct state_t* state = this->state;
  FAIL_IF(state == NULL);
  FAIL_IF(value == NULL);
  ui length;
  FAIL_IF(state->buffer->length(state->buffer, &length));
  if (state->index >= length) {
    return EXIT_FAILURE;
  }
  FAIL_IF(state->buffer->get(state->buffer, state->index, value));
  state->index++;
  return EXIT_SUCCESS;
}

static const struct reader_t prototype = {
  .state = NULL,
  .read = read
};

static si new(struct reader_t* this, struct buffer_t* buffer) {
  FAIL_IF(this == NULL);
  struct state_t* state = this->state;
  FAIL_IF(state != NULL);
  FAIL_IF(buffer == NULL);
  byte* memory = malloc(sizeof(struct state_t));
  FAIL_IF(memory == NULL);
  *this = prototype;
  this->state = state = (struct state_t*)(memory);
  state->buffer = buffer;
  state->index = 0;
  return EXIT_SUCCESS;
}

static si old(struct reader_t* this) {
  FAIL_IF(this == NULL);
  struct state_t* state = this->state;
  FAIL_IF(state == NULL);
  free(state);
  this->state = NULL;
  return EXIT_SUCCESS;
}

const struct buffer_reader_t buffer_reader_t = {
  .new = new,
  .old = old
};
