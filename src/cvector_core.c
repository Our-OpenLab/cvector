/*
** EPITECH PROJECT, 2024
** cvector
** File description:
** Core functions for a C dynamic vector similar to std::vector in C++
*/

#include "cvector.h"

void *vector_init(size_t item_size, size_t capacity)
{
    vector_header_t *header;

    if (item_size == 0 || capacity == 0)
        return NULL;
    header = malloc(sizeof(vector_header_t) + item_size * capacity);
    if (!header)
        return NULL;
    header->size = 0;
    header->capacity = capacity;
    header->initial_capacity = capacity;
    return (header + 1);
}

void *vector_ensure_capacity(void *v, size_t item_count, size_t item_size)
{
    vector_header_t *header;
    size_t new_capacity;
    size_t required_capacity;

    if (!v)
        return vector_init(item_size, item_count);
    header = VECTOR_HEADER(v);
    required_capacity = header->size + item_count;
    if (required_capacity <= header->capacity)
        return v;
    new_capacity = header->capacity * 2;
    while (new_capacity < required_capacity)
        new_capacity *= 2;
    header = realloc(header,
        sizeof(vector_header_t) + (new_capacity * item_size));
    if (!header)
        return NULL;
    header->capacity = new_capacity;
    return (header + 1);
}

int vector_push_back_impl(void **v, const void *val, size_t count,
    size_t item_size)
{
    vector_header_t *header;
    void *tmp;

    if (!v || !val || count == 0 || item_size == 0)
        return VECTOR_FAILURE;
    tmp = vector_ensure_capacity(*v, count, item_size);
    if (!tmp)
        return VECTOR_FAILURE;
    *v = tmp;
    header = VECTOR_HEADER(*v);
    memcpy((unsigned char *)(*v) + (header->size * item_size), val,
        count * item_size);
    header->size += count;
    return VECTOR_SUCCESS;
}

void vector_pop_back_impl(void **v, size_t count, size_t item_size)
{
    vector_header_t *header;

    if (!v || !*v || count == 0 || item_size == 0)
        return;
    header = VECTOR_HEADER(*v);
    if (count >= header->size) {
        header->size = 0;
    } else {
        header->size -= count;
    }
}
