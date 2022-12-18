#include <assert.h>
#include "queue.h"

void* int_copy(void * i)
{
    int* copy = malloc(sizeof(int)*1);
    *copy = *(int*) i;
    return copy;
}

void int_del(void * i)
{
    free(i);
}

int int_cmp(void* a, void* b)
{
    return (*(int*) a - *(int*) b);
}

static void test_queue__empty(void)
{
    printf("%-40s",__func__);

    struct queue* q = queue__empty(int_copy, int_del, int_cmp);

    assert(q->first == NULL);
    assert(q->last == NULL);

    queue__free(q);

    printf("OK\n");
}

static void test_queue__is_empty(void)
{
    printf("%-40s",__func__);

    struct queue* q = malloc(sizeof(struct queue)*1);
    q->first = NULL;
    q->last = NULL;
    
    assert(queue__is_empty(q));

    free(q);

    printf("OK\n");
}

static void test_queue__add(void)
{
    printf("%-40s",__func__);

    struct queue* q = queue__empty(int_copy, int_del, int_cmp);
    int i = 1;

    queue__add(q,&i);

    assert(!queue__is_empty(q));
    assert(q->first==q->last);
    assert(q->cmp(q->first->data,&i)==0);

    int j = 2;  
    queue__add(q,&j);

    assert(!queue__is_empty(q));
    assert(q->cmp(q->first->data,&i)==0);
    assert(q->cmp(q->last->data,&j)==0);
    assert(q->last->prev==q->first);

    queue__free(q);

    printf("OK\n");
}

static void test_queue__pop(void)
{
    printf("%-40s",__func__);

    struct queue* q = queue__empty(int_copy, int_del, int_cmp);
    int n1 = 1;
    int n2 = 2;

    queue__add(q,&n1);
    queue__add(q,&n2);

    struct element *e1 = queue__pop(q);
    assert(*(int*)element__data(e1) == 1);

    assert(q->cmp(e1->data,&n1)==0);
    assert(q->cmp(q->first->data,&n2)==0);
    assert(q->first->next==NULL);
    assert(q->last->next==NULL);
    assert(q->first->prev==NULL);
    assert(q->last->prev==NULL);    

    struct element *e2 = queue__pop(q);
    assert(*(int*)element__data(e2) == 2);

    assert(q->cmp(e2->data,&n2)==0);
    assert(q->first==NULL);
    assert(queue__is_empty(q));

    struct element* e3 = queue__pop(q);
    assert(e3==NULL);

    queue__free(q);
    element__free(e1);
    element__free(e2);

    printf("OK\n");
}

static void test_queue__size(void)
{
    printf("%-40s",__func__);

    struct queue* q = queue__empty(int_copy, int_del, int_cmp);
    int n1 = 1;
    int n2 = 2;
    int n3 = 3;
    int n4 = 4;

    assert(queue__size(q)==0);
    queue__add(q,&n1);
    assert(queue__size(q)==1);
    queue__add(q,&n2);
    assert(queue__size(q)==2);
    queue__add(q,&n3);
    assert(queue__size(q)==3);
    queue__add(q,&n4);
    assert(queue__size(q)==4);

    queue__free(q);

    printf("OK\n");
}

void queue_alltests()
{
    printf("%s\n",__FILE__);

    test_queue__empty();
    test_queue__is_empty();
    test_queue__add();
    test_queue__pop();
    test_queue__size();
}
