#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../vecodin.h"

int passed = 0, failed = 0;

#define CHECK(cond, msg) do { \
    if (cond) { \
        printf("[PASS] %s\n", msg); \
        ++passed; \
    } else { \
        printf("[FAIL] %s\n", msg); \
        ++failed; \
    } \
} while (0)

// For struct tests
typedef struct {
    int id;
    char name[16];
} Person;

int main(void) {
    // === INT TEST ===
    vecodin_t(int, vi);
    for (int i = 1; i <= 3; ++i)
        vecodin_append(vi, i);
    CHECK(vecodin_vi_length == 3 && vi[0] == 1 && vi[2] == 3, "int: append and access");

    vecodin_prepend(vi, 0);
    CHECK(vi[0] == 0, "int: prepend");

    // === FLOAT TEST ===
    vecodin_t(float, vf);
    vecodin_append(vf, 3.14f);
    vecodin_append(vf, 2.71f);
    CHECK(vecodin_vf_length == 2 && vf[0] == 3.14f && vf[1] == 2.71f, "float: append and access");

    // === STRING TEST ===
    vecodin_t(char*, vs);
    vecodin_append(vs, "hello");
    vecodin_append(vs, "world");
    CHECK(strcmp(vs[0], "hello") == 0 && strcmp(vs[1], "world") == 0, "char*: append and access");

    // Copy string vector
    vecodin_t(char*, vs2);
    vecodin_cp(vs2, vs);
    CHECK(strcmp(vs2[0], "hello") == 0 && vecodin_vs2_length == vecodin_vs_length, "char*: copy vector");

    // === STRUCT TEST ===
    vecodin_t(Person, vp);
    Person p1 = { .id = 1, .name = "Alice" };
    Person p2 = { .id = 2, .name = "Bob" };
    vecodin_append(vp, p1);
    vecodin_append(vp, p2);
    CHECK(vecodin_vp_length == 2 && vp[1].id == 2 && strcmp(vp[1].name, "Bob") == 0, "struct: append and access");

    // Clear, reuse, and range
    vecodin_clear(vp);
    Person p3 = { .id = 3, .name = "Carol" };
    vecodin_append(vp, p3);
    CHECK(vecodin_vp_length == 1 && vp[0].id == 3, "struct: reuse after clear");

    // === Final report ===
    printf("\nTotal Passed: %d | Failed: %d\n", passed, failed);
    return failed ? 1 : 0;
}
