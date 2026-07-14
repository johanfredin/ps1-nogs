//
// Created by johan on 2024-04-07.
//

#ifndef PS1_DEV_HEAP_H
#define PS1_DEV_HEAP_H

#include "stdlib.h"

#define HEAP_START_ADDR 0x800F8000
#define HEAP_SIZE 0x00100000            // 1 mb heap

#define HEAP_FREE_LINKED_LIST(linked_list_root, T)          \
    while (linked_list_root) {                              \
        T *linked_list_aux = linked_list_root;              \
        linked_list_root = linked_list_root->next;          \
        Heap_Free(linked_list_aux);                         \
    }

#define HEAP_FREE_STRING_ARRAY(char_array, n)               \
    for (size_t i = 0; i < n; i++) {                        \
        Heap_Free(char_array[i]);                           \
    }                                                       \
    Heap_Free(char_array)

/**
 * Create another entry in the linked list we are creating if the linked
 * list we are iterating has a next entry. This macro depends on both
 * ptr_to_check and curr_entry to be linked list entries with a *next pointer
 * property in them.
 * @param ptr_to_check the current entry in the linked list we are iterating
 * @param curr_entry the current entry in the linked list we are creating
 * @param ptr_type the type of the curr_entry
 */
#define HEAP_ALLOC_NEW_LINKEDLIST_ENTRY_IF_MORE_DATA(ptr_to_check, curr_entry, ptr_type)    \
    if (!ptr_to_check->next) {                                                              \
        curr_entry->next = NULL;                                                            \
    } else {                                                                                \
        curr_entry->next = Heap_Malloc(sizeof(ptr_type));                                   \
        curr_entry = curr_entry->next;                                                      \
    }

void Heap_Init(void);
void *Heap_Malloc(size_t n);
void *Heap_Calloc(size_t n, size_t s);
void Heap_Free(void *ptr);


#endif //PS1_DEV_HEAP_H
