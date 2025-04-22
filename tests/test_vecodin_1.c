#include <stdio.h>
#include <string.h>
#include <stdlib.h>
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

int main(void) {
    // Create vector
    vecodin_t(int, vi);
    CHECK(vi != NULL, "vecodin_t creates vector");

    // Append 5 elements
    for (int i = 1; i <= 5; ++i)
        vecodin_append(vi, i);
    CHECK(vecodin_vi_length == 5, "append 5 elements");

    // Prepend 0
    vecodin_prepend(vi, 0);
    CHECK(vi[0] == 0 && vecodin_vi_length == 6, "prepend 0");

    // Find element
    long long idx;
    vecodin_find(vi, 3, idx);
    CHECK(idx == 3, "find element 3");

    vecodin_find(vi, 42, idx);
    CHECK(idx == -1, "find non-existent element");

    // Remove tail
    int last = vi[vecodin_vi_length - 1];
    vecodin_rmt(vi);
    CHECK(vecodin_vi_length == 5 && vi[vecodin_vi_length - 1] != last, "remove tail");

    // Remove head
    int head = vi[0];
    vecodin_rmh(vi);
    CHECK(vecodin_vi_length == 4 && vi[0] != head, "remove head");

    // Remove index
    int before = vi[1];
    vecodin_rm(vi, 1); // remove second element
    CHECK(vecodin_vi_length == 3 && vi[1] != before, "remove index");

    // Place and shift
    vecodin_ps(vi, 1, 99);
    CHECK(vecodin_vi_length == 4 && vi[1] == 99, "insert at index 1");

    // Clear
    vecodin_clear(vi);
    CHECK(vecodin_vi_length == 0, "clear vector");

    // Reuse after clear
    vecodin_append(vi, 10);
    vecodin_append(vi, 20);
    CHECK(vecodin_vi_length == 2 && vi[0] == 10 && vi[1] == 20, "append after clear");

    // Copy
    vecodin_t(int, vi2);
    vecodin_cp(vi2, vi);
    CHECK(vecodin_vi2_length == vecodin_vi_length && vi2[0] == vi[0], "copy vector");

    // Range
    vecodin_append(vi, 30);
    vecodin_append(vi, 40);
    vecodin_t(int, vi_sub);
    vecodin_range(vi, 1, 2, vi_sub); // should get [20, 30]
    CHECK(vecodin_vi_sub_length == 2 && vi_sub[0] == 20 && vi_sub[1] == 30, "range from index 1 to 2");

    // Cat
    vecodin_t(int, vi_cat);
    vecodin_cat(vi, vi2, vi_cat);
    CHECK(vecodin_vi_cat_length == vecodin_vi_length + vecodin_vi2_length, "concatenate vi and vi2");

    // Final result
    printf("\nTotal Passed: %d | Failed: %d\n", passed, failed);
    return failed ? 1 : 0;
}
