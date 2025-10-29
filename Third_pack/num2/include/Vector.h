#ifndef VECTOR_H
#define VECTOR_H

#include <stdlib.h>

#define DEFINE_VECTOR(TYPE, NAME)                        \
    typedef struct                                       \
    {                                                    \
        TYPE *data;                                      \
        size_t size;                                     \
        size_t capacity;                                 \
        TYPE (*CopyVoidPtr)(TYPE);                       \
        void (*DeleteVoidPtr)(TYPE);                     \
    } NAME;                                              \
                                                         \
    NAME create_##NAME(size_t initial_capacity,          \
                       TYPE (*CopyFunc)(TYPE),           \
                       void (*DeleteFunc)(TYPE));        \
                                                         \
    void erase_##NAME(NAME *v);                          \
                                                         \
    int is_equal_##NAME(const NAME *v1, const NAME *v2); \
                                                         \
    void copy_##NAME(NAME *dest, const NAME *src);       \
                                                         \
    NAME *copy_##NAME##_new(const NAME *src);            \
                                                         \
    void push_back_##NAME(NAME *v, TYPE value);          \
                                                         \
    void delete_at_##NAME(NAME *v, size_t index);        \
                                                         \
    TYPE get_at_##NAME(const NAME *v, size_t index);     \
                                                         \
    void delete_##NAME(NAME *v);

#define IMPLEMENT_VECTOR(TYPE, NAME)                                        \
    NAME create_##NAME(size_t initial_capacity,                             \
                       TYPE (*CopyFunc)(TYPE),                              \
                       void (*DeleteFunc)(TYPE))                            \
    {                                                                       \
        NAME v;                                                             \
        v.data = malloc(initial_capacity * sizeof(TYPE));                   \
        v.size = 0;                                                         \
        v.capacity = initial_capacity;                                      \
        v.CopyVoidPtr = CopyFunc;                                           \
        v.DeleteVoidPtr = DeleteFunc;                                       \
        return v;                                                           \
    }                                                                       \
                                                                            \
    void erase_##NAME(NAME *v)                                              \
    {                                                                       \
        free(v->data);                                                      \
        v->data = NULL;                                                     \
        v->size = 0;                                                        \
        v->capacity = 0;                                                    \
    }                                                                       \
                                                                            \
    int is_equal_##NAME(const NAME *v1, const NAME *v2)                     \
    {                                                                       \
        if (v1 == v2)                                                       \
            return 1;                                                       \
        if (!v1 || !v2)                                                     \
            return 0;                                                       \
        if (v1->size != v2->size)                                           \
            return 0;                                                       \
        for (size_t i = 0; i < v1->size; i++)                               \
            if (v1->data[i] != v2->data[i])                                 \
                return 0;                                                   \
        return 1;                                                           \
    }                                                                       \
                                                                            \
    void copy_##NAME(NAME *dest, const NAME *src)                           \
    {                                                                       \
        if (!src || !dest || dest == src)                                   \
            return;                                                         \
        if (dest->capacity < src->size)                                     \
        {                                                                   \
            TYPE *new_data = realloc(dest->data, src->size * sizeof(TYPE)); \
            if (!new_data)                                                  \
                return;                                                     \
            dest->data = new_data;                                          \
            dest->capacity = src->size;                                     \
        }                                                                   \
        for (size_t i = 0; i < src->size; i++)                              \
            dest->data[i] = src->data[i];                                   \
        dest->size = src->size;                                             \
    }                                                                       \
                                                                            \
    NAME *copy_##NAME##_new(const NAME *src)                                \
    {                                                                       \
        if (!src)                                                           \
            return NULL;                                                    \
        NAME *dest = malloc(sizeof(NAME));                                  \
        if (!dest)                                                          \
            return NULL;                                                    \
        dest->data = malloc(src->capacity * sizeof(TYPE));                  \
        if (!dest->data)                                                    \
        {                                                                   \
            free(dest);                                                     \
            return NULL;                                                    \
        }                                                                   \
        for (size_t i = 0; i < src->size; i++)                              \
            dest->data[i] = src->data[i];                                   \
        dest->size = src->size;                                             \
        dest->capacity = src->capacity;                                     \
        dest->CopyVoidPtr = src->CopyVoidPtr;                               \
        dest->DeleteVoidPtr = src->DeleteVoidPtr;                           \
        return dest;                                                        \
    }                                                                       \
                                                                            \
    void push_back_##NAME(NAME *v, TYPE value)                              \
    {                                                                       \
        if (!v)                                                             \
            return;                                                         \
        if (v->size >= v->capacity)                                         \
        {                                                                   \
            size_t new_capacity = (v->capacity == 0) ? 1 : v->capacity * 2; \
            TYPE *new_data = realloc(v->data, new_capacity * sizeof(TYPE)); \
            if (!new_data)                                                  \
                return;                                                     \
            v->data = new_data;                                             \
            v->capacity = new_capacity;                                     \
        }                                                                   \
        v->data[v->size++] = value;                                         \
    }                                                                       \
                                                                            \
    void delete_at_##NAME(NAME *v, size_t index)                            \
    {                                                                       \
        if (!v || index >= v->size)                                         \
            return;                                                         \
        if (v->DeleteVoidPtr)                                               \
            v->DeleteVoidPtr(v->data[index]);                               \
        for (size_t i = index; i < v->size - 1; i++)                        \
            v->data[i] = v->data[i + 1];                                    \
        v->size--;                                                          \
    }                                                                       \
                                                                            \
    TYPE get_at_##NAME(const NAME *v, size_t index)                         \
    {                                                                       \
        if (!v || index >= v->size)                                         \
            return (TYPE)0;                                                 \
        return v->data[index];                                              \
    }                                                                       \
                                                                            \
    void delete_##NAME(NAME *v)                                             \
    {                                                                       \
        if (!v)                                                             \
            return;                                                         \
        free(v->data);                                                      \
        v->data = NULL;                                                     \
        v->size = 0;                                                        \
        v->capacity = 0;                                                    \
    }

#endif // VECTOR_H
