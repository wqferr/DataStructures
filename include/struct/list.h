#pragma once

#ifndef _LIST_H_
#define _LIST_H_ 1

#include <stdbool.h>
#include <sys/types.h>

#include "misc/utils.h"

typedef struct List List;
typedef struct ListIterator ListIterator;
typedef struct ListCIter ListCIter;

List *list_new(void);
void list_destroy(List *);

void list_append(List *, void *);
void *list_getFirst(const List *);
void *list_getLast(const List *);
void *list_removeFirst(List *);
void *list_removeLast(List *);
bool list_contains(const List *, void *);
void *list_remove(List *, void *);
void *list_removeCmp(List *, void *, int (*) (const void *, const void *));

size_t list_length(const List *);

ListIterator *list_iterator(List *);
ListCIter *list_citer(const List *);

ListIterator *listiter_copy(const ListIterator *);
ListCIter *listciter_copy(const ListCIter *);

bool listiter_hasPrev(const ListIterator *);
bool listiter_hasCurr(const ListIterator *);
bool listiter_hasNext(const ListIterator *);
void *listiter_prev(ListIterator *);
void *listiter_curr(const ListIterator *);
void *listiter_next(ListIterator *);
void listiter_add(ListIterator *, void *);
void *listiter_remove(ListIterator *);
bool listiter_equals(const ListIterator *, const ListIterator *);
void listiter_destroy(ListIterator *);

bool listciter_hasPrev(const ListCIter *);
bool listciter_hasCurr(const ListCIter *);
bool listciter_hasNext(const ListCIter *);
void *listciter_prev(ListCIter *);
void *listciter_curr(const ListCIter *);
void *listciter_next(ListCIter *);
bool listciter_equals(const ListCIter *, const ListCIter *);
void listciter_destroy(ListCIter *);

#endif /* ifndef _LIST_H_ */
