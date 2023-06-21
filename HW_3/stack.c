#include <stdio.h>
#include <stdlib.h>
#include "stack.h"


pstack_t stack_create(size_t max_num_of_elem, clone_t clone_func, destroy_t destroy_func, print_t print_func){


    pstack_t my_stack = malloc(sizeof(struct stack)); //allocate memory for stack

    if(my_stack == NULL){
        return NULL;
    }

    my_stack->max_num_of_elem = max_num_of_elem;

    my_stack->arr = malloc(max_num_of_elem*sizeof(void*)); //allocate memory for stack content

    if (my_stack->arr == NULL){

        return NULL;
    }


    my_stack->clone_func = clone_func;
    my_stack->destroy_func = destroy_func;
    my_stack->print_func = print_func;
    my_stack->top = 0;

    return my_stack;
}

Result stack_destroy(pstack_t stack){

    if (stack == NULL) {
        return FAIL;
    }

    free(stack);

    return SUCCESS;
}

Result stack_push(pstack_t stack, elem_t e){

    if (stack == NULL || e == NULL) {

        return FAIL;
    }

    if (stack->top > stack->max_num_of_elem-1){
        return FAIL;
    }

    elem_t new_element;
    new_element = stack->clone_func(e); // make a copy for the element
    stack->arr[stack->top] = new_element; // push the element to the stack
    stack->top++;
    return SUCCESS;
}

void stack_pop(pstack_t stack){

    if(stack == NULL || stack->max_num_of_elem == 0){
        return;
    }

    stack->destroy_func(stack->arr[stack->top-1]);
    stack->top--;
}

elem_t stack_peek(pstack_t stack){

    if(stack == NULL){

        return NULL;
    }
    return stack->arr[stack->top-1];
}

size_t stack_size(pstack_t stack){

    return stack->top;
}

bool stack_is_empty(pstack_t stack){

    if( stack == NULL){
        return false;
    }
    if(stack->top == 0){
        return true;
    }
    return false;

}

size_t stack_capacity(pstack_t stack){

    return stack->max_num_of_elem - stack_size(stack);
}

// printing the stack from the last element pushed to the first
void stack_print(pstack_t stack){

    for (size_t i = 0 ; i <= stack->top-1; i++){

        stack->print_func(stack->arr[stack->top-1-i]);
    }
}
