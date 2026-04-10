/*******************************************************************************
 * 
 * @file    stack.c
 * @brief   Implementation of a stack. 
 * @author  Kyungjae Lee
 * @date    Apr 09, 2026
 * @note    The definitions of stack_t and stack_node_t are intentionally kept
 *          private to this source file to enforce encapsulation. Users of this
 *          module interact with the list only through the public API and cannot
 *          access or modify internal members directly.
 * 
 ******************************************************************************/

#include "stack.h"
#include <stdio.h>
#include <stdlib.h>

/* Private data types --------------------------------------------------------*/

/*!
 * @brief Structure representing a node in a stack.
 * @note This structure is internal to the implementation and must not be
 * accessed directly by users of the API.
 */
typedef struct stack_node_t
{
   int data;
   struct stack_node_t *p_next;
} stack_node_t;

/*!
 * @brief Structure representing a stack.
 * @note This structure is opaque to users of the API. The full definition is
 * hidden to prevent direct access to internal members and to preserve list
 * invariants.
 */
struct stack_t
{
   stack_node_t *p_tos; /* Top-of-stack. */
   size_t size;
};

/* Public API definitions ----------------------------------------------------*/

/*!
 * @brief Creates and initializes an empty stack.
 * @return Pointer to newly created stack, or NULL on allocation failure.
 * @note Time complexity: O(1)
 * @note The caller owns the returned object, and is responsible for destroying
 * it by calling slist_destroy().
 */
stack_t* stack_create(void)
{
	stack_t *p_stack = malloc(sizeof(stack_t));
	if (NULL == p_stack)
	{
		return NULL;
	}

	p_stack->p_tos = NULL;
	p_stack->size = 0;

	return p_stack;
}

/*!
 * @brief Destroys a stack and frees all allocated memory.
 * @param[in] p_stack Pointer to stack object.
 * @return STACK_OK on success, error codes otherwise.
 * @note Time complexity: O(n), where n is the number of nodes.
 */
stack_status_t stack_destroy(stack_t *p_stack)
{
	if (NULL == p_stack)
	{
		return STACK_ERR_NULL;
	}

	while (p_stack->p_tos != NULL)
	{
		stack_node_t *p_temp = p_stack->p_tos;
		p_stack->p_tos = p_temp->p_next;
		free(p_temp);
	}

	free(p_stack);

	return STACK_OK;
}

/*!
 * @brief Pushes a node onto the stack.
 * @param[in] p_stack Pointer to stack object.
 * @param[in] data Data to push.
 * @return STACK_OK on success, error codes otherwise.
 * @note Time complexity: O(1)
 */
stack_status_t stack_push(stack_t *p_stack, const int data)
{
	if (NULL == p_stack)
	{
		return STACK_ERR_NULL;
	}

	stack_node_t *p_new = malloc(sizeof(stack_node_t));
	if (NULL == p_new)
	{
		return STACK_ERR_MALLOC;
	}
	p_new->data = data;

	p_new->p_next = p_stack->p_tos;
	p_stack->p_tos = p_new;
	p_stack->size++;
	
	return STACK_OK;
}

/*!
 * @brief Pops the top node of the stack.
 * @param[in] p_stack Pointer to stack object.
 * @param[out] p_data Optional pointer to store popped value (can be NULL).
 * @return STACK_OK on success, error codes otherwise.
 * @note Time complexity: O(1)
 */
stack_status_t stack_pop(stack_t *p_stack, int *p_data)
{
	if (NULL == p_stack)
	{
		return STACK_ERR_NULL;
	}

	if (0 == p_stack->size)
	{
		return STACK_ERR_EMPTY;
	}

	if (p_data != NULL)
	{
		*p_data = p_stack->p_tos->data;
	}

	stack_node_t *p_temp = p_stack->p_tos;
	p_stack->p_tos = p_stack->p_tos->p_next;
	free(p_temp);
	p_stack->size--;

	return STACK_OK;
}

/*!
 * @brief Retrieves (without removing) the top node of the stack.
 * @param[in] p_stack Pointer to stack object.
 * @param[out] p_data Pointer to store top node.
 * @return STACK_OK on success, error codes otherwise.
 * @note Time complexity: O(1)
 */
stack_status_t stack_peek(const stack_t *p_stack, int *p_data)
{
	if (NULL == p_stack || NULL == p_data)
	{
		return STACK_ERR_NULL;
	}

	if (0 == p_stack->size)
	{
		return STACK_ERR_EMPTY;
	}

	*p_data = p_stack->p_tos->data;

	return STACK_OK;
}

/*!
 * @brief Retrieves the number of nodes in the stack.
 * @param[in] p_stack Pointer to stack object.
 * @param[out] p_size Pointer to store stack size.
 * @return STACK_OK on success, error codes otherwise.
 * @note Time complexity: O(1)
 */
stack_status_t stack_size(const stack_t *p_stack, size_t *p_size)
{
	if (NULL == p_stack || NULL == p_size)
	{
		return STACK_ERR_NULL;
	}

	*p_size = p_stack->size;

	return STACK_OK;
}

/*!
 * @brief Prints stack content from top to bottom.
 * @param[in] p_stack Pointer to stack object.
 * @return STACK_OK on success, error codes otherwise.
 * @note Time complexity: O(n), where n is the number of nodes.
 */
stack_status_t stack_display(const stack_t *p_stack)
{
	if (NULL == p_stack)
	{
		return STACK_ERR_NULL;
	}

	printf("tos -> ");

	stack_node_t *p_temp = p_stack->p_tos;

	while (p_temp != NULL)
	{
		printf("%d -> ", p_temp->data);
		p_temp = p_temp->p_next;
	}

	printf("null\n");

	return STACK_OK;
}

/* End of file: stack.c */
