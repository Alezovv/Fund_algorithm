#ifndef LINKEDLIST_H
#define LINKEDLIST_H

#include <stdio.h>
#include <stdlib.h>
#include "log.h"

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
    NAME *create_##NAME(void);                                   \
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

#define IMPLEMENT_LINKEDLIST(TYPE, NAME)                                    \
    NAME *create_##NAME(void)                                               \
    {                                                                       \
        NAME *obj = (NAME *)malloc(sizeof(NAME));                           \
        if (!obj)                                                           \
            return NULL;                                                    \
        obj->head = NULL;                                                   \
        obj->tail = NULL;                                                   \
        obj->size = 0;                                                      \
        return obj;                                                         \
    }                                                                       \
                                                                            \
    void erase_##NAME(NAME *list)                                           \
    {                                                                       \
        if (!list || list->size == 0)                                       \
            return;                                                         \
                                                                            \
        Node_##NAME *node = list->head;                                     \
        while (node)                                                        \
        {                                                                   \
            Node_##NAME *next = node->next;                                 \
            free(node);                                                     \
            node = next;                                                    \
        }                                                                   \
                                                                            \
        list->head = NULL;                                                  \
        list->tail = NULL;                                                  \
        list->size = 0;                                                     \
    }                                                                       \
                                                                            \
    void delete_##NAME(NAME *list)                                          \
    {                                                                       \
        if (!list || list->size == 0)                                       \
            return;                                                         \
                                                                            \
        Node_##NAME *node = list->head;                                     \
        while (node)                                                        \
        {                                                                   \
            Node_##NAME *next = node->next;                                 \
            free(node);                                                     \
            node = next;                                                    \
        }                                                                   \
        list->head = NULL;                                                  \
        list->tail = NULL;                                                  \
        list->size = 0;                                                     \
        free(list);                                                         \
    }                                                                       \
                                                                            \
    void push_back_##NAME(NAME *list, TYPE value)                           \
    {                                                                       \
        if (!list)                                                          \
            return;                                                         \
        Node_##NAME *new_node = (Node_##NAME *)malloc(sizeof(Node_##NAME)); \
        if (!new_node)                                                      \
            return;                                                         \
        new_node->data = value;                                             \
        new_node->next = NULL;                                              \
        new_node->prev = list->tail;                                        \
                                                                            \
        if (!list->tail)                                                    \
            list->head = new_node;                                          \
        else                                                                \
            list->tail->next = new_node;                                    \
                                                                            \
        list->tail = new_node;                                              \
        list->size++;                                                       \
    }                                                                       \
                                                                            \
    void push_front_##NAME(NAME *list, TYPE value)                          \
    {                                                                       \
        if (!list)                                                          \
            return;                                                         \
        Node_##NAME *new_node = (Node_##NAME *)malloc(sizeof(Node_##NAME)); \
        if (!new_node)                                                      \
            return;                                                         \
        new_node->data = value;                                             \
        new_node->prev = NULL;                                              \
        new_node->next = list->head;                                        \
                                                                            \
        if (!list->head)                                                    \
            list->tail = new_node;                                          \
        else                                                                \
            list->head->prev = new_node;                                    \
                                                                            \
        list->head = new_node;                                              \
        list->size++;                                                       \
    }                                                                       \
                                                                            \
    TYPE pop_back_##NAME(NAME *list)                                        \
    {                                                                       \
        if (!list || list->size == 0)                                       \
        {                                                                   \
            TYPE empty = {0};                                               \
            return empty;                                                   \
        }                                                                   \
        Node_##NAME *temp = list->tail;                                     \
        TYPE value = temp->data;                                            \
        if (list->head != list->tail)                                       \
        {                                                                   \
            list->tail = list->tail->prev;                                  \
            list->tail->next = NULL;                                        \
        }                                                                   \
        else                                                                \
        {                                                                   \
            list->head = NULL;                                              \
            list->tail = NULL;                                              \
        }                                                                   \
        free(temp);                                                         \
        list->size--;                                                       \
                                                                            \
        return value;                                                       \
    }                                                                       \
                                                                            \
    TYPE pop_front_##NAME(NAME *list)                                       \
    {                                                                       \
        if (!list || list->size == 0)                                       \
        {                                                                   \
            TYPE empty = {0};                                               \
            return empty;                                                   \
        }                                                                   \
                                                                            \
        Node_##NAME *temp = list->head;                                     \
        TYPE value = temp->data;                                            \
        if (list->head != list->tail)                                       \
        {                                                                   \
            list->head = list->head->next;                                  \
            list->head->prev = NULL;                                        \
        }                                                                   \
        else                                                                \
        {                                                                   \
            list->head = NULL;                                              \
            list->tail = NULL;                                              \
        }                                                                   \
        free(temp);                                                         \
        list->size--;                                                       \
                                                                            \
        return value;                                                       \
    }                                                                       \
                                                                            \
    void insert_at_##NAME(NAME *list, size_t index, TYPE value)             \
    {                                                                       \
        if (!list)                                                          \
            return;                                                         \
        if (index > list->size)                                             \
            return;                                                         \
                                                                            \
        Node_##NAME *node = (Node_##NAME *)malloc(sizeof(Node_##NAME));     \
        if (!node)                                                          \
            return;                                                         \
                                                                            \
        node->data = value;                                                 \
        node->next = NULL;                                                  \
        node->prev = NULL;                                                  \
                                                                            \
        if (index == 0)                                                     \
        {                                                                   \
            node->next = list->head;                                        \
            if (list->head)                                                 \
                list->head->prev = node;                                    \
            list->head = node;                                              \
            if (list->size == 0)                                            \
                list->tail == node;                                         \
        }                                                                   \
        else if (index == list->size)                                       \
        {                                                                   \
            node->prev = list->tail;                                        \
            if (list->tail)                                                 \
                list->tail->next = node;                                    \
            list->tail = node;                                              \
        }                                                                   \
        else                                                                \
        {                                                                   \
            Node_##NAME *tmp = list->head;                                  \
            for (size_t i = 1; i < index; i++)                              \
                tmp = tmp->next;                                            \
            node->next = tmp->next;                                         \
            node->prev = tmp;                                               \
            tmp_next->prev = node;                                          \
            tmp->next = node;                                               \
        }                                                                   \
        list->size++;                                                       \
    }                                                                       \
                                                                            \
    void delete_at_##NAME(NAME *list, size_t index)                         \
    {                                                                       \
        if (!list || list->size == 0)                                       \
            return;                                                         \
                                                                            \
        if (index >= list->size)                                            \
            return;                                                         \
                                                                            \
        Node_##NAME *node = list->head;                                     \
        for (size_t i = 0; i < index; i++)                                  \
            node = node->next;                                              \
                                                                            \
        if (node == list->head)                                             \
        {                                                                   \
            list->head = node->next;                                        \
            if (list->head)                                                 \
                list->head->prev = NULL;                                    \
        }                                                                   \
        else if (node == list->tail)                                        \
        {                                                                   \
            list->tail = node->prev;                                        \
            if (list->tail)                                                 \
                list->tail->next = NULL;                                    \
        }                                                                   \
        else                                                                \
        {                                                                   \
            node->prev->next = node->next;                                  \
            node->next->prev = node->prev;                                  \
        }                                                                   \
                                                                            \
        free(node);                                                         \
        list->size--;                                                       \
    }                                                                       \
                                                                            \
    TYPE get_at_##NAME(const NAME *list, size_t index)                      \
    {                                                                       \
        TYPE empty = {0};                                                   \
        if (!list || list->size == 0)                                       \
            return empty;                                                   \
                                                                            \
        if (index >= list->size)                                            \
            return empty;                                                   \
                                                                            \
        size_t i = 0;                                                       \
        Node_##NAME *node = list->head;                                     \
        while (i++ != index)                                                \
            node = node->next;                                              \
        return node->data;                                                  \
    }                                                                       \
                                                                            \
    int is_equal_##NAME(const NAME *l1, const NAME *l2)                     \
    {                                                                       \
        if (!l1 || !l2)                                                     \
            return 0;                                                       \
                                                                            \
        Node_int_list *na = l1->head;                                       \
        Node_int_list *nb = l2->head;                                       \
                                                                            \
        while (na && nb)                                                    \
        {                                                                   \
            if (na->data < nb->data)                                        \
                return -1;                                                  \
            else if (na->data > nb->data)                                   \
                return 1;                                                   \
                                                                            \
            na = na->next;                                                  \
            nb = nb->next;                                                  \
        }                                                                   \
                                                                            \
        if (na && !nb)                                                      \
            return 1;                                                       \
        else if (!na && nb)                                                 \
            return -1;                                                      \
        else                                                                \
            return 0;                                                       \
    }                                                                       \
                                                                            \
    void push_stack_##NAME(NAME *stack, TYPE value)                         \
    {
    }
#endif // LINKEDLIST_H
