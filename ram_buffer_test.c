#include "ram_buffer.h"

si main(void) {
  struct buffer_t buffer = buffer_t;
  FAIL_IF(ram_buffer_t.new(&buffer, 4));
  ui length;
  FAIL_IF(buffer.length(&buffer, &length));
  FAIL_IF(length != 4);
  FAIL_IF(ram_buffer_t.old(&buffer));
  return EXIT_SUCCESS;
}
