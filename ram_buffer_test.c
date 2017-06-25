#include "ram_buffer.h"

si testLifeCycle() {
  struct buffer_t buffer = buffer_t;
  FAIL_IF(ram_buffer_t.new(&buffer, 2));
  FAIL_IF(ram_buffer_t.old(&buffer));
  return EXIT_SUCCESS;
}

si testLength() {
  struct buffer_t buffer = buffer_t;
  FAIL_IF(ram_buffer_t.new(&buffer, 2));
  ui length;
  FAIL_IF(buffer.length(&buffer, &length));
  FAIL_IF(length != 2);
  FAIL_IF(ram_buffer_t.old(&buffer));
  return EXIT_SUCCESS;
}

si testGet() {
  struct buffer_t buffer = buffer_t;
  FAIL_IF(ram_buffer_t.new(&buffer, 2));
  byte value;
  FAIL_IF(buffer.get(&buffer, 0, &value));
  FAIL_IF(value != 0);
  FAIL_IF(buffer.get(&buffer, 1, &value));
  FAIL_IF(value != 0);
  FAIL_IF(ram_buffer_t.old(&buffer));
  return EXIT_SUCCESS;
}

si testSet() {
  struct buffer_t buffer = buffer_t;
  FAIL_IF(ram_buffer_t.new(&buffer, 2));
  FAIL_IF(buffer.set(&buffer, 0, 1));
  FAIL_IF(buffer.set(&buffer, 1, 2));
  byte value;
  FAIL_IF(buffer.get(&buffer, 0, &value));
  FAIL_IF(value != 1);
  FAIL_IF(buffer.get(&buffer, 1, &value));
  FAIL_IF(value != 2);
  FAIL_IF(ram_buffer_t.old(&buffer));
  return EXIT_SUCCESS;
}

si testSetMany() {
  struct buffer_t buffer = buffer_t;
  FAIL_IF(ram_buffer_t.new(&buffer, 2));
  FAIL_IF(buffer.set_many(&buffer, 0, ARRAY_ACTUAL(byte, 1, 2)));
  byte value;
  FAIL_IF(buffer.get(&buffer, 0, &value));
  FAIL_IF(value != 1);
  FAIL_IF(buffer.get(&buffer, 1, &value));
  FAIL_IF(value != 2);
  FAIL_IF(ram_buffer_t.old(&buffer));
  return EXIT_SUCCESS;
}

si main(void) {
  FAIL_IF(testLifeCycle());
  FAIL_IF(testLength());
  FAIL_IF(testGet());
  FAIL_IF(testSet());
  FAIL_IF(testSetMany());
  return EXIT_SUCCESS;
}
