/*******************************************************************************
 * 
 * @file    stack.h
 * @brief   Public APIs for a stack.
 * @details This module provides an opaque stack implementation.
 *          Users must interact with the list only through the provided APIs.
 * @author  Kyungjae Lee
 * @date    Apr 09, 2026
 * @note    The internal data structures are opaque to users to prevent
 *          accidental violation of list invariants.
 * 
 ******************************************************************************/

#ifndef STACK_H
#define STACK_H

#include <stddef.h>

/* Opaque type declarations --------------------------------------------------*/
typedef struct stack_t stack_t;

/* User-defined data types ---------------------------------------------------*/
typedef enum
{
    STACK_OK,
    STACK_ERR_EMPTY,
    STACK_ERR_FULL,
    STACK_ERR_NULL,
	STACK_ERR_MALLOC
} stack_status_t;

/* Public APIs ---------------------------------------------------------------*/

stack_t* stack_create(void);                              
stack_status_t stack_destroy(stack_t *p_stack);
stack_status_t stack_push(stack_t *p_stack, const int data);            
stack_status_t stack_pop(stack_t *p_stack, int *p_data);            
stack_status_t stack_peek(const stack_t *p_stack, int *p_data);
stack_status_t stack_size(const stack_t *p_stack, size_t *p_size);
stack_status_t stack_display(const stack_t *p_stack);

#endif /* STACK_H */

/*** End of file: stack.h */
