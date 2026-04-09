/*******************************************************************************
 * 
 * @file    main.c 
 * @brief   Test driver for the singly linked list module.
 * @author  Kyungjae Lee
 * @date    Jan 24, 2026
 * 
 ******************************************************************************/

#include <stdio.h>
#include "slist.h"

int main(int argc, char *argv[])
{
    slist_t *p_list = slist_create();
    int data;

    /* Add nodes to the head of the list. */
    slist_add_to_head(p_list, 1);
    slist_add_to_head(p_list, 2);
    slist_add_to_head(p_list, 3);

    /* Add nodes to the tail of the list. */
    slist_add_to_tail(p_list, 4);
    slist_add_to_tail(p_list, 5); 

    /* Display the size and the contents of the list. */
    printf("size: %d\n", slist_size(p_list)); /* 5 */
    slist_display(p_list); /* 3 2 1 4 5 */
    printf("%d\n", slist_is_empty(p_list)); /* 0 */

    /* Peek at the head of the list. */
    slist_peek_head(p_list, &data);
    printf("%d\n", data); /* 3 */

    /* Remove the head and check the new head.*/
    slist_remove_head(p_list, &data);
    slist_peek_head(p_list, &data); 
    printf("%d\n", data); /* 2 */
    
    /* Display the list after removal. */
    slist_display(p_list); /* 2 1 4 5 */

    /* Clear the list. */
    slist_clear(p_list);
    printf("size: %d\n", slist_size(p_list)); /* 0 */
    slist_display(p_list); /* NULL */
    
    /* Attempt to remove from an empty list. */
    if (!slist_remove_head(p_list, &data))
    {
        printf("Error: Cannot remove from an empty list.\n");
    }

    slist_destroy(p_list);

    return 0;
} /* End of main() */

/*** End of file: main.c ***/