#ifndef LINKEDLIST_H
#define LINKEDLIST_H

#include <stdio.h>
#include <stdlib.h>

#define DEFINE_LINKEDLIST(TYPE, NAME)                            \
                                                                 \
    typedef struct Node_##NAME                                   \
    {                                                            \
        TYPE data;                                               \
        struct Node_##NAME *prev;                                \
        struct Node_##NAME *next;                                \
    } Node_##NAME;                                               \
                                                                 \
    typedef struct                                               \
    {                                                            \
        Node_##NAME *head;                                       \
        Node_##NAME *tail;                                       \
        size_t size;                                             \
    } NAME;                                                      \
                                                                 \
    NAME create_##NAME(void);                                    \
    void erase_##NAME(NAME *list);                               \
    void delete_##NAME(NAME *list);                              \
    void push_back_##NAME(NAME *list, TYPE value);               \
    void push_front_##NAME(NAME *list, TYPE value);              \
    TYPE pop_back_##NAME(NAME *list);                            \
    TYPE pop_front_##NAME(NAME *list);                           \
    void insert_at_##NAME(NAME *list, size_t index, TYPE value); \
    void delete_at_##NAME(NAME *list, size_t index);             \
    TYPE get_at_##NAME(const NAME *list, size_t index);          \
    int is_equal_##NAME(const NAME *l1, const NAME *l2);         \
                                                                 \
    void push_stack_##NAME(NAME *stack, TYPE value);             \
    TYPE pop_stack_##NAME(NAME *stack);                          \
    TYPE peek_stack_##NAME(const NAME *stack);                   \
                                                                 \
    void enqueue_##NAME(NAME *queue, TYPE value);                \
    TYPE dequeue_##NAME(NAME *queue);                            \
    TYPE peek_queue_##NAME(const NAME *queue);

// #define IMPLEMENT_LINKEDLIST(TYPE, NAME)

#endif // LINKEDLIST_H
