#pragma once

#include "header.h"

struct allocator_t;

struct INTERFACE(allocator_t) {
  si (*access)(void** ref, void** target);
  si (*create)(void** ref, ui bytes, si (*destroy_callback)(void**));
  si (*release)(void** ref);
  si (*release_weak)(void** ref);
  si (*retain)(void** ref, void** target);
  si (*retain_weak)(void** ref, void** target);
};

extern const struct INTERFACE(allocator_t) allocator_t;
