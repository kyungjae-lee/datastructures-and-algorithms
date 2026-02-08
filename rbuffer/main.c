/*******************************************************************************
 * 
 * @file    main.c 
 * @brief   Test driver for the ring buffer module.
 * @author  Kyungjae Lee
 * @date    Feb 07, 2026
 * 
 ******************************************************************************/

#include <stdio.h>
#include "rbuffer.h"

#define BUFFER_SIZE (8)

int main(int argc, char *argv[])
{
    int32_t data;
    
    rbuffer_t *rb = rbuffer_create(BUFFER_SIZE);
    printf("%d\n", rbuffer_is_empty(rb)); /* 1 */
    printf("%d\n", rbuffer_data_count(rb)); /* 0 */
    printf("%d\n", rbuffer_free_count(rb)); /* 8 */
    rbuffer_display(rb); /* (none) */

    /* Write buffer to full. */
    for (int i = 0; i < BUFFER_SIZE; i++)
    {
        rbuffer_write(rb, i);
    }
    rbuffer_display(rb); /* 0 1 2 3 4 5 6 7 */
    printf("%d\n", rbuffer_data_count(rb)); /* 8 */
    printf("%d\n", rbuffer_is_full(rb)); /* 1 */
    printf("%d\n", rbuffer_is_empty(rb)); /* 0 */

    /* Overwrite. */
    for (int i = -4; i < 0; i++)
    {
        rbuffer_write(rb, i);
    }
    rbuffer_display(rb); /* 4 5 6 7 -4 -3 -2 -1 */
    printf("%d\n", rbuffer_data_count(rb)); /* 8 */

    /* Read buffer. */
    for (int i = 0; i < 3; i++)
    {
        rbuffer_read(rb, &data);
        printf("%d ", data);
    } /* 4 5 6 */
    printf("\n");
    rbuffer_display(rb); /* 7 -4 -3 -2 -1 */
    printf("%d\n", rbuffer_data_count(rb)); /* 5 */
    printf("%d\n", rbuffer_free_count(rb)); /* 3 */

    /* Read bufer to empty. */
    for (int i = 0; i < BUFFER_SIZE; i++)
    {
        if (rbuffer_read(rb, &data))
        {
            printf("%d ", data);
        }
        else
        {
            printf("_ ");
        }
    } /* 7 -4 -3 -2 -1 _ _ _ */
    printf("\n");

    printf("%d\n", rbuffer_is_empty(rb)); /* 1 */

    rbuffer_write(rb, 4);
    rbuffer_display(rb); /* 4 */
    printf("%d\n", rbuffer_data_count(rb)); /* 1 */
    printf("%d\n", rbuffer_free_count(rb)); /* 7 */

    rbuffer_clear(rb);
    rbuffer_display(rb); /* (none) */
    printf("%d\n", rbuffer_data_count(rb)); /* 0 */
    printf("%d\n", rbuffer_free_count(rb)); /* 8 */

    /* Free. */
    rbuffer_destroy(rb);

    return 0;
} /* End of main() */

/*** End of file: main.c ***/