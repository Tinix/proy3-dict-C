#include <assert.h>
#include <stdlib.h>

#include "list.h"
#include "pair.h"
#include "stack.h"


struct _node_t {
    pair_t elem;
    stack_t next;
};

stack_t stack_empty(void) {
    stack_t result = NULL;

    return (result);
}

bool stack_is_empty(stack_t stack) {
    return (stack == NULL);
}

stack_t stack_push(pair_t pair, stack_t stack) {
    stack_t node = NULL;

    node = calloc(1, sizeof(struct _node_t));
    assert(node != NULL);
    node->elem = pair;
    node->next = stack;
    stack = node;

    return (stack);
}

pair_t stack_top(stack_t stack) {
    assert(!stack_is_empty(stack));

    return (stack->elem);
}

stack_t stack_pop(stack_t stack) {
    assert(!stack_is_empty(stack));

    stack_t node = NULL;

    node = stack;
    stack = stack->next;
    node->elem = pair_destroy(node->elem);
    free(node);

    return (stack);
}

stack_t stack_destroy(stack_t stack) {
    while (!stack_is_empty(stack)) {
        stack = stack_pop(stack);
    }

    return (stack);
}
