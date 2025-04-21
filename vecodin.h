#ifndef VECODIN
#define VECODIN

#include <stdio.h>
#include <stdlib.h>

/*
 * VECODIN: The Vicodin of vectors
 * A minimal library to create and manipulate type-agnostic dynamic arrays
 * Available methods:
 *  vecodin_t(dtype, vecname): creates a new vector named 'vecname' of type 'dtype'
 *  vecodin_length(vecname): returns the length of 'vecname' vector
 *  vecodin_find(vecname, element, index): searches for 'element' in 'vecname' vector; if found, writes its index in 'index' variable, otherwise writes -1 in 'index'
 *  vecodin_append(vecname, value): inserts 'value' at the end of 'vecname' vector
 *  vecodin_prepend(vecname, value): inserts 'value' at the beginning of 'vecname' vector
 *  vecodin_clear(vecname): deletes all current elements in 'vecname' vector
 *  vecodin_rmh(vecname): remove head; deletes 'vecname' vector's first element
 *  vecodin_rmt(vecname): remove tail; deletes 'vecname' vector's last element
 *  vecodin_rm(vecname, index): deletes element at index 'index' in 'vecname' vector
 *  vecodin_ps(vecname, position, element): place and shift; places new 'element' at index 'index' after shifting pre-existing values to the right [TODO]
 *  vecodin_cat(vec1, vec2, destination): stores in 'destination' vector the result of the concatenation of 'vec1' and 'vec2' vectors [TODO]
 *  vecodin_range(vecname, s, e, destination): takes 'vecname' vector's sub-vector that ranges from index 's' to index 'e' (both inclusive) and stores it in 'destination' vector [TODO]
 */

/*
 * vecodin_t: initializes to zero a new vector named 'vecname' of type 'dtype';
 * vecodin_##vecname##_size: actual size of the vector, i.e. total number of cells available (initially 1);
 * vecodin_##vecname##_curs: next position available for appending a new value;
 * vecname##_length: number of elements currently stored in the vector;
 * vecodin_##vecname##_realloc_buffer: used to perform realloc() and check if memory allocation was successfull before making 'vecname' point to the resized vector;
 */
#define vecodin_t(dtype, vecname) \
    dtype##* vecname = dtype##* calloc(1, sizeof(dtype)); \
    if(!vecname) printf("[vecodin] [CRITICAL] %s allocation failed!\n", "##vecname##"); \
    else { \
        dtype##* vecodin_##vecname##_realloc_buffer = NULL; \
        size_t vecodin_##vecname##_size = 1, \
               vecodin_##vecname##_curs = 0, \
               vecname##_length = 0; \
    }

/*
 * vecodin_length: returns number of elements in 'vecname';
 */
#define vecodin_length(vecname) vecodin_##vecname##_length;

/*
 * vecodin_find: sets a given variable 'index' of type long long to the index of 'element' in 'vecname' if found,
 * sets 'index' to -1 otherwise;
 */
#define vecodin_find(vecname, element, index) \
    index = -1; \
    for(long long i = 0; i < vecodin_##vecname##_curs; ++i) { \
        if(vecname[i] == element) index = i; \
        break; \
    }

/*
 * vecodin_append: inserts element 'value' at the end of 'vecname' and expands 'vecname' if it becomes full;
 */
#define vecodin_append(vecname, value) \
    vecname[vecodin_##vecname##_curs] = value; \
    ++vecodin_##vecname##_curs; \
    if(vecodin_##vecname##_curs >= vecodin_##vecname##_size) { \
        vecodin_##vecname##_size *= 2; \
        vecodin_##vecname##_realloc_buffer = realloc(vecname, sizeof(vecname[0]) * vecodin_##vecname##_size); \
        if(!vecodin_##vecname##_realloc_buffer) printf("[vecodin] [CRITICAL] %s resize failed!\n", "##vecname##"); \
        else { \
            vecname = vecodin_##vecname##_realloc_buffer; \
            free(vecodin_##vecname##_realloc_buffer); \
            vecodin_##vecname##_realloc_buffer = NULL; \
        } \
    }

/*
 * vecodin_prepend: inserts element 'value' at the beginning of 'vecname' after shifting all the other elements one place to the right;
 * expands 'vecname' if it becomes full;
 */
#define vecodin_prepend(vecname, value) \
    for(size_t i = vecodin_##vecname##_curs; i > 0; --i) vecname[i] = vecname[i-1]; \
    vecname[0] = value; \
    ++vecodin_##vecname##_curs; \
    if(vecodin_##vecname##_curs >= vecodin_##vecname##_size) { \
        vecodin_##vecname##_size *= 2; \
        vecodin_##vecname##_realloc_buffer = realloc(vecname, sizeof(vecname[0]) * vecodin_##vecname##_size); \
        if(!vecodin_##vecname##_realloc_buffer) printf("[vicodin] [CRITICAL] %s resize failed!\n", "##vecname##"); \
        else { \
            vecname = vecodin_##vecname##_realloc_buffer; \
            free(vecodin_##vecname##_realloc_buffer); \
            vecodin_##vecname##_realloc_buffer = NULL; \
        } \
    }

/*
 * vecodin_clear: deletes all of 'vecname' vector's content and reinitializes it to the minimum size (1);
 */
#define vecodin_clear(vecname) \
    size_t vecodin_##vecname##_element_size = sizeof(vecname[0]); \
    vecodin_##vecname##_size = 1; \
    vecodin_##vecname##_curs = 0; \
    vecname##_length = 0; \
    free(vecname); \
    vecname = calloc(1, sizeof(vecodin_##vecname##_element_size)); \
    if(!vecname) printf("[vecodin] [CRITICAL] %s allocation failed!\n", "##vecname##");

/*
 * vecodin_rmh: deletes first element from 'vecname';
 * shifts every element one place to the left;
 * shrinks 'vecname' if needed (if elements count go below half of vector size);
 */
#define vecodin_rmh(vecname) \
    for(size_t i = 0; i < vecodin_##vecname##_curs - 1; ++i) vecname[i] = vecname[i+1]; \
    --vecodin_##vecname##_curs; \
    if(vecodin_##vecname##_curs < vecodin_##vecname##_size / 2) { \
        vecodin_##vecname##_size /= 2; \
        vecodin_##vecname##_realloc_buffer = realloc(vecname, sizeof(vecname[0]) * vecodin_##vecname##_size); \
        if(!vecodin_##vecname##_realloc_buffer) printf("[vicodin] [CRITICAL] %s resize failed!\n", "##vecname##"); \
        else { \
            vecname = vecodin_##vecname##_realloc_buffer; \
            free(vecodin_##vecname##_realloc_buffer); \
            vecodin_##vecname##_realloc_buffer = NULL; \
        } \
    }

/*
 * vecodin_rmt: deletes last element from 'vecname';
 * shrinks 'vecname' if needed (if elements count go below half of vector size);
 */
#define vecodin_rmt(vecname) \
    --vecodin_##vecname##_curs; \
    if(vecodin_##vecname##_curs < vecodin_##vecname##_size / 2) { \
        vecodin_##vecname##_size /= 2; \
        vecodin_##vecname##_realloc_buffer = realloc(vecname, sizeof(vecname[0]) * vecodin_##vecname##_size); \
        if(!vecodin_##vecname##_realloc_buffer) printf("[vicodin] [CRITICAL] %s resize failed!\n", "##vecname##"); \
        else { \
            vecname = vecodin_##vecname##_realloc_buffer; \
            free(vecodin_##vecname##_realloc_buffer); \
            vecodin_##vecname##_realloc_buffer = NULL; \
        } \
    }

/*
 * vecodin_rm: deletes element at index 'index' from 'vecname';
 * shrinks 'vecname' if needed (if elements count go below half of vector size);
 */
#define vecodin_rm(vecname, index) \
    for(size_t i = index; i < vecodin_##vecname##_curs - 1; ++i) vecname[i] = vecname[i+1]; \
    --vecodin_##vecname##_curs; \
    if(vecodin_##vecname##_curs < vecodin_##vecname##_size / 2) { \
        vecodin_##vecname##_size /= 2; \
        vecodin_##vecname##_realloc_buffer = realloc(vecname, sizeof(vecname[0]) * vecodin_##vecname##_size); \
        if(!vecodin_##vecname##_realloc_buffer) printf("[vicodin] [CRITICAL] %s resize failed!\n", "##vecname##"); \
        else { \
            vecname = vecodin_##vecname##_realloc_buffer; \
            free(vecodin_##vecname##_realloc_buffer); \
            vecodin_##vecname##_realloc_buffer = NULL; \
        } \
    }

#endif