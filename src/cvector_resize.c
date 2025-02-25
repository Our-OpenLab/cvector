/*
** EPITECH PROJECT, 2024
** cvector
** File description:
** Resize functions for a C dynamic vector similar to std::vector in C++
*/

#include "cvector.h"

int vector_reserve_impl(void **v, const size_t n, const size_t item_size)
{
    vector_header_t *header;
    vector_header_t *new_header;

    if (!v || n == 0 || item_size == 0)
        return VECTOR_FAILURE;
    if (!*v) {
        *v = vector_init(item_size, n);
        return *v ? VECTOR_SUCCESS : VECTOR_FAILURE;
    }
    header = VECTOR_HEADER(*v);
    if (n <= header->capacity)
        return VECTOR_SUCCESS;
    new_header = realloc(header, sizeof(vector_header_t) + (n * item_size));
    #warning "TODO: memset new memory"
    if (!new_header)
        return VECTOR_FAILURE;
    new_header->capacity = n;
    *v = (new_header + 1);
    return VECTOR_SUCCESS;
}

static inline void *vector_init_zeroed(size_t item_size, size_t capacity)
{
    vector_header_t *header;

    if (item_size == 0 || capacity == 0)
        return NULL;
    header = calloc(1, sizeof(vector_header_t) + item_size * capacity);
    if (!header)
        return NULL;
    header->size = capacity;
    header->capacity = capacity;
    header->initial_capacity = capacity;
    return (header + 1);
}

int verif_success(const size_t new_size, size_t old_size,
    vector_header_t *header)
{
    if (new_size < old_size) {
        header->size = new_size;
        return (0);
    }
    if (new_size == old_size)
        return (0);
    return (1);
}

int vector_resize_impl(void **v, const size_t new_size,
    const size_t item_size)
{
    vector_header_t *header;
    void *tmp;
    size_t old_size;

    if (!v || item_size == 0)
        return VECTOR_FAILURE;
    if (!*v) {
        *v = vector_init_zeroed(item_size, new_size);
        return (*v) ? VECTOR_SUCCESS : VECTOR_FAILURE;
    }
    header = VECTOR_HEADER(*v);
    old_size = header->size;
    if (verif_success(new_size, old_size, header) == 0)
        return VECTOR_SUCCESS;
    tmp = vector_ensure_capacity(*v, new_size - old_size, item_size);
    if (!tmp)
        return VECTOR_FAILURE;
    *v = tmp;
    header = VECTOR_HEADER(*v);
    memset((unsigned char *)(*v) + (old_size * item_size),
        0, (new_size - old_size) * item_size);
    header->size = new_size;
    return VECTOR_SUCCESS;
}

int vector_shrink_to_fit_impl(void **v, const size_t item_size)
{
    vector_header_t *header;
    vector_header_t *new_header;

    if (!v || !*v || item_size == 0)
        return VECTOR_FAILURE;
    header = VECTOR_HEADER(*v);
    if (header->capacity == header->size)
        return VECTOR_SUCCESS;
    new_header = realloc(header,
        sizeof(vector_header_t) + (header->size * item_size));
    if (!new_header)
        return VECTOR_FAILURE;
    new_header->capacity = new_header->size;
    *v = (new_header + 1);
    return VECTOR_SUCCESS;
}
