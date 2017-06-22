#include "buffer_reader.h"

si get(struct buffer_t* this, ui index, byte* value) {
  FAIL_IF(this == NULL);
  FAIL_IF(value == NULL);
  *value = index;
  return EXIT_SUCCESS;
}

si length(struct buffer_t* this, ui* length) {
  FAIL_IF(this == NULL);
  FAIL_IF(length == NULL);
  *length = 4;
  return EXIT_SUCCESS;
}

struct buffer_t buffer = {
  .get = get,
  .length = length
};

si main(void) {
  struct reader_t reader = reader_t;
  FAIL_IF(buffer_reader_t.new(&reader, &buffer));
  byte values[4];
  ui index = 0;
  byte value;
  while (reader.read(&reader, &value) == EXIT_SUCCESS) {
    FAIL_IF(index >= 4);
    values[index++] = value;
  }
  FAIL_IF(values[0] != 0);
  FAIL_IF(values[1] != 1);
  FAIL_IF(values[2] != 2);
  FAIL_IF(values[3] != 3);
  FAIL_IF(buffer_reader_t.old(&reader));
  return EXIT_SUCCESS;
}
