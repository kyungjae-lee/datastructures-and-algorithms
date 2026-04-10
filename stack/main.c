/*******************************************************************************
 * 
 * @file    main.c 
 * @brief   Test driver for the stack module.
 * @author  Kyungjae Lee
 * @date    Apr 10, 2026
 * 
 ******************************************************************************/

#include <stdio.h>
#include "stack.h"

int main(int argc, char *argv[])
{
    stack_t *p_stack = stack_create();
    int data;
	size_t size; 

    /* Add nodes to the head of the list. */
	stack_push(p_stack, 1);
	stack_push(p_stack, 2);
	stack_push(p_stack, 3);
	stack_push(p_stack, 4);

    /* Display the size and the contents of the list. */
	stack_size(p_stack, &size);
    printf("size: %d\n", size); /* 4 */
    stack_display(p_stack); /* tos -> 4 -> 3 -> 2 -> 1 -> null */

    /* Peek at the top of stack. */
    stack_peek(p_stack, &data);
    printf("%d\n", data); /* 4 */

    /* Remove the head and check the new head.*/
    stack_pop(p_stack, &data);
    printf("%d\n", data); /* 4 */
    stack_peek(p_stack, &data);
    printf("%d\n", data); /* 3 */
    
    /* Display the list after pop. */
    stack_display(p_stack); /* tos -> 3 -> 2 -> 1 -> null */

    /* Clear the list. */
    stack_pop(p_stack, NULL);
    stack_pop(p_stack, NULL);
    stack_pop(p_stack, NULL);
    if (stack_pop(p_stack, NULL) == STACK_ERR_EMPTY)
	{
		printf("Cannot remove from an empty stack.\n");
	}
    
    stack_destroy(p_stack);

    return 0;
} /* End of main() */

/*** End of file: main.c ***/
