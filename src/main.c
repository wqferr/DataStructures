#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "misc/utils.h"
#include "misc/primitive.h"
#include "struct/list.h"
#include "struct/heap.h"

#define SEL_STR_LIST "list"
#define SEL_STR_HEAP "heap"
#define SEL_STR_QUEUE "queue"
#define SEL_STR_GRAPH "graph"


#define CMD_LIST_HLP 'h'
#define CMD_LIST_ADD 'a'
#define CMD_LIST_NXT 'n'
#define CMD_LIST_CUR 'c'
#define CMD_LIST_PRV 'p'
#define CMD_LIST_REM 'r'
#define CMD_LIST_LEN 'l'
#define CMD_LIST_DSP 'P'

#define CMD_HEAP_HLP 'h'
#define CMD_HEAP_ADD 'a'
#define CMD_HEAP_REM 'r'
#define CMD_HEAP_SZE 's'
#define CMD_HEAP_DSP 'P'


#define CMD_END 'q'

#define MSG_INVALID_STR "Invalid structure identifier"
#define ERR_INVALID_STR 1

int mainList(int argc, char *argv[]) {
    size_t bufSize = 0;
    char *buf = NULL;
    char cmd;
    int *elm, i;
    List *list = list_new();
    ListIterator *iter = list_iterator(list), *aux;

    do {
        getline(&buf, &bufSize, stdin);
        cmd = buf[0];
        
        switch (cmd) {
            case CMD_LIST_HLP:
                printf("%c: Display help text\n", CMD_LIST_HLP);
                printf("%c %%d: Add element at iterator\n", CMD_LIST_ADD);
                printf("%c: Iterator forward\n", CMD_LIST_NXT);
                printf("%c: Iterator current\n", CMD_LIST_CUR);
                printf("%c: Iterator backward\n", CMD_LIST_PRV);
                printf("%c: Iterator remove current\n", CMD_LIST_REM);
                printf("%c: List length\n", CMD_LIST_LEN);
                printf("%c: Display list\n", CMD_LIST_DSP);
                printf("\n");
                break;

            case CMD_LIST_ADD:
                elm = int_new(atoi(buf+1));
                listiter_add(iter, elm);
                break;

            case CMD_LIST_NXT:
                if (listiter_hasNext(iter))
                    printf("%d\n", deref(listiter_next(iter), int));
                break;

            case CMD_LIST_CUR:
                if (listiter_hasCurr(iter))
                    printf("%d\n", deref(listiter_curr(iter), int));
                break;

            case CMD_LIST_PRV:
                if (listiter_hasPrev(iter))
                    printf("%d\n", deref(listiter_prev(iter), int));
                break;

            case CMD_LIST_REM:
                elm = listiter_remove(iter);
                if (elm != NULL) {
                    printf("%d\n", deref(elm, int));
                    free(elm);
                }
                break;

            case CMD_LIST_LEN:
                printf("%zu\n", list_length(list));
                break;

            case CMD_LIST_DSP:
                if (list_length(list) > 0) {
                    aux = list_iterator(list);
                    while (listiter_hasNext(aux)) {
                        printf("%d", deref(listiter_next(aux), int));
                        if (listiter_equals(iter, aux))
                            putc('<', stdout);
                        else
                            putc(' ', stdout);
                    }
                    listiter_destroy(aux);
                } else {
                    putc('<', stdout);
                }
                putc('\n', stdout);
                break;
        }

    } while (cmd != CMD_END);

    aux = list_iterator(list);
    while (listiter_hasNext(aux))
        free(listiter_next(aux));
    listiter_destroy(aux);

    listiter_destroy(iter);
    list_destroy(list);

    free(buf);
    return 0;
}

void printHeapElm(const void *elm, void *arg) {
    size_t nPrinted;
    nPrinted = ++deref(arg, size_t);
    if (!(nPrinted & (nPrinted-1))) // power of 2
        putc('\n', stdout);
    printf("%d ", deref(elm, const int));
}

int mainHeap(int argc, char *argv[]) {
    size_t bufSize = 0, n;
    char *buf = NULL;
    int cmd, val;
    int *elm;
    Heap *h = heap_new(&intref_compare);

    do {
        getline(&buf, &bufSize, stdin);
        cmd = buf[0];

        switch (cmd) {
            case CMD_HEAP_HLP:
                printf("%c: Display help text\n", CMD_HEAP_HLP);
                printf("%c %%d: Push element\n", CMD_HEAP_ADD);
                printf("%c: Pop element\n", CMD_HEAP_REM);
                printf("%c: Heap size\n", CMD_HEAP_SZE);
                printf("%c: Display heap\n", CMD_HEAP_DSP);
                printf("\n");
                break;

            case CMD_HEAP_ADD:
                elm = int_new(atoi(buf+1));
                heap_push(h, elm);
                break;

            case CMD_HEAP_REM:
                elm = heap_pop(h);
                if (elm != NULL) {
                    printf("%d\n", *elm);
                    free(elm);
                }
                break;

            case CMD_HEAP_SZE:
                printf("%zu\n", heap_getSize(h));
                break;

            case CMD_HEAP_DSP:
                n = 0;
                heap_preOrder(h, &printHeapElm, &n);
                printf("\n");
                break;
        }
    } while (cmd != CMD_END);

    free(buf);
    heap_destroy(h);

    return 0;
}

int main(int argc, char *argv[]) {
    char *selStr = NULL, *aux;
    size_t bufSize = 0;

    if (argc >= 2) {
        selStr = argv[1];
    } else {
        getline(&selStr, &bufSize, stdin);
        selStr[strlen(selStr)-1] = '\0';
    }

    aux = alloca(bufSize);
    strcpy(aux, selStr);
    free(selStr);
    selStr = aux;

    if (strcmp(selStr, SEL_STR_LIST) == 0) {
        return mainList(argc, argv);
    } else if (strcmp(selStr, SEL_STR_HEAP) == 0) {
        return mainHeap(argc, argv);
    } else if (strcmp(selStr, SEL_STR_QUEUE) == 0) {
    } else if (strcmp(selStr, SEL_STR_GRAPH) == 0) {
    }

    puts(MSG_INVALID_STR);
    return ERR_INVALID_STR;
}
