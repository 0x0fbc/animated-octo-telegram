/*
 * Simple implementation of a singly linked list supporting ints.
 * All functions that return pointers should have guards for NULLs,
 * which I've used to indicate issues such as out of bounds access.
 *
 * @0x0fbc
 */
#include<stdlib.h>
#include<stdio.h>

#include "slinkedlist.h"

void sll_print(struct sll_node *head)
{
    struct sll_node* curr = head;
    printf("[");
    while (curr != NULL) {
        if (curr->next == NULL) {
            printf("%d", curr->data);
        } else {
            printf("%d, ", curr->data);
        }
        curr = curr->next;
    }
    printf("]\n");
}

size_t sll_len(struct sll_node *head)
{
    size_t size = 0;

    if (head == NULL) {
        return (size_t) 0;
    }

    sll_node *curr = head;
    while (curr != NULL) {
        size++;
        curr = curr->next;
    }

    return size;
}

struct sll_node *sll_push(struct sll_node *head, int data)
{
    struct sll_node *node = malloc(sizeof(sll_node));
    if (!head) {
        node->data = data;
        node->next = NULL;
    } else {
        node->data = data;
        node->next = head;
    }
    return node;
}


struct sll_node *sll_new(int data)
{
    return sll_push((sll_node *) NULL, data);
}


void sll_tail_append(struct sll_node *tail, int data)
{
    struct sll_node *node = malloc(sizeof(sll_node));
    // Create new tail node
    node->data = data;
    node->next = NULL;
    // Set previous tail's next to the new node.
    tail->next = node;
}


struct sll_node *sll_append(struct sll_node *head, int data)
{
    if (head == NULL) {
        return sll_new(data);
    }

    struct sll_node *curr = head;
    while (curr->next != NULL) {
        curr = curr->next;
    }

    struct sll_node *node = malloc(sizeof(sll_node));
    node->data = data;
    node->next = NULL;

    curr->next = node;

    return head;
}

struct sll_node *sll_insert(struct sll_node *head, size_t i, int data)
{
    // if the index to insert at is 0, use push and return the new head.
    if (i == 0) {
        return sll_push(head, data);
    }

    size_t len = sll_len(head);

    // If the index to insert at exceeds the position of the tail of the list,
    // return NULL.
    if (i > len) {
        return NULL;
    }

    // If the index to insert at is the index after the tail of the list use
    // append.
    if (i == len) {
        return sll_append(head, data);
    }

    // seek to the element immediately before the index to insert at.
    struct sll_node *curr = head;
    size_t ctr = 0;
    while (ctr != (i - 1)) {
        curr = head->next;
        ctr++;
    }

    struct sll_node *node = malloc(sizeof(sll_node));
    node->next = curr->next;
    node->data = data;
    curr->next = node;
    return head;
}


int *sll_get(struct sll_node *head, size_t i)
{
    if (i >= sll_len(head)) {
        return NULL;
    }

    // Traverse the list, stop at the requested index and return a pointer
    // to the data it contains.
    size_t ctr = 0;
    struct sll_node *curr = head;
    while (ctr != i) {
        curr = curr->next;
        ctr++;
    }
    return &curr->data;
}


void sll_free_list(struct sll_node *head)
{
    struct sll_node *curr = head;
    while (curr != NULL) {
        struct sll_node *tmp = curr->next;
        free(curr);
        curr = tmp;
    }
}


struct sll_node *sll_pop(struct sll_node *head)
{
    if (head == NULL) {
        return NULL;
    }

    struct sll_node *tmp = head->next;
    free(head);
    return tmp;
}


struct sll_node *sll_remove(struct sll_node *head, size_t i)
{
    // Re-use pop for removing the head.
    if (i == 0) {
        return sll_pop(head);
    }

    // Guard against invalid indicies
    size_t len = sll_len(head);
    if (i > len - 1) {
        return NULL;
    }

    size_t ctr = 0;
    struct sll_node *curr = head;
    while (ctr != (i - 1)) {
        curr = curr->next;
        ctr++;
    }

    if (i == (len - 1)) {
        free(curr->next);
        curr->next = NULL;
        return head;
    } else {
        struct sll_node *tmp = curr->next->next;
        free(curr->next);
        curr->next = tmp;
        return head;
    }
}

struct sll_node *sll_search(struct sll_node *head, int key)
{
    struct sll_node *curr = head;
    while(curr != NULL) {
        if (curr->data == key) {
            return curr;
        }
        curr = curr->next;
    }
    return NULL;
}
