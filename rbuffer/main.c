/*******************************************************************************
 * 
 * @file    main.c 
 * @brief   Test driver for the ring buffer module.
 * @author  Kyungjae Lee
 * @date    Tue 07, 2026
 * 
 ******************************************************************************/

#include <stdio.h>
#include "rbuffer.h"

#define BUFFER_SIZE (8)

int main(int argc, char *argv[])
{
    rbuffer_t *rb = rbuffer_create(BUFFER_SIZE);
    
    /* TBD */
    
    rbuffer_destroy(rb);

    return 0;
} /* End of main() */

/*** End of file: main.c ***/