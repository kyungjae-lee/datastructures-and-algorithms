/*******************************************************************************
 * 
 * @file    slist.h
 * @brief   Public APIs for a singly linked list.
 * @details This module provides an opaque singly linked list implementation.
 *          Users must interact with the list only through the provided APIs.
 * @author  Kyungjae Lee
 * @date    Jan 24, 2026
 * @note    The internal data structures are opaque to users to prevent
 *          accidental violation of list invariants.
 * 
 ******************************************************************************/

#ifndef SLIST_H
#define SLIST_H

#include <stdbool.h>
#include <stddef.h>

/* Opaque type declarations --------------------------------------------------*/
typedef struct slist_t slist_t;

/* Public APIs ---------------------------------------------------------------*/

slist_t* slist_create(void);                              
bool slist_destroy(slist_t *p_list);
bool slist_add_to_head(slist_t *p_list, int data);            
bool slist_add_to_tail(slist_t *p_list, int data);
bool slist_peek_head(const slist_t *p_list, int *p_data);
bool slist_remove_head(slist_t *p_list, int *p_data);
bool slist_is_empty(const slist_t *p_list);
unsigned int slist_size(const slist_t *p_list);
void slist_clear(slist_t *p_list);
void slist_display(slist_t *p_list);

#endif /* SLIST_H */

/*** End of file: slist.h */