/*******************************************************************************
 * 
 * @file    rbuffer.c
 * @brief   Implementation of a ring buffer.
 * @author  Kyungjae Lee
 * @date    Feb 07, 2026
 * @note    The definitions of rbuffer_t is intentionally kept private to this
 *          source file to enforce encapsulation. Users of this module interact
 *          with the list only through the public API and cannot access or
 *          modify internal members directly.
 * 
 ******************************************************************************/

#include "rbuffer.h"
#include "string.h"
#include <stdio.h>
#include <stdlib.h>

/* Macros --------------------------------------------------------------------*/

/* Private data types --------------------------------------------------------*/

/*!
 * @brief Structure representing a ring buffer.
 * @note This structure is opaque to users of the API. The full definition is
 * hidden to prevent direct access to internal members and to preserve list
 * invariants.
 */
struct rbuffer_t
{
    uint8_t *p_buf;
    uint32_t capacity;
    uint32_t ridx;   /* Read index. */
    uint32_t widx;   /* Write index. */
    bool b_is_full;
};

/* Public API definitions ----------------------------------------------------*/

/*!
 * @brief Creates and initializes a ring buffer.
 * @param[in] capacity Maximum number of elements the ring buffer can store.
 * @return Pointer to the created ring buffer control structure, or NULL if 
 * capacity is less than 1 or if any memory allocation fails.
 * @note Time complexity: O(1)
 * @note The caller owns the returned object, and is responsible for destroying
 * it by calling rbuffer_destroy().
 */
rbuffer_t* rbuffer_create(uint32_t capacity)
{
    if (capacity < 1)
    {
        return NULL;
    }

    /* Allocate memory a ring buffer. */
    rbuffer_t *p_rb = malloc(sizeof(rbuffer_t));
    if (NULL == p_rb)
    {
        /* Memory allocation failed. */
        return NULL;
    }

    /* Initialize the ring buffer to an empty state. */
    p_rb->p_buf = malloc(capacity * sizeof(uint8_t));
    if (NULL == p_rb->p_buf)
    {
        free(p_rb);
        return NULL;
    }
    p_rb->capacity = capacity;
    p_rb->ridx = 0;
    p_rb->widx = 0;
    p_rb->b_is_full = false;

    return p_rb;
} /* End of rbuffer_create() */

/*!
 * @brief Reads and removes oldest data from the ring buffer.
 * @param[in,out] p_rb Pointer to ring buffer control structure.
 * @param[out] p_data Pointer to variable that receives the popped data.
 * @return true If data is successfully read.
 * @return false If the buffer is empty, or p_rb is NULL, or p_data is NULL.
 * @note Time complexity: O(1)
 */
bool rbuffer_read(rbuffer_t *p_rb, uint8_t *p_data)
{
    if (NULL == p_rb || NULL == p_data)
    {
        return false;
    }

    if ((p_rb->widx == p_rb->ridx) && (false == p_rb->b_is_full))
    {
        /* Cannot read from an empty buffer. */
        return false;
    }

    /* Read oldest data. */
    *p_data = p_rb->p_buf[p_rb->ridx];

    /* Advance read index. */
    p_rb->ridx++;
    if (p_rb->ridx >= p_rb->capacity)
    {
        p_rb->ridx = 0;
    }

    /* Update full flag if the buffer is empty now. */
    if (p_rb->ridx == p_rb->widx)
    {
        p_rb->b_is_full = false;
    }

    return true;
} /* End of rbuffer_read() */

/*!
 * @brief Writes a new data into the ring buffer.
 * @param[in,out] p_rb Pointer to ring buffer control structure.
 * @param[in] data Data to write to the buffer.
 * @return true If new data is successfully written. If the buffer was full, the
 * oldest data is overwritten.
 * @return false If p_rb is NULL.
 * @note Time complexity: O(1)
 */
bool rbuffer_write(rbuffer_t *p_rb, uint8_t data)
{
    if (NULL == p_rb)
    {
        return false;
    }

    if (p_rb->b_is_full)
    {
        /* Buffer full: advance read index to overwrite oldest data. */
        p_rb->ridx++;
        if (p_rb->ridx >= p_rb->capacity)
        {
            p_rb->ridx = 0;
        }
    }

    /* Write new data. */
    p_rb->p_buf[p_rb->widx] = data;

    /* Advance write index. */
    p_rb->widx++;
    if (p_rb->widx >= p_rb->capacity)
    {
        p_rb->widx = 0;
    }

    /* Update full flag if the buffer is full now. */
    if (p_rb->widx == p_rb->ridx)
    {
        p_rb->b_is_full = true;
    }

    return true;
} /* End of rbuffer_write() */

/*!
 * @brief Counts the number of available data in the ring buffer.
 * @param[in] p_rb Pointer to ring buffer control structure.
 * @return Number of data currently stored in the buffer. Returns 0 if the
 * buffer is empty or p_rb is NULL.
 */
uint32_t rbuffer_data_count(const rbuffer_t *p_rb)
{
    if (NULL == p_rb)
    {
        return 0;
    }

    if (p_rb->widx == p_rb->ridx)
    {
        return p_rb->b_is_full ? p_rb->capacity : 0;
    }
    else if (p_rb->widx > p_rb->ridx)
    {
        return p_rb->widx - p_rb->ridx;
    }
    else
    {
        return p_rb->capacity - (p_rb->ridx - p_rb->widx);
    }
} /* End of rbuffer_data_count() */

/*!
 * @brief Counts the number of available free slots in the ring buffer.
 * @param[in] p_rb Pointer to ring buffer control structure.
 * @return Number of free slots available for writing. Returns 0 if the buffer is
 * full or p_rb is NULL.
 * @note Time complexity: O(1)
 */
uint32_t rbuffer_free_count(const rbuffer_t *p_rb)
{
    if (NULL == p_rb)
    {
        return 0;
    }

    if (p_rb->widx == p_rb->ridx)
    {
        return p_rb->b_is_full ? 0 : p_rb->capacity;
    }
    else if (p_rb->widx > p_rb->ridx)
    {
        return p_rb->capacity - (p_rb->widx - p_rb->ridx);
    }
    else
    {
        return p_rb->ridx - p_rb->widx;
    }
} /* End of rbuffer_free_count() */

/*!
 * @brief Checks whether the ring buffer is empty. 
 * @param[in] p_rb Pointer to ring buffer control structure.
 * @return true If the buffer is empty.
 * @return false If the buffer contains at least one data, or if p_rb is NULL.
 * @note Time complexity: O(1)
 * @note Full and empty states are distinguished using an explicit full flag.
 */
bool rbuffer_is_empty(const rbuffer_t *p_rb)
{
    if (NULL == p_rb)
    {
        return false;
    }

    return (p_rb->widx == p_rb->ridx && !p_rb->b_is_full);
} /* End of rbuffer_is_empty() */

/*!
 * @brief Checks whether the ring buffer is full. 
 * @param[in] p_rb Pointer to ring buffer control structure.
 * @return true If buffer is full.
 * @return false If buffer has available space, or p_rb is NULL.
 * @note Time complexity: O(1)
 * @note Full and empty states are distinguished using an explicit full flag.
 */
bool rbuffer_is_full(const rbuffer_t *p_rb)
{
    if (NULL == p_rb)
    {
        return false;
    }

    return (p_rb->widx == p_rb->ridx && p_rb->b_is_full);
} /* End of rbuffer_is_full() */

/*!
 * @brief Clears all data in the ring buffer.
 * @param[in,out] p_rb Pointer to the ring buffer control structure.
 * @return true If the buffer was successfully cleared.
 * @return false If p_rb is NULL.
 * @note Time complexity: O(n), where n is the capacity.
 */
bool rbuffer_clear(rbuffer_t *p_rb)
{
    if (NULL == p_rb)
    {
        return false;
    }

    /* Clear the buffer. */
    memset(p_rb->p_buf, 0, p_rb->capacity);

    /* Reset the member variables to empty state. */
    p_rb->widx = 0;
    p_rb->ridx = 0;
    p_rb->b_is_full = false;

    return true;
} /* End of rbuffer_clear() */

/*!
 * @brief Destroys a ring buffer instance and releases all associated
 * resources. 
 * @param[in] p_rb Pointer to the ring buffer control structure.
 * @note Time complexity: O(1)
 * @note It is safe to call this function with a NULL pointer.
 * @note After this function returns, the pointer must not be used gain.
 */
void rbuffer_destroy(rbuffer_t *p_rb)
{
    if (NULL == p_rb)
    {
        return;
    }

    free(p_rb->p_buf);
    free(p_rb);
} /* End of rbuffer_destroy() */

/*** End of file: rbuffer.c */