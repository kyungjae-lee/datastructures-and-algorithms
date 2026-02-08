/*******************************************************************************
 * 
 * @file    rbuffer.h
 * @brief   Public APIs for a ring buffer.
 * @details This module provides an opaque ring buffer implementation.
 *          Users must interact with the list only through the provided APIs.
 * @author  Kyungjae Lee
 * @date    Jan 24, 2026
 * @note    The internal data structures are opaque to users to prevent
 *          accidental violation of list invariants.
 * 
 ******************************************************************************/

#ifndef RBUFFER_H
#define RBUFFER_H

#include <stdbool.h>
#include <stdint.h>

/* Opaque type declarations --------------------------------------------------*/

typedef struct rbuffer_t rbuffer_t;

/* Public APIs ---------------------------------------------------------------*/

rbuffer_t* rbuffer_create(uint32_t capacity);
bool rbuffer_read(rbuffer_t *p_rb, uint8_t *p_data);
bool rbuffer_write(rbuffer_t *p_rb, uint8_t data);
uint32_t rbuffer_data_count(const rbuffer_t *p_rb);
uint32_t rbuffer_free_count(const rbuffer_t *p_rb);
bool rbuffer_is_empty(const rbuffer_t *p_rb);
bool rbuffer_is_full(const rbuffer_t *p_rb);
bool rbuffer_clear(rbuffer_t *p_rb);
void rbuffer_destroy(rbuffer_t *p_rb);

#endif /* RBUFFER_H */

/*** End of file: rbuffer.h */