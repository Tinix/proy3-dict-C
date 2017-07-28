#ifndef STACK_H
#define STACK_H

#include <stdio.h>
#include <stdbool.h>

#include "data.h"
#include "index.h"
#include "pair.h"


typedef struct _node_t *stack_t;

stack_t empty(void);

bool is_empty(stack_t stack);

stack_t push(pair_t pair, stack_t stack);

pair_t top(stack_t stack);

stack_t pop(stack_t stack);

stack_t destroy(stack_t stack);

#endif
