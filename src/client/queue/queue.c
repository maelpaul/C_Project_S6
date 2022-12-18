#include "queue.h"

struct queue* queue__empty(void* (*cpy) (void*), void (*del) (void*), int (*cmp) (void*, void*))
{
    struct queue* empty = malloc(sizeof(struct queue)*1);
    empty->first=NULL;
    empty->last=NULL;
    empty->cpy=cpy;
    empty->del=del;
    empty->cmp=cmp;
    return empty; 
}

int queue__is_empty(struct queue* q)
{
    return (q->first==NULL && q->last==NULL);
}

void queue__add(struct queue* q, void* data)
{
    struct element* e = malloc(sizeof(struct element)*1);
    e->data = q->cpy(data);
    e->prev = q->last;
    e->next = NULL;
    if (queue__is_empty(q)) {
        q->first = e;
    }
    else {
        q->last->next = e;
    }
    q->last=e;
}

struct element* queue__pop(struct queue* q)
{
    if (queue__is_empty(q))
        return NULL;
    struct element* ret = q->first;
    q->first = q->first->next;
    if (q->first!=NULL)
        q->first->prev = NULL;
    else
        q->last = NULL;
    ret->next = NULL;
    ret->prev = NULL;
    return ret;
}

int queue__size(struct queue* q)
{
    int acc = 0;
    if (queue__is_empty(q))
        return 0;
    struct element* e = q->first;
    while (e->next!=NULL) {
        acc++;
        e=e->next;
    }
    acc++;
    return acc;
}

void queue__free(struct queue* q)
{
    if (!queue__is_empty(q)) {
        struct element* e = q->first;
        while (e->next!=NULL) {
                q->del(e->data);
                e=e->next;
                free(e->prev);
        }
        q->del(e->data);
        free(e);
    }
    free(q);
}

void element__free(struct element* e)
{
    if (e!=NULL) {
        free(e->data);
        free(e);
    }
}

void* element__data(struct element* e)
{
    return (e->data);
}
