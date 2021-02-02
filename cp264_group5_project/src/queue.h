/*
 -------------------------------------
 File:    queue.h
 Project: cp264_group5_project

 * CP 264 Huffman Coding
 *
 * This file contains function headers for a
 * linked queue structure

 -------------------------------------
 Authors (Group 5): Scoban Pham, Mohammad Safi, Prithvi Pandya, Owen Read, Owen Hagen
 -------------------------------------
 */

#ifndef QUEUE_H
#define QUEUE_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include<assert.h>
#include<math.h>
#include "queue.h"
#include "common.h"

typedef struct queue {
    struct node *front, *rear;
} QUEUE;

void enqueue(QUEUE *qp, struct node *np);
struct node* dequeue(QUEUE *qp);
void clean_queue(QUEUE *qp);
void printQueue(QUEUE* qp);
void fillQueue(char fileName[], QUEUE* queue);

//mergeSort Functions
struct node* sortedMerge(struct node *a, struct node *b);
void frontBackSplit(struct node *source, struct node **frontRef,
		struct node **backRef);

#endif /* QUEUE_H_*/

