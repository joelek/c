#include "reader_bit_reader.h"

struct state_t {
  byte bytes[2];
  ui index;
};

si read(struct reader_t* this, byte* value) {
  FAIL_IF(this == NULL);
  struct state_t* state = this->state;
  FAIL_IF(state == NULL);
  FAIL_IF(value == NULL);
  if (state->index >= 2) {
    return EXIT_FAILURE;
  }
  *value = state->bytes[state->index++];
  return EXIT_SUCCESS;
}

si testLeftToRight() {
  struct state_t state = {
    .bytes = { 5, 160 },
    .index = 0
  };
  struct reader_t reader = {
    .state = &state,
    .read = read
  };
  struct bit_reader_t bit_reader = bit_reader_t;
  FAIL_IF(reader_bit_reader_t.new(&bit_reader, &reader, 0));
  flag values[16];
  ui index = 0;
  flag value;
  while (bit_reader.read(&bit_reader, &value) == EXIT_SUCCESS) {
    FAIL_IF(index >= 16);
    values[index++] = value;
  }
  FAIL_IF(values[0] != 1);
  FAIL_IF(values[1] != 0);
  FAIL_IF(values[2] != 1);
  FAIL_IF(values[3] != 0);
  FAIL_IF(values[4] != 0);
  FAIL_IF(values[5] != 0);
  FAIL_IF(values[6] != 0);
  FAIL_IF(values[7] != 0);
  FAIL_IF(values[8] != 0);
  FAIL_IF(values[9] != 0);
  FAIL_IF(values[10] != 0);
  FAIL_IF(values[11] != 0);
  FAIL_IF(values[12] != 0);
  FAIL_IF(values[13] != 1);
  FAIL_IF(values[14] != 0);
  FAIL_IF(values[15] != 1);
  FAIL_IF(reader_bit_reader_t.old(&bit_reader));
  return EXIT_SUCCESS;
}

si testRightToLeft() {
  struct state_t state = {
    .bytes = { 5, 160 },
    .index = 0
  };
  struct reader_t reader = {
    .state = &state,
    .read = read
  };
  struct bit_reader_t bit_reader = bit_reader_t;
  FAIL_IF(reader_bit_reader_t.new(&bit_reader, &reader, 1));
  flag values[16];
  ui index = 0;
  flag value;
  while (bit_reader.read(&bit_reader, &value) == EXIT_SUCCESS) {
    FAIL_IF(index >= 16);
    values[index++] = value;
  }
  FAIL_IF(values[0] != 0);
  FAIL_IF(values[1] != 0);
  FAIL_IF(values[2] != 0);
  FAIL_IF(values[3] != 0);
  FAIL_IF(values[4] != 0);
  FAIL_IF(values[5] != 1);
  FAIL_IF(values[6] != 0);
  FAIL_IF(values[7] != 1);
  FAIL_IF(values[8] != 1);
  FAIL_IF(values[9] != 0);
  FAIL_IF(values[10] != 1);
  FAIL_IF(values[11] != 0);
  FAIL_IF(values[12] != 0);
  FAIL_IF(values[13] != 0);
  FAIL_IF(values[14] != 0);
  FAIL_IF(values[15] != 0);
  FAIL_IF(reader_bit_reader_t.old(&bit_reader));
  return EXIT_SUCCESS;
}

si main(void) {
  FAIL_IF(testLeftToRight());
  FAIL_IF(testRightToLeft());
  return EXIT_SUCCESS;
}
