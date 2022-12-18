/**
 * @file queue.h
 * @brief Queue of the project
 * @version 0.1
 * @date 2022-05-10
 * 
 * @copyright Copyright (c) 2022
 * 
 */
#ifndef _QUEUE_H_
#define _QUEUE_H_

#include <stdio.h>
#include <stdlib.h>

/**
 * @brief Structure of an element of a queue
 * 
 */
struct element {
    void* data; /*!< A pointer on a data */
    struct element* prev; /*!< A pointer on the previous element */
    struct element* next; /*!< A pointer on the next element */
};

/**
 * @brief Structure of a queue
 * 
 */
struct queue {
    struct element* first; /*!< A pointer on the first element */
    struct element* last; /*!< A pointer on the last element */
    void* (*cpy) (void*); /*!< A pointer on a copy function */
    void (*del) (void*); /*!< A pointer on a free function */
    int (*cmp) (void*, void*); /*!< A pointer on a compare function */
};

/**
 * @brief Creates and allocates space for an empty queue
 * 
 * @param cpy A pointer on a copy function
 * @param del A pointer on a free function
 * @param cmp A pointer on a cmp function
 * @return struct queue* 
 */
struct queue* queue__empty(void* (*cpy) (void*), void (*del) (void*), int (*cmp) (void*, void*));

/**
 * @brief Returns if q is considered empty
 * 
 * @param q A pointer on a queue
 * @return int 
 */
int queue__is_empty(struct queue* q);

/**
 * @brief Adds data to the queue q  
 * 
 * @param q A pointer on a queue
 * @param data A pointer on a data
 */
void queue__add(struct queue* q, void* data);

/**
 * @brief Removes top of the queue q and returns what was removed
 * 
 * @param q A pointer on a queue
 * @return struct element* 
 */
struct element* queue__pop(struct queue* q);

/**
 * @brief Returns queue q size
 * 
 * @param q A pointer on a queue
 * @return int 
 */
int queue__size(struct queue* q);

/**
 * @brief Frees the queue q
 * 
 * @param q A pointer on a queue
 */
void queue__free(struct queue* q);

/**
 * @brief Frees the element e
 * 
 * @param e A pointer on an element
 */
void element__free(struct element* e);

/**
 * @brief Returns the data from the element e
 * 
 * @param e A pointer on an element
 * @return void* 
 */
void* element__data(struct element* e);

#endif // _QUEUE_H_
