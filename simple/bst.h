#ifndef BST_H
#define BST_H

#include <stdio.h>
#include <stdbool.h>

#include "data.h"
#include "index.h"
#include "list.h"


typedef struct _tree_node_t *bst_t;

bst_t bst_empty(void);
/*
 * Returns a newly created, empty binary search tree (BST).
 *
 * The caller must call bst_destroy when done using the resulting BST,
 * so the resources allocated by this BST constructor are freed.
 *
 */

bst_t bst_destroy(bst_t bst);
/*
 * Free the resources allocated for the given ’bst’, and set it to NULL.
 */

unsigned int bst_length(bst_t bst);
/*
 * Returns the number of elements in the given ’bst’.
 * This method has a linear order complexity.
 */

bool bst_is_equal(bst_t bst, bst_t other);
/*
 * Returns whether the given ’bst’ is equal to ’other’.
 *
 * Equality is defined by comparing both BSTs, node by node, and ensuring that
 * each node is equal as a whole (ie, that both pairs are equal).
 */

data_t bst_search(bst_t bst, index_t index);
/*
 * Returns the data associated to the given ’index’ in the given ’bst’,
 * or NULL if the ’index’ is not in ’bst’.
 *
 * The caller must NOT free the resources allocated for the result when done
 * using it.
 */

bst_t bst_add(bst_t bst, index_t index, data_t data);
/*
 * Returns the given ’bst’ with the pair (’index’, ’data’) added to it.
 *
 * The given ’index’ and ’data’ are inserted in the BST,
 * so they can not be destroyed by the caller (they will be destroyed when
 * bst_destroy is called).
 *
 * PRE: Also, there is no pair in the given BST such as its index is equal to
 * ’index’ (this means, bst_search for ’index’ must be NULL).
 *
 * POST: the length of the result is the same as the length of ’bst’
 * plus one. The elements of the result are the same as the ones in ’bst’
 * with the new pair (’index’, ’data’) added accordingly (see:
 * http://en.wikipedia.org/wiki/Binary_search_tree
 * for specifications about behavior).
 */

bst_t bst_remove(bst_t bst, index_t index);
/*
 * Returns the given ’bst’ with the pair which index is equal to ’index’
 * removed.
 *
 * Please note that ’index’ may not be in the BST (thus an unchanged
 * BST is returned).
 *
 *
 * POST: the length of the result is the same as the length of ’bst’
 * minus one if ’index’ existed in ’bst’. The elements of the result are
 * the same as the ones in ’bst’ with the entry for ’index’ removed.
 */

bst_t bst_copy(bst_t bst);
/*
 * Returns a newly created copy of the given ’bst’.
 *
 * The caller must call bst_destroy when done using the resulting BST,
 * so the resources allocated by this BST contructor are freed.
 *
 * POST: the result is an exact copy of ’bst’.
 * In particular, bst_is_equal(result, bst) holds.
 */

list_t bst_to_list(bst_t bst, list_t list);
/*
 * This function appends to the given ’list’ a copy of all the
 * elements of the ’bst’ in ascending order.
 *
 * The result’s length is equal to bst_length(bst)
 * plus list_length(list).
 *
 * In particular, a call to bst_to_list(bst, list_empty()) will return
 * a sorted list with all and only the elements of the ’bst’.
 */

/* All the functions assume that the input pointers are *valid*: that
 * is, depending on the implementation, the pointers must point either
 * to ’NULL’ or to a well-formed structure. It is guaranteed that the
 * pointers remain valid after the execution of the functions.
 */

#endif
