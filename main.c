/*
#define ARRAY_ACTUAL(type, ...) sizeof((type[]){__VA_ARGS__})/sizeof(type), (type[]){__VA_ARGS__}
#define ARRAY_FORMAL(type, name) ui name##__length, type name[name##__length]
#define ARRAY_LENGTH(name) name##__length

void test(ARRAY_FORMAL(ui32, array)) {
  ui length = ARRAY_LENGTH(array);
  for (ui i = 0; i < length; i++) {
    printf("%u ", array[i]);
  }
  printf("\nlength: %u\n", length);
}
test(ARRAY_ACTUAL(ui32, 0, 1));
*/

#include "lib.h"

si main(void) {
  return EXIT_SUCCESS;
}
