# Vecodin – The Vicodin of Vectors
**Type-agnostic dynamic arrays in C, without the pain.**

Vecodin is a minimal, single-header C library that brings dynamic array functionality (vectors) to C in a type-agnostic, macro-based style. You can use it with any type — integers, floats, strings, structs, and more — while keeping full control over performance and memory.

---

## Quick Start

```c
#include "vecodin.h"

int main() {
    vecodin_t(int, vi);
    vecodin_append(vi, 10);
    vecodin_append(vi, 20);
    printf("Length: %zu, First: %d\n", vecodin_length(vi), vi[0]);
}
```

---

## Features

- **Single header** – just drop it in your project
- **Type-agnostic** – works with any C data type
- **Macro-based** – no structs, typedefs, or templates needed
- **Automatic resizing** – no manual reallocs
- **Reusability** – vectors can be cleared and reused
- **Well-tested** – with automated test coverage

---

## 🔧 API Reference

### Initialization
```c
vecodin_t(dtype, vecname)
```
Creates a dynamic vector `vecname` of type `dtype`.

---

### Metadata
```c
vecodin_length(vecname)
```
Returns number of elements stored in the vector.

---

### Core Operations

```c
vecodin_append(vecname, element)
vecodin_prepend(vecname, element)
vecodin_rm(vecname, index)
vecodin_rmh(vecname)        // Remove head
vecodin_rmt(vecname)        // Remove tail
vecodin_clear(vecname)
vecodin_ps(vecname, pos, element) // Place & shift
vecodin_find(vecname, element, index_var)
```

---

### Composite Operations

```c
vecodin_cp(vec1, vec2)                        // Copy vec2 into vec1
vecodin_range(vec, start, end, dest)          // Copy [start, end] into dest
vecodin_cat(vec1, vec2, dest)                 // Concatenate into dest
```

---

## Example: Using with Multiple Types

```c
vecodin_t(float, vf);
vecodin_append(vf, 3.14f);

vecodin_t(char*, vs);
vecodin_append(vs, "hello");

typedef struct { int id; char name[16]; } Person;
vecodin_t(Person, vp);
vecodin_append(vp, (Person){1, "Alice"});
```

---

## Testing

The project includes two test files located in the `tests/` directory.

To build and run all tests:

```bash
cd tests
make run
```

To clean up:

```bash
make clean
```

Tests include:
- Operations with `int`, `float`, `char*`, and custom `struct` types
- All vector operations: append, prepend, remove, clear, copy, range, concat
- Automated PASS/FAIL output per check

---

## Limitations

- Macros are **not scope-safe**: variables like `vecodin_<vecname>_length` are global.
- No thread safety
- Doesn’t own `char*` strings — you manage your own memory if needed
- Macros can make debugging harder (use `.i` preprocessed output for help)

---

## License

MIT License. Do what you want — but attribution is appreciated.

---

## Author

Crafted with painkillers and pointer arithmetic by A. Asaduz.

---

> “Vecodin — because C deserves vectors too.”
