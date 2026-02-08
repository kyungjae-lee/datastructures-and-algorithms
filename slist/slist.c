/*******************************************************************************
 * 
 * @file    slist.c
 * @brief   Implementation of a singly linked list. 
 * @author  Kyungjae Lee
 * @date    Jan 24, 2026
 * @note    The definitions of slist_t and slist_node_t are intentionally kept
 *          private to this source file to enforce encapsulation. Users of this
 *          module interact with the list only through the public API and cannot
 *          access or modify internal members directly.
 * 
 ******************************************************************************/

#include "slist.h"
#include <stdio.h>
#include <stdlib.h>

/* Private data types --------------------------------------------------------*/

/*!
 * @brief Structure representing a node in a singly linked list.
 * @note This structure is internal to the implementation and must not be
 * accessed directly by users of the API.
 */
typedef struct slist_node_t
{
   int data;
   struct slist_node_t *p_next;
} slist_node_t;

/*!
 * @brief Structure representing a singly linked list.
 * @note This structure is opaque to users of the API. The full definition is
 * hidden to prevent direct access to internal members and to preserve list
 * invariants.
 */
struct slist_t
{
   slist_node_t *p_head;
   slist_node_t *p_tail; /* Enables O(1) push_back(). */
   unsigned int size;
};

/* Public API definitions ----------------------------------------------------*/

/*!
 * @brief Creates and initializes a singly linked list.
 * @return Pointer to the created list, or NULL if memory allocation fails.
 * @note Time complexity: O(1)
 * @note The caller owns the returned object, and is responsible for destroying
 * it by calling slist_destroy().
 */
slist_t* slist_create(void)
{
    /* Allocate memory for a singly linked list. */
    slist_t *p_list = malloc(sizeof(slist_t));
    if (NULL == p_list)
    {
        /* Memory allocation failed. */
        return NULL;
    }

    /* Initialize the list to an empty state. */
    p_list->p_head = NULL;
    p_list->p_tail = NULL;
    p_list->size = 0;

    return p_list;
} /* End of slist_create() */

/*!
 * @brief Destroys a singly linked list and frees all associated memory.
 * @param[in] p_list Pointer to the singly linked list.
 * @return true If the list was destroyed.
 * @return false If p_list is NULL.
 * @note Time complexity: O(n), where n is the number of nodes.
 */
bool slist_destroy(slist_t *p_list)
{
    if (NULL == p_list)
    {
        return false;
    }

    slist_clear(p_list);
    free(p_list);

    return true;
} /* End of slist_destroy() */

/*!
 * @brief Adds a node to the head of the list.
 * @param[in,out] p_list Pointer to the singly linked list.
 * @param[in] data Data to add.
 * @return true If the addition was successful.
 * @return false If p_list is NULL or memory allocation fails.
 * @note Time complexity: O(1)
 */
bool slist_add_to_head(slist_t *p_list, int data)
{
    if (NULL == p_list)
    {
        return false;
    }    

    /* Create a node. */
    slist_node_t *p_new = malloc(sizeof(slist_node_t));
    if (NULL == p_new)
    {
        /* Memory allocation failed. */
        return false;
    }
    p_new->data = data;
    p_new->p_next = NULL;

    /* Add the new node to the head of the list. */
    if (0 == p_list->size)
    {
        /* Empty list. */
        p_list->p_head = p_new;
        p_list->p_tail = p_new;
    }
    else
    {
        /* Non-empty list. */
        p_new->p_next = p_list->p_head;
        p_list->p_head = p_new; 
    }

    p_list->size++;

    return true;
} /* End of slist_add_to_head() */

/*!
 * @brief Adds a node to the tail of the list.
 * @param[in,out] p_list Pointer to the singly linked list.
 * @param[in] data Data to add.
 * @return true If the addition was successful.
 * @return false If p_list is NULL or memory allocation fails.
 * @note Time complexity: O(1)
 */
bool slist_add_to_tail(slist_t *p_list, int data)
{
    if (NULL == p_list)
    {
        return false;
    }

    /* Create a new node. */
    slist_node_t *p_new = malloc(sizeof(slist_node_t));
    if (NULL == p_new)
    {
        /* Memory allocation failed. */
        return false;
    }
    p_new->data = data;
    p_new->p_next = NULL;

    /* Add the new node to tail of the list. */    
    if (0 == p_list->size)
    {
        p_list->p_head = p_new;
        p_list->p_tail = p_new;
    }
    else
    {
        p_list->p_tail->p_next = p_new;
        p_list->p_tail = p_new; 
    }

    p_list->size++;

    return true;
} /* End of slist_add_to_tail() */

/*!
 * @brief Returns the data at the head of the list without removing it.
 * @param[in] p_list Pointer to the singly linked list.
 * @param[out] p_data Pointer to store the data at the head.
 * @return true If the peek was successful.
 * @return false If p_list is NULL or p_data is NULL, or the list is empty.
 * @note Time complexity: O(1)
 */
bool slist_peek_head(const slist_t *p_list, int *p_data)
{
    if (NULL == p_list || NULL == p_data)
    {
        return false;
    }

    if (0 == p_list->size)
    {
        /* Cannot peek an empty list. */
        return false;
    }

    *p_data = p_list->p_head->data;

    return true;
} /* End of slist_peek_head() */

/*!
 * @brief Removes the node at the head of the list and stores its data.
 * @param[in,out] p_list Pointer to the singly linked list.
 * @param[out] p_data Pointer to store the data at the head.
 * @return true If the removal was successful.
 * @return false If p_list is NULL, p_data is NULL, or the list is empty.
 * @note Time complexity: O(1)
 */
bool slist_remove_head(slist_t *p_list, int *p_data)
{
    if (NULL == p_list || NULL == p_data)
    {
        return false;
    }

    if (0 == p_list->size)
    {
        /* Cannot remove from an empty list. */
        return false;
    }

    slist_node_t * p_remove = p_list->p_head;

    /* Store the data of the current head node being removed. */
    *p_data = p_remove->data;

    /* Update p_head. */
    p_list->p_head = p_remove->p_next;

    if (1 == p_list->size)
    {
        /* Special case: Clear p_tail when removing the last node to avoid
         * a dangling pointer. */
        p_list->p_tail = NULL;
    }

    p_list->size--;
    free(p_remove);

    return true;
} /* End of slist_remove_head() */

/*!
 * @brief Checks if the list is empty.
 * @param[in] p_list Pointer to the singly linked list.
 * @return true If the list is empty.
 * @return false If the list is not empty, or p_list is NULL.
 * @note Time complexity: O(1)
 */
bool slist_is_empty(const slist_t *p_list)
{
    if (NULL == p_list)
    {
        return false;
    }

    return (0 == p_list->size);
} /* End of slist_is_empty() */

/*!
 * @brief Returns the size of the list.
 * @param[in] p_list Pointer to the singly linked list.
 * @return Number of nodes in the list. Returns 0 if p_list is NULL.
 * @note Time complexity: O(1)
 */
unsigned int slist_size(const slist_t *p_list)
{
    if (NULL == p_list)
    {
        return 0;
    }

    return p_list->size;
} /* End of slist_size() */

/*!
 * @brief Removes all nodes in the list.
 * @param[in,out] p_list Pointer to the singly linked list.
 * @note If p_list is NULL, the function does nothing.
 * @note Time complexity: O(n), where n is the number of nodes.
 */
void slist_clear(slist_t *p_list)
{
    if (NULL == p_list)
    {
        return;
    }

    slist_node_t *p_remove = p_list->p_head;

    /* Free nodes one by one while advancing the p_head. */
    while (NULL != p_remove)
    {
        p_list->p_head = p_remove->p_next;
        free(p_remove);
        p_remove = p_list->p_head;
    }

    /* Reset list to empty state. */
    p_list->p_head = NULL; /* Optional. */
    p_list->p_tail = NULL;
    p_list->size = 0;
} /* End of slist_clear() */

/*!
 * @brief Displays all nodes in the list.
 * @param[in] p_list Pointer to the singly linked list.
 * @note If p_list is NULL, the function does nothing.
 * @note Time complexity: O(n), where n is the number of nodes.
 */
void slist_display(slist_t *p_list)
{
    if (NULL == p_list)
    {
        return;
    }  

    slist_node_t *p_curr = p_list->p_head;
    while (p_curr)
    {
        printf("%d -> ", p_curr->data);
        p_curr = p_curr->p_next; 
    }
    printf("NULL\n");
} /* End of slist_display() */

/*** End of file: slist.c */ 