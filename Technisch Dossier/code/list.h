/**
 *  File    list.h
 *  Created 03-05-2016
 *  Author  Matthijs Visser
 *          Amsterdam University of applied sciences
 *  contact Matthijs.Visser@hva.nl
**/

#ifndef LIST_H_
#define LIST_H_

#include <stdio.h>
#include <stdlib.h>

#define DATASIZE 5
#define FIRSTDATAITEM 0

typedef struct node {
    char* data [DATASIZE];
    struct node * next;
}node_t;


void print_list(node_t *listHead);
void insert (node_t ** listHead, char* data[DATASIZE]);
void append (node_t *listHead, char* data[DATASIZE]);

#endif /* LIST_H_ */