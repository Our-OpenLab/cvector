/*
** EPITECH PROJECT, 2024
** cvector
** File description:
** add and del functions for a C dynamic vector similar to std::vector in C++
*/

#include "cvector.h"

int vector_insert_impl(void **v, const size_t index, const void *val,
    const size_t count, size_t item_size)
{
    vector_header_t *header;
    void *tmp;
    size_t required_size;
    size_t old_size;

    if (!v || !val || count == 0 || item_size == 0)
        return VECTOR_FAILURE;
    header = (*v) ? VECTOR_HEADER(*v) : NULL;
    old_size = header ? header->size : 0;
    required_size = ((index > old_size) ? index : old_size) + count;
    tmp = vector_ensure_capacity(*v, required_size - old_size, item_size);
    if (!tmp)
        return VECTOR_FAILURE;
    *v = tmp;
    header = VECTOR_HEADER(*v);
    if (index > old_size)
        memset((unsigned char *)(*v) + old_size * item_size, 0,
            (index - old_size) * item_size);
    if (index < old_size)
        memmove((unsigned char *)(*v) + (index + count) * item_size,
            (unsigned char *)(*v) + index * item_size,
                (old_size - index) * item_size);
    memcpy((unsigned char *)(*v) + index * item_size, val, count * item_size);
    header->size = required_size;
    return VECTOR_SUCCESS;
}

void vector_erase_impl(void **v, const size_t index, size_t count,
    const size_t item_size)
{
    vector_header_t *header;
    size_t old_size;

    if (!v || !*v || count == 0 || item_size == 0)
        return;
    header = VECTOR_HEADER(*v);
    if (index >= header->size)
        return;
    if (index + count > header->size)
        count = header->size - index;
    old_size = header->size;
    memmove((unsigned char *)*v + index * item_size,
        (unsigned char *)*v + (index + count) * item_size,
            (old_size - index - count) * item_size);
    header->size = old_size - count;
}
