#ifndef NECS_SPARSE_H
#define NECS_SPARSE_H

#include "vec.h"
#include <stddef.h>
#include <stdint.h>

/** Sparse Set.
 *
 * Map entity id to dense indices.
 * Provides O(1) add, remove and lookup operations.
 */
typedef struct ecs_sparse_t {
  ecs_vec_t dense_element; /* dense array to store components */
  ecs_vec_t
      dense_id; /* dense array parallel to dense_element to store entity id */
  uint32_t sparse_id;  /* sparse array that stores id of entity in
                          dense_id and dense_element*/
  uint32_t sparse_cap; /* capacity of sparse array */
  uint32_t count;      /* count of alive elements in sparse array */
  size_t element_size;
} ecs_sparse_t;

/**
 * Initialize a sparse set.
 *
 * @param s Pointer to the sparse set.
 * @param element_size Size of a component in bytes.
 * @param sparse_cap Max number of entites in sparse array.
 *
 * @note The sparse set must be destroyed with ecs_sparse_fini.
 */
void ecs_sparse_init(ecs_sparse_t *s, size_t element_size, uint32_t sparse_cap);

/**
 * Destroy a sparse set.
 *
 * @param s Pointer to the sparse set.
 */
void ecs_sparse_fini(ecs_sparse_t *s);

/**
 * Check if entity has a component inside a sparse set.
 *
 * @param s Pointer to the sparse set.
 * @param entity_id Id of the entity (0 <= entity_id < sparse_cap).
 * @return Returns true if entity has a component.
 */
bool ecs_sparse_has(ecs_sparse_t *s, uint32_t entity_id);

/**
 * Create new element in dense array.
 *
 * @param s Pointer to the sparse set.
 * @return Returns pointer to newly created component.
 *
 * @note Returns NULL if the entity already have a component.
 *
 * @warning Returned pointer becomes invalid if the sparse set is modified.
 */
void *ecs_sparse_add(ecs_sparse_t *s);

/**
 * Get a pointer to a component of an entity.
 *
 * @param s Pointer to the sparse set.
 * @param entity_id Id of the entity (0 <= entity_id < sparse_cap).
 * @return Returns pointer to a component of the entity.
 *
 * @note Returns NULL if the entity doesn't have a component.
 *
 * @warning Returned pointer becomes invalid if the sparse set is modified.
 */
void *ecs_sparse_get(const ecs_sparse_t *s, uint32_t entity_id);

/**
 * Removes component of an entity.
 *
 * @param s Pointer to the sparse set.
 * @param entity_id Id of the entity (0 <= entity_id < sparse_cap).
 */
void ecs_sparse_remove(ecs_sparse_t *s, uint32_t entity_id);

/**
 * Get pointer to the component in dense array.
 *
 * @param s Pointer to the sparse set.
 * @param index Index of dense array (0 <= index < count).
 * @return Returns pointer to element at the index of dense array.
 *
 * @warning Returned pointer becomes invalid if the sparse set is modified.
 */
void *ecs_sparse_component_at(const ecs_sparse_t *s, uint32_t index);

/**
 * Get entity id.
 *
 * @param s Pointer to the sparse set.
 * @param index Index of dense array (0 <= index < count).
 * @return Returns entity id at the index of dense array.
 */
uint32_t ecs_sparse_entity_at(const ecs_sparse_t *s, uint32_t index);

/**
 * Get number of components in a sparse set.
 *
 * @param s Pointer to the sparse set.
 */
uint32_t ecs_sparse_count(const ecs_sparse_t *s);

#endif // NECS_SPARSE_H
