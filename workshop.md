### **EPITECH PROJECT, 2024**  
**CVector - Workshop**  

---

### **Contexte**
Le but de ce projet est de développer une implémentation en C d'un vecteur dynamique similaire à `std::vector` en C++. Vous devrez compléter un fichier d'en-tête partiellement rempli et implémenter les fonctions principales dans différents fichiers `.c`.

Le vecteur dynamique devra permettre :
1. L'allocation dynamique de mémoire.
2. L'ajout, la suppression et le redimensionnement des éléments.
3. La gestion explicite de la mémoire.

---

### **Objectifs**
1. Compléter le fichier d’en-tête `cvector.h` en remplissant les parties marquées comme `TODO`.
2. Implémenter les fonctions manquantes dans les fichiers suivants :
   - `cvector_core.c`
   - `cvector_insert_erase.c`
   - `cvector_resize.c`
3. Tester votre implémentation avec des cas simples et des assertions.

---

### **Fichier `cvector.h`**

Voici le fichier partiellement complété que vous devrez modifier :

```c
#ifndef CVECTOR_H
#define CVECTOR_H

#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <stdio.h>

#define VECTOR_SUCCESS 0
#define VECTOR_FAILURE 1

/**
 * @brief Structure for the vector header.
 * Similar to std::vector, it only stores size and capacity.
 * Data starts immediately after this structure.
 */
typedef struct {
  size_t size;         // Number of elements currently in the vector
  size_t capacity;     // Total capacity allocated
  size_t initial_capacity;
} vector_header_t;

#if defined(__GNUC__) || defined(__clang__)
#define WARN_UNUSED_RESULT __attribute__((warn_unused_result))
#else
#define WARN_UNUSED_RESULT
#endif

// Access the vector header
#define VECTOR_HEADER(v) (TODO) // Complétez cette macro pour accéder à l'en-tête du vecteur

// Get the size of the vector
#define vector_size(v) ((v) ? (TODO) : 0) // Complétez pour retourner la taille actuelle du vecteur

// Get the capacity of the vector
#define vector_capacity(v) ((v) ? (TODO) : 0) // Complétez pour retourner la capacité totale

// Check if the vector is empty
#define vector_empty(v) (TODO) // Implémentez une condition pour vérifier si le vecteur est vide

// Get a pointer to the underlying data
#define vector_data(v) (TODO) // Complétez pour retourner un pointeur vers les données

// Get the first element
#define vector_front(v) ((v) ? (v) : NULL)

// Get the last element
#define vector_back(v) ((v) && vector_size(v) > 0 ? (TODO) : NULL) // Complétez pour retourner le dernier élément

// Create a new vector of type T with initial capacity c
#define VECTOR(T, c) ((T*)vector_init(sizeof(T), (c)))

// Push back n elements (from pointer val) to the vector
#define vector_push_back(v, val, n) vector_push_back_impl((void**)&(v), (const void*)(val), (n), sizeof(*(v))) // Complétez pour ajouter des éléments au vecteur

// Pop back n elements
#define vector_pop_back(v, n) vector_pop_back_impl(TODO, (n), TODO) // Complétez pour retirer des éléments du vecteur

// Clear the vector (size = 0, but doesn't change capacity)
#define vector_clear(v) (TODO) // Complétez pour réinitialiser la taille à 0

// Destroy the vector completely (free memory)
#define vector_destroy(v) (TODO) // Complétez pour libérer la mémoire allouée au vecteur

// Reserve capacity
#define vector_reserve(v, n) vector_reserve_impl(TODO, (n), TODO) // Complétez pour réserver de la capacité

// Resize the vector (increase or decrease size)
#define vector_resize(v, new_size) vector_resize_impl(TODO, (new_size), TODO) // Complétez pour redimensionner le vecteur

// Shrink to fit (reduce capacity to current size)
#define vector_shrink_to_fit(v) vector_shrink_to_fit_impl(TODO, TODO)

// Insert elements at the specified index
#define vector_insert(v, index, val, count) vector_insert_impl(TODO, (index), (val), (count), TODO)

// Erase elements at the specified index
#define vector_erase(v, index, count) vector_erase_impl(TODO, (index), (count), TODO)

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief Initialize a new vector with given element size and capacity.
 *
 * @param item_size Size of each element.
 * @param capacity Initial capacity.
 * @return Pointer to the newly allocated vector, or NULL on failure.
 */
void *vector_init(size_t item_size, size_t capacity) WARN_UNUSED_RESULT;

/**
 * @brief Ensure the vector has enough capacity for at least item_count new elements.
 *
 * @param v Pointer to the vector.
 * @param item_count Number of additional elements required.
 * @param item_size Size of each element.
 * @return A pointer to the (possibly reallocated) vector, or NULL on failure.
 */
void *vector_ensure_capacity(void *v, size_t item_count, size_t item_size) WARN_UNUSED_RESULT;

/**
 * @brief Push back n elements from val to the end of the vector.
 *
 * @param v Address of the vector pointer.
 * @param val Pointer to the data to insert.
 * @param n Number of elements to insert.
 * @param item_size Size of each element.
 * @return VECTOR_SUCCESS if successful, VECTOR_FAILURE otherwise.
 */
int vector_push_back_impl(TODO v, const void *val, size_t n, size_t item_size) WARN_UNUSED_RESULT;

/**
 * @brief Pop back n elements from the vector.
 *
 * @param v Address of the vector pointer.
 * @param n Number of elements to remove from the end.
 * @param item_size Size of each element.
 */
void vector_pop_back_impl(TODO v, size_t n, size_t item_size);

/**
 * @brief Reserve capacity for at least 'c' elements.
 *
 * @param v Address of the vector pointer.
 * @param n Number of elements to reserve.
 * @param item_size Size of each element.
 * @return VECTOR_SUCCESS on success, VECTOR_FAILURE on failure.
 */
int vector_reserve_impl(TODO v, size_t n, size_t item_size);

/**
 * @brief Resize the vector to have new_size elements.
 * If new_size > current_size, new elements are zero-initialized.
 * If new_size < current_size, elements are truncated.
 *
 * @param v Address of the vector pointer.
 * @param new_size New desired size.
 * @param item_size Size of each element.
 * @return VECTOR_SUCCESS on success, VECTOR_FAILURE on failure.
 */
int vector_resize_impl(TODO v, size_t new_size, size_t item_size);

/**
 * @brief Shrink the capacity of the vector to match its current size.
 *
 * @param v Address of the vector pointer.
 * @param item_size Size of each element.
 * @return VECTOR_SUCCESS on success, VECTOR_FAILURE on failure.
 */
int vector_shrink_to_fit_impl(TODO v, size_t item_size);

/**
 * @brief Insert an element at the specified index (like std::vector::insert).
 *
 * @param v Address of the vector pointer.
 * @param index Position where to insert the elements.
 * @param val Pointer to the element(s) to insert.
 * @param count Number of elements to insert.
 * @param item_size Size of each element.
 * @return VECTOR_SUCCESS on success, VECTOR_FAILURE on failure.
 */
int vector_insert_impl(TODO v, size_t index, const void *val, size_t count, size_t item_size) WARN_UNUSED_RESULT;

/**
 * @brief Erase elements at the specified index (like std::vector::erase).
 *
 * @param v Address of the vector pointer.
 * @param index Position of the first element to erase.
 * @param count Number of elements to erase.
 * @param item_size Size of each element.
 */
void vector_erase_impl(TODO v, size_t index, size_t count, size_t item_size);

#ifdef __cplusplus
}
#endif

#endif // CVECTOR_H
```

---

### **Fichier `cvector_core.c`**

Dans ce fichier, implémentez les fonctions principales du vecteur dynamique. Voici les squelettes des fonctions :

```c
#include "cvector.h"

void *vector_init(size_t item_size, size_t capacity)
{
    // TODO : Implémentez la logique pour initialiser un vecteur
}

void *vector_ensure_capacity(void *v, size_t item_count, size_t item_size)
{
    // TODO : Implémentez la logique pour garantir la capacité
}

int vector_push_back_impl(TODO v, const void *val, size_t count, size_t item_size)
{
    // TODO : Implémentez l'ajout d'éléments à la fin
}

void vector_pop_back_impl(TODO v, size_t count, size_t item_size)
{
    // TODO : Implémentez la suppression des éléments en fin de vecteur
}
```

---

### **Fichier `cvector_insert_erase.c`**

Dans ce fichier, implémentez les fonctions d'insertion et de suppression.

```c
#include "cvector.h"

int vector_insert_impl(TODO v, const size_t index, const void *val, const size_t count, size_t item_size)
{
    // TODO : Implémentez la logique pour insérer des éléments
}

void vector_erase_impl(TODO v, const size_t index, size_t count, const size_t item_size)
{
    // TODO : Implémentez la logique pour supprimer des éléments
}
```

---

### **Fichier `cvector_resize.c`**

Dans ce fichier, implémentez les fonctions de redimensionnement.

```c
#include "cvector.h"

int vector_reserve_impl(void **v, const size_t n,
                               const size_t item_size)
{

    // TODO : Implémentez la logique pour réserver de la capacité
}

static inline void *vector_init_zeroed(size_t item_size, size_t capacity)
{
    // TODO : Implémentez la logique pour initialiser un vecteur avec des éléments à zéro
    
    -> man calloc
}

int vector_resize_impl(TODO v, const size_t new_size, const size_t item_size)
{
    // TODO : Implémentez la logique pour redimensionner le vecteur
    
    -> utiliser vector_init_zeroed si !*v
}

int vector_shrink_to_fit_impl(TODO v, const size_t item_size)
{
    // TODO : Implémentez la logique pour réduire la capacité
    
    -> man realloc
}
```

---

### **Instructions**

1. **Complétez les `TODO` :**
   - Remplissez les parties manquantes dans chaque fichier.
   - Respectez les signatures des fonctions.

2. **Compilez et testez :**
   - Créez un fichier `main.c` pour tester toutes les fonctionnalités.
   - Utilisez des cas simples pour valider chaque opération.

3. **Critères d’évaluation :**
   - Toutes les fonctionnalités doivent fonctionner correctement.
   - La gestion de la mémoire doit être efficace et sans fuites.

---

Ce sujet vous permet de travailler sur un concept fondamental de la programmation : la gestion dynamique de la mémoire. Si vous avez des questions ou souhaitez des clarifications, n’hésitez pas à demander.
