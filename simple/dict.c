#include <assert.h>
#include <stdlib.h>

#include "bst.h"
#include "dict.h"
#include "list.h"


struct _dict_t {
    bst_t bst;
    unsigned int length;
};

dict_t dict_empty(void) {
    dict_t result = NULL;

    result = calloc(1, sizeof(struct _dict_t));
    assert(result != NULL);
    result->bst = bst_empty();
    result->length = 0;

    /* POST */
    assert(dict_length(result) == 0);

    return (result);
}

dict_t dict_destroy(dict_t dict) {
    if (dict != NULL) {
        dict->bst = bst_destroy(dict->bst);
        dict->length = 0;
        free(dict);
        dict = NULL;
    }

    return (dict);
}

unsigned int dict_length(dict_t dict) {
    /* PRE */
    assert(dict != NULL);

    return (dict->length);
}

bool dict_is_equal(dict_t dict, dict_t other) {
    /* PRE */
    assert(dict != NULL && other != NULL);

    bool result = false;

    result = bst_is_equal(dict->bst, other->bst) &&
        dict->length == other->length;

    return (result);
}

bool dict_exists(dict_t dict, word_t word) {
    /* PRE */
    assert(dict != NULL && word != NULL);

    bool result = false;
    index_t index = NULL;

    index = index_from_string(word);
    result = bst_search(dict->bst, index) != NULL;
    free(index);

    return (result);
}

def_t dict_search(dict_t dict, word_t word) {
    /* PRE */
    assert(dict != NULL && word != NULL && dict_exists(dict, word));

    def_t result = NULL;
    index_t index = NULL;

    index = index_from_string(word);
    result = data_to_string(bst_search(dict->bst, index));
    free(index);

    /* POST */
    assert(result != NULL);

    return (result);
}

dict_t dict_add(dict_t dict, word_t word, def_t def) {
    /* PRE */
    assert(dict != NULL && word != NULL && def != NULL &&
           !dict_exists(dict, word));

    index_t index = NULL;
    data_t data = NULL;

    index = index_from_string(word);
    data = data_from_string(def);
    dict->bst = bst_add(dict->bst, index, data);
    dict->length += 1;

    return (dict);
}

dict_t dict_remove(dict_t dict, word_t word) {
    /* PRE */
    assert(dict != NULL && word != NULL && dict_exists(dict, word));

    index_t index = NULL;

    index = index_from_string(word);
    dict->bst = bst_remove(dict->bst, index);
    dict->length -= 1;
    free(index);

    return (dict);
}

dict_t dict_copy(dict_t dict) {
    dict_t result = NULL;

    result = calloc(1, sizeof(struct _dict_t));
    assert(result != NULL);
    result->bst = bst_copy(dict->bst);
    result->length = dict->length;

    /* POST */
    assert(result != NULL && dict_is_equal(result, dict));

    return (result);
}

void dict_dump(dict_t dict, FILE * fd) {
    /* PRE */
    assert(dict != NULL && fd != NULL);

    list_t list = NULL;

    list = list_empty();
    list = bst_to_list(dict->bst, list);
    list_dump(list, fd);
    list = list_destroy(list);
}
