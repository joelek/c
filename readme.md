# C with interfaces

An attempt at structuring C code using interfaces and implementations in order to promote encapsulation, testability, extensibility and code-safety.

The method used in this repository uses standardized C99 features only and is currently limited to single interface implementations only.

## interface.h:

```
struct interface_t {
  void* state;
  int (*method)(struct interface_t* this);
};

extern const struct interface_t interface_t;
```

The structure defines an interface where all methods are function pointers as well as a state of `void*` type. The function pointers allow implementations of the interface to be created simply by setting them to concrete functions for the given implementation. The `void*` type of the state allows the state to be of a structure that is only known by the implementation itself. Implementations may also choose not to use it when it's not needed.

## interface.c

```
static int method(struct interface_t* this) {
  (void)(this);
  FAIL_IF(true);
}

const struct interface_t interface_t = {
  .state = NULL,
  .method = method
};
```

The functions have static storage duration in order for the names not to conflict with other functions in the project. The default `interface_t` object is set up so that all methods point to valid functions that simply report EXIT_FAILURE when calling them.

## implementation.h

```
struct implementation_t {
  int (*new)(struct interface_t* this);
  int (*old)(struct interface_t* this);
};

extern const struct implementation_t implementation_t;
```

The structure defines an implementation which consists solely of object lifetime methods. They are placed in a structure in order not to clutter the symbol table.

## implementation.c

```
static int method(struct interface_t* this) {
  FAIL_IF(this == NULL);
  printf("I'm a stateless implementation!\n");
  return EXIT_SUCCESS;
}

static const struct interface_t prototype = {
  .state = NULL,
  .method = method
};

static int new(struct interface_t* this) {
  FAIL_IF(this == NULL);
  *this = prototype;
  // Manage heap allocated state storage here.
  return EXIT_SUCCESS;
}

static int old(struct interface_t* this) {
  FAIL_IF(this == NULL);
  // Manage heap allocated state storage here.
  return EXIT_SUCCESS;
}

const struct implementation_t implementation_t = {
  .new = new,
  .old = old
};
```

The interface is implemented by defining the concrete methods and attaching them to an implementation prototype. The object lifetime methods configure a pointer to the object (stack allocated at the call site) by copying from the prototype. The object lifetime methods can also manage heap allocated state storage if needed by the implementation.

## main.c

```
int main(void) {
  struct interface_t implementation = interface_t;
  FAIL_IF(implementation_t.new(&implementation));
  FAIL_IF(implementation.method(&implementation));
  FAIL_IF(implementation_t.old(&implementation));
  return EXIT_SUCCESS;
}
```

The `implementation` is declared as having `struct interface_t` type and is initialized as a copy of the default `interface_t` object. This makes all function pointers callable by pointing them to the dummy methods. The object lifetime method `new` assigns the concrete methods from the prototype making the call to `method` print a message to the console and report EXIT_SUCCESS, preventing the `FAIL_IF` macro from reporting EXIT_FAILURE. The object lifetime method `old` needs to be called at the end since we cannot assume anything about the implementation, especially not about whether or not it manages state storage on the heap.
