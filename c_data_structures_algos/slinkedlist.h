#include <stdlib.h>

#ifndef SLINKEDLIST_H_
#define SLINKEDLIST_H_

typedef struct sll_node {
    int data;
    struct sll_node *next;
} sll_node;

// Traverse the linked list at head, printing to stdout the elements.
void sll_print(struct sll_node *head);

// Returns the length of the linked list at head.
size_t sll_len(struct sll_node *head);

// Creates the head to a new one element linked list containing `data`.
struct sll_node *sll_new(int data);

/*
 * Inserts a new element at the linked list represented by `head`. Returns a
 * pointer to the new head of the linked list.
 */
struct sll_node *sll_push(struct sll_node *head, int data);

// Using the a tail node, appends data to the end of the list.
void sll_tail_append(struct sll_node *tail, int data);

// Appends to the end of the list, returns a pointer to the head of the list.
struct sll_node *sll_append(struct sll_node *head, int data);

/*
 * Inserts into position i of the list (0 indexed). Returns a pointer to the
 * head of the list. Attempting to write to insert at indices beyond the
 * length of the list will return a null pointer and no addition to the list
 * will be made.
 */
struct sll_node *sll_insert(struct sll_node *head, size_t i, int data);

/*
 * Fetches the element at i in the linked list represented by head.
 * Returns an int pointer to the element's data.
 * Calls where i is out of the bounds of the list will return a null pointer.
 */
int *sll_get(struct sll_node *head, size_t i);

/*
 * Returns a pointer to the first element of the list that contains the
 * supplied key.
 * Returns a null pointer if the key was not found.
 */
struct sll_node *sll_search(struct sll_node *head, int key);

// Frees every element in a linked list.
void sll_free_list(struct sll_node *head);

/*
 * Removes the first element of the list and returns a pointer to the new head.
 * Callers should save the data in the head before calling pop if they want it.
 */
struct sll_node *sll_pop(struct sll_node *head);

/*
 * Removes the indicated element and returns a pointer to the new head.
 * Attempts to remove an item which is out of bounds from the list will return
 * a null pointer and no modification will be made.
 */
struct sll_node *sll_remove(struct sll_node *head, size_t i);

#endif
