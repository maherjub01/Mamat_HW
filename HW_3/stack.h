#ifndef _STACK_
#define _STACK_

#include <stddef.h>  /* size_t */
#include <stdbool.h> /* bool   */ 
#include "stdlib.h"
#include "stdio.h"

typedef enum { SUCCESS = 0, FAIL } Result;
typedef void *elem_t;
typedef elem_t (*clone_t)(elem_t e);
typedef void (*destroy_t)(elem_t e);
typedef void (*print_t)(elem_t e);



typedef struct stack{

    size_t max_num_of_elem;
    elem_t *arr;
    size_t top;
    clone_t clone_func;
    destroy_t destroy_func;
    print_t print_func;

}*pstack_t;

typedef elem_t (*clone_t)(elem_t e);
typedef void (*destroy_t)(elem_t e);
typedef void (*print_t)(elem_t e);



pstack_t stack_create(size_t max_num_of_elem, clone_t clone_func, destroy_t destroy_func, print_t print_func);
Result stack_destroy(pstack_t stack);
Result stack_push(pstack_t stack, elem_t new_elem);
void stack_pop(pstack_t stack);
elem_t stack_peek(pstack_t stack);
size_t stack_size(pstack_t stack);
bool stack_is_empty(pstack_t stack);
size_t stack_capacity(pstack_t stack);
void stack_print(pstack_t stack);


#endif /* _STACK_ */
