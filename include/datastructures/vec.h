#ifndef NECS_VEC_H
#define NECS_VEC_H

#include <stddef.h>
#include <stdint.h>

/** Dynamic array.
 *
 * Stores elements in a contigunous memory block.
 * Elements are stored densely and indexed form 0 to size - 1
 */
typedef struct ecs_vec_t {
  void *data;
  size_t element_size;
  uint32_t count;
  uint32_t cap;
} ecs_vec_t;

/**
 * Initialize a vector.
 *
 * @param v Pointer to the vector.
 * @param element_size Size of single element in bytes.
 * @param initial_cap  Initial capacity of the vector.
 *
 * @note The vector must be destroyed with ecs_vec_fini.
 */
void ecs_vec_init(ecs_vec_t *v, size_t element_size, uint32_t initial_cap);

/**
 * Destroy a vector.
 *
 * @param v Pointer to the vector.
 */
void ecs_vec_fini(ecs_vec_t *v);

/**
 * Increase size of a vector.
 *
 * @param v Pointer to the vector.
 * @param new_cap new capacity of the vector.
 *
 * @note capacity changes only if new_cap > v->cap.
 */
void ecs_vec_grow(ecs_vec_t *v, uint32_t new_cap);

/**
 * Change size of a vector to 0;
 *
 * @param v Pointer to the vector.
 */
void ecs_vec_clear(ecs_vec_t *v);

/**
 * Create new element.
 *
 * @param v Pointer to the vector
 * @return Returns pointer to newly created element.
 *
 * @warning Returned pointer becomes invalid if the vector is modified.
 */
void *ecs_vec_append(ecs_vec_t *v);

/**
 * Get raw pointer to vector data.
 *
 * @param v pointer to the vector.
 * @return Pointer to internal data buffer.
 *
 * @note The retured pointer is owned by the vector.
 * @note It becomes invalid after any modifying operation.
 *
 * @warning Returned pointer becomes invalid if the vector is modified.
 */
void *ecs_vec_data(const ecs_vec_t *v);

/**
 * Get pointer to an element at index.
 *
 * @param v Pointer to the vector.
 * @param index Index of the element (0 <= index < size).
 * @return Returns pointer to element at the index.
 *
 * @warning Returned pointer becomes invalid if the vector is modified.
 */
void *ecs_vec_get(const ecs_vec_t *v, uint32_t index);

/**
 * Get pointer to the last element in the vector.
 *
 * @param v pointer to the vector.
 * @return Returns pointer to element at the index.
 *
 * @warning Returned pointer becomes invalid if the vector is modified.
 */
void *ecs_vec_get_last(const ecs_vec_t *v);

/**
 * Remove element at the index.
 * Swap it with the last element in the vector.
 *
 * @param v Pointer to the vector.
 * @param index Index of the element (0 <= index < size).
 */
void ecs_vec_remove(ecs_vec_t *v, uint32_t index);

/**
 * Get number of elements in the vector.
 *
 * @param v Pointer to the vector.
 */
uint32_t ecs_vec_size(const ecs_vec_t *v);

#endif // NECS_VEC_H
