#include <assert.h>
#include <stdlib.h>

#include "bst.h"
#include "pair.h"


struct _tree_node_t {
    pair_t elem;
    bst_t left;
    bst_t right;
};

bst_t bst_empty(void) {
    bst_t result = NULL;

    return (result);
}

bst_t bst_destroy(bst_t bst) {
    if (bst != NULL) {
        bst->elem = pair_destroy(bst->elem);
        bst->left = bst_destroy(bst->left);
        bst->right = bst_destroy(bst->right);
        free(bst);
        bst = NULL;
    }

    return (bst);
}

unsigned int bst_length(bst_t bst) {
    unsigned int result = 0;

    if (bst != NULL) {
        result = 1 + bst_length(bst->left) + bst_length(bst->right);
    }

    return (result);
}

bool bst_is_equal(bst_t bst, bst_t other) {
    bool result = false;

    result = bst == NULL && other == NULL;
    if (bst != NULL && other != NULL) {
        result = pair_is_equal(bst->elem, other->elem) &&
            bst_is_equal(bst->left, other->left) &&
            bst_is_equal(bst->right, other->right);
    }

    return (result);
}

data_t bst_search(bst_t bst, index_t index) {
    data_t result = NULL;

    if (bst != NULL) {
        if (index_is_less_than(index, pair_fst(bst->elem))) {
            result = bst_search(bst->left, index);
        } else if (index_is_equal(index, pair_fst(bst->elem))) {
            result = pair_snd(bst->elem);
        } else {
            result = bst_search(bst->right, index);
        }
    }

    return (result);
}

bst_t bst_add(bst_t bst, index_t index, data_t data) {
    /* PRE */
    assert(bst_search(bst, index) == NULL);

    if (bst == NULL) {
        bst = calloc(1, sizeof(struct _tree_node_t));
        assert(bst != NULL);
        bst->elem = pair_from_index_data(index, data);
        bst->left = NULL;
        bst->right = NULL;
    } else {
        if (index_is_less_than(index, pair_fst(bst->elem))) {
            bst->left = bst_add(bst->left, index, data);
        } else if (!index_is_equal(index, pair_fst(bst->elem))) {
            bst->right = bst_add(bst->right, index, data);
        }
    }

    return (bst);
}

/* Dado un árbol, devuelve una copia del elemento del nodo maximal. */
pair_t bst_copy_max(bst_t bst) {
    assert(bst != NULL);

    pair_t result = NULL;

    if (bst->right == NULL) {
        result = pair_copy(bst->elem);
    } else {
        result = bst_copy_max(bst->right);
    }

    return (result);
}

/* Dado un árbol, elimina el nodo maximal. */
bst_t bst_delete_max(bst_t bst) {
    assert(bst != NULL);

    bst_t node = NULL;

    if (bst->right == NULL) {
        bst->elem = pair_destroy(bst->elem);
        node = bst;
        bst = bst->left;
        free(node);
    } else {
        bst->right = bst_delete_max(bst->right);
    }

    return (bst);
}

bst_t bst_remove(bst_t bst, index_t index) {
    bst_t node = NULL;

    if (bst != NULL) {
        if (index_is_less_than(index, pair_fst(bst->elem))) {
            bst->left = bst_remove(bst->left, index);
        } else if (index_is_equal(index, pair_fst(bst->elem))) {
            bst->elem = pair_destroy(bst->elem);
            if (bst->left == NULL) {
                node = bst;
                bst = bst->right;
                free(node);
            } else {
                bst->elem = bst_copy_max(bst->left);
                bst->left = bst_delete_max(bst->left);
            }
        } else {
            bst->right = bst_remove(bst->right, index);
        }
    }

    return (bst);
}

bst_t bst_copy(bst_t bst) {
    bst_t result = NULL;

    if (bst != NULL) {
        result = calloc(1, sizeof(struct _tree_node_t));
        assert(result != NULL);
        result->left = bst_copy(bst->left);
        result->elem = pair_copy(bst->elem);
        result->right = bst_copy(bst->right);
    }

    /* POST */
    assert(bst_is_equal(result, bst));

    return (result);
}

list_t bst_to_list(bst_t bst, list_t list) {
    if (bst != NULL) {
        list = bst_to_list(bst->left, list);
        list = list_append(list, index_copy(pair_fst(bst->elem)),
                           data_copy(pair_snd(bst->elem)));
        list = bst_to_list(bst->right, list);
    }

    return (list);
}
