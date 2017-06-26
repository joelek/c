#include "ram_buffer.h"

si test_life_cycle() {
  struct buffer_t buffer = buffer_t;
  FAIL_IF(ram_buffer_t.new(&buffer, 2));
  FAIL_IF(ram_buffer_t.old(&buffer));
  return EXIT_SUCCESS;
}

si test_length() {
  struct buffer_t buffer = buffer_t;
  FAIL_IF(ram_buffer_t.new(&buffer, 2));
  ui length;
  FAIL_IF(buffer.length(&buffer, &length));
  FAIL_IF(length != 2);
  FAIL_IF(ram_buffer_t.old(&buffer));
  return EXIT_SUCCESS;
}

si test_get() {
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

si test_set() {
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

si test_set_many() {
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
  FAIL_IF(test_life_cycle());
  FAIL_IF(test_length());
  FAIL_IF(test_get());
  FAIL_IF(test_set());
  FAIL_IF(test_set_many());
  return EXIT_SUCCESS;
}
