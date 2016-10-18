#include <stdlib.h>

#include "struct/queue.h"
#include "struct/list.h"
#include "misc/utils.h"

struct Queue {
    List *elements;
    ListIterator *first;
};

Queue *queue_new(void) {
    Queue *q = (Queue *) malloc(sizeof(*q));
    q->elements = list_new();
    return q;
}

void queue_destroy(Queue *q) {
    list_destroy(q->elements);
    free(q);
}

void queue_add(Queue *q, void *e) {
    list_append(q->elements, e);
}

void *queue_remove(Queue *q) {
    ListIterator *iter = list_iterator(q->elements);
    void *val = listiter_next(iter);
    listiter_remove(iter);
    listiter_destroy(iter);
    return val;
}

void *queue_peek(const Queue *q) {
    ListIterator *iter = list_iterator(q->elements);
    void *val = listiter_next(iter);
    listiter_destroy(iter);
    return val;
}

size_t queue_getSize(const Queue *q) {
    return list_length(q->elements);
}

bool queue_isEmpty(const Queue *q) {
    return list_length(q->elements) == 0;
}
