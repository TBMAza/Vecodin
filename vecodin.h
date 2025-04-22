#ifndef VECODIN
#define VECODIN

#include <stdio.h>
#include <stdlib.h>

/*
 * VECODIN: The Vicodin of vectors
 * A minimal library to create and manipulate type-agnostic dynamic arrays
 * 
 * Available methods:
 *  vecodin_t(dtype, vecname): creates a new vector named 'vecname' of type 'dtype'
 *  vecodin_length(vecname): returns the length of 'vecname' vector
 *  vecodin_find(vecname, element, index): searches for 'element' in 'vecname' vector; if found, writes its index in 'index' variable, otherwise writes -1 in 'index'
 *  vecodin_append(vecname, element): inserts 'element' at the end of 'vecname' vector
 *  vecodin_prepend(vecname, element): inserts 'element' at the beginning of 'vecname' vector
 *  vecodin_clear(vecname): deletes all current elements in 'vecname' vector
 *  vecodin_delete(vecname): deletes all of 'vecname' vector's content and makes it no longe usable: to use when you're sure to no longer need a vector and before program termination;
 *  vecodin_rmh(vecname): remove head; deletes 'vecname' vector's first element
 *  vecodin_rmt(vecname): remove tail; deletes 'vecname' vector's last element
 *  vecodin_rm(vecname, index): deletes element at index 'index' in 'vecname' vector
 *  vecodin_ps(vecname, position, element): place and shift; places new 'element' at index 'index' after shifting pre-existing values to the right
 *  vecodin_cp(vec1, vec2): copies the content of 'vec2' into 'vec1'
 *  vecodin_range(vecname, s, e, destination): takes 'vecname' vector's sub-vector that ranges from index 's' to index 'e' (both inclusive) and stores it in 'destination' vector
 *  vecodin_cat(vec1, vec2, destination): stores in 'destination' vector the result of the concatenation of 'vec1' and 'vec2' vectors
 */

/*
 * vecodin_t: initializes to zero a new vector named 'vecname' of type 'dtype';
 * vecodin_##vecname##_size: actual size of the vector, i.e. total number of cells available (initially 1);
 * vecodin_##vecname##_curs: next position available for appending a new value;
 * vecname##_length: number of elements currently stored in the vector;
 * vecodin_##vecname##_realloc_buffer: used to perform realloc() and check if memory allocation was successfull before making 'vecname' point to the resized vector;
 */
#define vecodin_t(dtype, vecname) \
    dtype* vecname = (dtype*) calloc(1, sizeof(dtype)); \
    if(!vecname) {fprintf(stderr, "[vecodin] [CRITICAL] %s allocation failed!\n", "##vecname##");} \
    dtype* vecodin_##vecname##_realloc_buffer = NULL; \
    size_t vecodin_##vecname##_size = 1, \
           vecodin_##vecname##_curs = 0, \
           vecodin_##vecname##_length = 0; \

/*
 * vecodin_length: returns number of elements in 'vecname';
 */
#define vecodin_length(vecname) vecodin_##vecname##_length

/*
 * vecodin_find: sets a given variable 'index' of type long long to the index of 'element' in 'vecname' if found,
 * sets 'index' to -1 otherwise;
 */
#define vecodin_find(vecname, element, index) \
    { \
        index = -1; \
        for(long long i = 0; i < vecodin_##vecname##_curs; ++i) { \
            if(vecname[i] == element) { \
                index = i; \
                break; \
            } \
        } \
    }

/*
 * vecodin_append: inserts 'element' at the end of 'vecname' and expands 'vecname' if it becomes full;
 */
#define vecodin_append(vecname, element) \
    { \
        vecname[vecodin_##vecname##_curs] = element; \
        ++vecodin_##vecname##_length; \
        ++vecodin_##vecname##_curs; \
        if(vecodin_##vecname##_curs >= vecodin_##vecname##_size) { \
            vecodin_##vecname##_size *= 2; \
            vecodin_##vecname##_realloc_buffer = realloc(vecname, sizeof(vecname[0]) * vecodin_##vecname##_size); \
            if(!vecodin_##vecname##_realloc_buffer) { \
                fprintf(stderr, "[vecodin] [CRITICAL] %s resize failed!\n", "##vecname##"); \
                vecodin_##vecname##_size /= 2; \
            } \
            else { \
                vecname = vecodin_##vecname##_realloc_buffer; \
                vecodin_##vecname##_realloc_buffer = NULL; \
            } \
        } \
    }

/*
 * vecodin_prepend: inserts 'element' at the beginning of 'vecname' after shifting all the other elements one place to the right;
 * expands 'vecname' if it becomes full;
 */
#define vecodin_prepend(vecname, element) \
    { \
        for(size_t i = vecodin_##vecname##_curs; i > 0; --i) { vecname[i] = vecname[i-1]; } \
        vecname[0] = element; \
        ++vecodin_##vecname##_length; \
        ++vecodin_##vecname##_curs; \
        if(vecodin_##vecname##_curs >= vecodin_##vecname##_size) { \
            vecodin_##vecname##_size *= 2; \
            vecodin_##vecname##_realloc_buffer = realloc(vecname, sizeof(vecname[0]) * vecodin_##vecname##_size); \
            if(!vecodin_##vecname##_realloc_buffer) { \
                fprintf(stderr, "[vecodin] [CRITICAL] %s resize failed!\n", "##vecname##"); \
                vecodin_##vecname##_size /= 2; \
            } \
            else { \
                vecname = vecodin_##vecname##_realloc_buffer; \
                vecodin_##vecname##_realloc_buffer = NULL; \
            } \
        } \
    }

/*
 * vecodin_clear: deletes all of 'vecname' vector's content and reinitializes it to the minimum size (1);
 */
#define vecodin_clear(vecname) \
    { \
        if(vecodin_##vecname##_size != -1) { \
            size_t vecodin_##vecname##_element_size = sizeof(vecname[0]); \
            vecodin_##vecname##_size = 1; \
            vecodin_##vecname##_curs = 0; \
            vecodin_##vecname##_length = 0; \
            free(vecname); \
            vecname = calloc(1, vecodin_##vecname##_element_size); \
            if(!vecname) { fprintf(stderr, "[vecodin] [CRITICAL] %s allocation failed!\n", "##vecname##"); }; \
        } \
    }

/*
 * vecodin_delete: deletes all of 'vecname' vector's content and sets it to NULL;
 * this operation make 'vecname' no longer usable;
 * it's best practice to call it before program termination on all vectors;
 */
#define vecodin_delete(vecname) \
    { \
        vecodin_##vecname##_size = -1; \
        vecodin_##vecname##_curs = -1; \
        vecodin_##vecname##_length = -1; \
        if(vecname) { free(vecname); } \
        vecname = NULL; \
    }

/*
 * vecodin_rmh: deletes first element from 'vecname';
 * shifts every element one place to the left;
 * shrinks 'vecname' if needed (if elements count go below half of vector size);
 */
#define vecodin_rmh(vecname) \
    { \
        for(size_t i = 0; i < vecodin_##vecname##_curs - 1; ++i) { vecname[i] = vecname[i+1]; } \
        --vecodin_##vecname##_length; \
        --vecodin_##vecname##_curs; \
        if(vecodin_##vecname##_curs < vecodin_##vecname##_size / 2) { \
            vecodin_##vecname##_size /= 2; \
            vecodin_##vecname##_realloc_buffer = realloc(vecname, sizeof(vecname[0]) * vecodin_##vecname##_size); \
            if(!vecodin_##vecname##_realloc_buffer) { \
                fprintf(stderr, "[vecodin] [CRITICAL] %s resize failed!\n", "##vecname##"); \
                vecodin_##vecname##_size *= 2; \
            } \
            else { \
                vecname = vecodin_##vecname##_realloc_buffer; \
                vecodin_##vecname##_realloc_buffer = NULL; \
            } \
        } \
    }

/*
 * vecodin_rmt: deletes last element from 'vecname';
 * shrinks 'vecname' if needed (if elements count go below half of vector size);
 */
#define vecodin_rmt(vecname) \
    { \
        if(vecodin_##vecname##_curs > 0) { \
            --vecodin_##vecname##_length; \
            --vecodin_##vecname##_curs; \
        } \
        if(vecodin_##vecname##_curs < vecodin_##vecname##_size / 2) { \
            vecodin_##vecname##_size /= 2; \
            vecodin_##vecname##_realloc_buffer = realloc(vecname, sizeof(vecname[0]) * vecodin_##vecname##_size); \
            if(!vecodin_##vecname##_realloc_buffer) { \
                fprintf(stderr, "[vecodin] [CRITICAL] %s resize failed!\n", "##vecname##"); \
                vecodin_##vecname##_size *= 2; \
            } \
            else { \
                vecname = vecodin_##vecname##_realloc_buffer; \
                vecodin_##vecname##_realloc_buffer = NULL; \
            } \
        } \
    }

/*
 * vecodin_rm: deletes element at index 'index' from 'vecname';
 * shrinks 'vecname' if needed (if elements count go below half of vector size);
 */
#define vecodin_rm(vecname, index) \
    { \
        if(index < vecodin_##vecname##_curs - 1) { \
            for(size_t i = index; i < vecodin_##vecname##_curs - 1; ++i) { vecname[i] = vecname[i+1]; } \
        } \
        if(vecodin_##vecname##_curs > 0) { \
            --vecodin_##vecname##_length; \
            --vecodin_##vecname##_curs; \
        } \
        if(vecodin_##vecname##_curs < vecodin_##vecname##_size / 2) { \
            vecodin_##vecname##_size /= 2; \
            vecodin_##vecname##_realloc_buffer = realloc(vecname, sizeof(vecname[0]) * vecodin_##vecname##_size); \
            if(!vecodin_##vecname##_realloc_buffer) { \
                fprintf(stderr, "[vecodin] [CRITICAL] %s resize failed!\n", "##vecname##"); \
                vecodin_##vecname##_size *= 2; \
            } \
            else { \
                vecname = vecodin_##vecname##_realloc_buffer; \
                vecodin_##vecname##_realloc_buffer = NULL; \
            } \
        } \
    }

/*
 * vecodin_ps: inserts 'element' at index 'position' after shifting all the other elements one place to the right;
 * expands 'vecname' if it becomes full;
 */
#define vecodin_ps(vecname, position, element) \
    { \
        for(size_t i = vecodin_##vecname##_curs; i > position; --i) { vecname[i] = vecname[i-1]; } \
        vecname[position] = element; \
        ++vecodin_##vecname##_length; \
        ++vecodin_##vecname##_curs; \
        if(vecodin_##vecname##_curs >= vecodin_##vecname##_size) { \
            vecodin_##vecname##_size *= 2; \
            vecodin_##vecname##_realloc_buffer = realloc(vecname, sizeof(vecname[0]) * vecodin_##vecname##_size); \
            if(!vecodin_##vecname##_realloc_buffer) { \
                fprintf(stderr, "[vecodin] [CRITICAL] %s resize failed!\n", "##vecname##"); \
                vecodin_##vecname##_size /= 2; \
            } \
            else { \
                vecname = vecodin_##vecname##_realloc_buffer; \
                vecodin_##vecname##_realloc_buffer = NULL; \
            } \
        } \
    }

/*
 *  vecodin_cp: copiest the content of 'vec2' into 'vec1';
 *  beware: the old content of 'vec1', if any, is erased;
 */
#define vecodin_cp(vec1, vec2) \
    { \
        if(vecodin_##vec1##_size != -1) { \
            vecodin_##vec1##_realloc_buffer = calloc(vecodin_##vec2##_size, sizeof(vec1[0])); \
            if(!vecodin_##vec1##_realloc_buffer) { fprintf(stderr, "[vecodin] [CRITICAL] %s resize failed!\n", "##vec1##"); } \
            else { \
                vecodin_##vec1##_size = vecodin_##vec2##_size; \
                vecodin_##vec1##_curs = vecodin_##vec2##_curs; \
                vecodin_##vec1##_length = vecodin_##vec2##_length; \
                free(vec1); \
                vec1 = vecodin_##vec1##_realloc_buffer; \
                vecodin_##vec1##_realloc_buffer = NULL; \
                for(size_t i = 0; i < vecodin_##vec2##_curs; ++i) { vec1[i] = vec2[i]; } \
            } \
        } \
    }

/*
 *  vecodin_range: copies the content in the [s, e] inclusive range of indexes into 'destination', which can even be 'vecname' itself;
 */
#define vecodin_range(vecname, s, e, destination) \
    { \
        if(vecodin_##destination##_size != -1 && s <= e) { \
            size_t vecodin_intermediate_destination_size = e - s + 2; \
            size_t vecodin_intermediate_destination_curs = e + 1; \
            size_t vecodin_intermediate_destination_length = e; \
            vecodin_##destination##_realloc_buffer = calloc(vecodin_intermediate_destination_size, sizeof(destination[0])); \
            if(!vecodin_##destination##_realloc_buffer) { fprintf(stderr, "[vecodin] [CRITICAL] %s resize failed!\n", "##destination##"); } \
            else { \
                for(size_t i = 0; i <= vecodin_intermediate_destination_length; ++i) { vecodin_##destination##_realloc_buffer[i] = vecname[i+s]; } \
                vecodin_##destination##_size = vecodin_intermediate_destination_size; \
                vecodin_##destination##_curs = vecodin_intermediate_destination_curs; \
                vecodin_##destination##_length = vecodin_intermediate_destination_length; \
                free(destination); \
                destination = vecodin_##destination##_realloc_buffer; \
                vecodin_##destination##_realloc_buffer = NULL; \
            } \
        } \
    }

/*
 *  vecodin_cat: concatenates 'vec1' and 'vec2' and stores the result in 'destination';
 *  'destination' can be even 'vec1' or 'vec2';
 */
#define vecodin_cat(vec1, vec2, destination) \
    { \
        if(vecodin_##destination##_size != -1) { \
            size_t vecodin_intermediate_destination_size = vecodin_##vec1##_size + vecodin_##vec2##_size; \
            size_t vecodin_intermediate_destination_curs = vecodin_##vec1##_curs + vecodin_##vec2##_curs; \
            size_t vecodin_intermediate_destination_length = vecodin_##vec1##_length + vecodin_##vec2##_length; \
            vecodin_##destination##_realloc_buffer = calloc(vecodin_intermediate_destination_size, sizeof(destination[0])); \
            if(!vecodin_##destination##_realloc_buffer) { fprintf(stderr, "[vecodin] [CRITICAL] %s resize failed!\n", "##destination##"); } \
            else { \
                for(size_t i = 0; i < vecodin_intermediate_destination_curs; ++i) { vecodin_##destination##_realloc_buffer[i] = i < vecodin_##vec1##_curs ? vec1[i] : vec2[i]; } \
                vecodin_##destination##_size = vecodin_intermediate_destination_size; \
                vecodin_##destination##_curs = vecodin_intermediate_destination_curs; \
                vecodin_##destination##_length = vecodin_intermediate_destination_length; \
                free(destination); \
                destination = vecodin_##destination##_realloc_buffer; \
                vecodin_##destination##_realloc_buffer = NULL; \
            } \
        } \
    }

#endif
