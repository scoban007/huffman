/*
 -------------------------------------
 File:    queue.c
 Project: cp264_group5_project

 * CP 264 Huffman Coding
 *
 * This file contains the structure of a linked queue structure
 * used to store huffman nodes

 -------------------------------------
 Authors (Group 5): Scoban Pham, Mohammad Safi, Prithvi Pandya, Owen Read, Owen Hagen
 -------------------------------------
 */

#include <stdio.h>
#include <stdlib.h>
#include<string.h>
#include "common.h"
#include "queue.h"

//adds a node to a queue
void enqueue(QUEUE *qp, struct node *np)
    {

	if (qp->rear == NULL) {
	    qp->front = np;
		qp->rear = np;

	}else{
		qp->rear->next = np;
		qp->rear = np;
	    }

    }

//checks if array contains a specific char
int contains(char arr[], char c){

	int contains = 0;

	for (int i = 0; i < strlen(arr); i++){
		if (arr[i] == c){
			contains = 1;
		}
	}

	return contains;

}


//cleans the queue by removing duplicates
void clean_queue(QUEUE *qp)
    {

	char arr[128] = "";
	struct node* curr = qp->front;
	struct node* prev = NULL;
	int i = 0;

	while (curr != NULL){

		if (contains(arr,curr->data) == 0){
			arr[i] = curr->data;
			i++;
			prev = curr;
		} else {
			prev->next = curr->next;
		}
		curr = curr->next;

	}

}




