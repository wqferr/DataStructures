#pragma once

#ifndef _QUEUE_H_
#define _QUEUE_H_ 1

#include <stdbool.h>
#include <sys/types.h>

typedef struct Queue Queue;

Queue *queue_new(void);
void queue_destroy(Queue *);

void queue_add(Queue *, void *);
void *queue_remove(Queue *);
void *queue_peek(const Queue *);

size_t queue_getSize(const Queue *);
bool queue_isEmpty(const Queue *);

#endif /* ifndef _QUEUE_H_ */
