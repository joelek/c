#include "allocator.h"

struct allocator_t {
  si retain_count;
  si retain_count_weak;
  si (*destroy_callback)(void**);
};

static si access(void** ref, void** target) {
  FAIL_IF(ref == NULL);
  void* this = *ref;
  FAIL_IF(this == NULL);
  FAIL_IF(target == NULL);
  FAIL_IF(*target != NULL);
  byte* memory = (byte*)(this) - sizeof(struct allocator_t);
  struct allocator_t* allocator = (struct allocator_t*)(memory);
  FAIL_IF(allocator->retain_count <= 0);
  *target = this;
  return EXIT_SUCCESS;
}

static si create(void** ref, ui bytes, si (*destroy_callback)(void**)) {
  FAIL_IF(ref == NULL);
  void* this = *ref;
  FAIL_IF(this != NULL);
  FAIL_IF(bytes == 0);
  FAIL_IF(destroy_callback == NULL);
  byte* memory = (byte*)(malloc(sizeof(struct allocator_t) + bytes));
  FAIL_IF(memory == NULL);
  struct allocator_t* allocator = (struct allocator_t*)(memory);
  allocator->retain_count = 1;
  allocator->retain_count_weak = 0;
  allocator->destroy_callback = destroy_callback;
  this = (void*)(memory + sizeof(struct allocator_t));
  *ref = this;
  return EXIT_SUCCESS;
}

static si release(void** ref) {
  FAIL_IF(ref == NULL);
  void* this = *ref;
  FAIL_IF(this == NULL);
  byte* memory = (byte*)(this) - sizeof(struct allocator_t);
  struct allocator_t* allocator = (struct allocator_t*)(memory);
  FAIL_IF(allocator->retain_count <= 0);
  if (--(allocator->retain_count) == 0) {
    si retain_count_weak_before_destroy_callback = allocator->retain_count_weak;
    FAIL_IF(allocator->destroy_callback(ref));
    if (retain_count_weak_before_destroy_callback == 0) {
      free(memory);
    }
  }
  *ref = NULL;
  return EXIT_SUCCESS;
}

static si release_weak(void** ref) {
  FAIL_IF(ref == NULL);
  void* this = *ref;
  FAIL_IF(this == NULL);
  byte* memory = (byte*)(this) - sizeof(struct allocator_t);
  struct allocator_t* allocator = (struct allocator_t*)(memory);
  FAIL_IF(allocator->retain_count_weak <= 0);
  if (--(allocator->retain_count_weak) == 0) {
    if (allocator->retain_count == 0) {
      free(memory);
    }
  }
  *ref = NULL;
  return EXIT_SUCCESS;
}

static si retain(void** ref, void** target) {
  FAIL_IF(ref == NULL);
  void* this = *ref;
  FAIL_IF(this == NULL);
  FAIL_IF(target == NULL);
  FAIL_IF(*target != NULL);
  byte* memory = (byte*)(this) - sizeof(struct allocator_t);
  struct allocator_t* allocator = (struct allocator_t*)(memory);
  FAIL_IF(allocator->retain_count <= 0);
  (allocator->retain_count)++;
  *target = this;
  return EXIT_SUCCESS;
}

static si retain_weak(void** ref, void** target) {
  FAIL_IF(ref == NULL);
  void* this = *ref;
  FAIL_IF(this == NULL);
  FAIL_IF(target == NULL);
  FAIL_IF(*target != NULL);
  byte* memory = (byte*)(this) - sizeof(struct allocator_t);
  struct allocator_t* allocator = (struct allocator_t*)(memory);
  FAIL_IF(allocator->retain_count <= 0);
  (allocator->retain_count_weak)++;
  *target = this;
  return EXIT_SUCCESS;
}

const struct INTERFACE(allocator_t) allocator_t = {
  .access = access,
  .create = create,
  .release = release,
  .release_weak = release_weak,
  .retain = retain,
  .retain_weak = retain_weak
};
