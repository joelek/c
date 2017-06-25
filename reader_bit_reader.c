#include "reader_bit_reader.h"

struct state_t {
  struct reader_t* reader;
  byte current_byte;
  byte current_mask;
  flag left_to_right;
};

static si read(struct bit_reader_t* this, flag* value) {
  FAIL_IF(this == NULL);
  struct state_t* state = this->state;
  FAIL_IF(state == NULL);
  FAIL_IF(value == NULL);
  if (state->current_mask == 0) {
    if (state->reader->read(state->reader, &state->current_byte) == EXIT_FAILURE) {
      return EXIT_FAILURE;
    }
    if (state->left_to_right) {
      state->current_mask = (1 << 7);
    } else {
      state->current_mask = (1 << 0);
    }
  }
  *value = ((state->current_byte & state->current_mask) == state->current_mask);
  if (state->left_to_right) {
    state->current_mask = (state->current_mask >> 1);
  } else {
    state->current_mask = (state->current_mask << 1);
  }
  return EXIT_SUCCESS;
}

static const struct bit_reader_t implementation = {
  .state = NULL,
  .read = read
};

static si new(struct bit_reader_t* this, struct reader_t* reader, flag left_to_right) {
  FAIL_IF(this == NULL);
  struct state_t* state = this->state;
  FAIL_IF(state != NULL);
  FAIL_IF(reader == NULL);
  byte* memory = malloc(sizeof(struct state_t));
  FAIL_IF(memory == NULL);
  *this = implementation;
  this->state = state = (struct state_t*)(memory);
  state->reader = reader;
  state->current_byte = 0;
  state->current_mask = 0;
  state->left_to_right = left_to_right;
  return EXIT_SUCCESS;
}

static si old(struct bit_reader_t* this) {
  FAIL_IF(this == NULL);
  struct state_t* state = this->state;
  FAIL_IF(state == NULL);
  free(state);
  this->state = NULL;
  return EXIT_SUCCESS;
}

const struct reader_bit_reader_t reader_bit_reader_t = {
  .new = new,
  .old = old
};
