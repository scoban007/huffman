/*
 -------------------------------------
 File:    common.c
 Project: cp264_group5_project

 * CP 264 Huffman Coding
 *
 * This file contains methods for a Huffman node

 -------------------------------------
 Authors (Group 5):  Scoban Pham, Mohammad Safi, Prithvi Pandya, Owen Read, Owen Hagen
 -------------------------------------
 */

#include <stdio.h>
#include <stdlib.h>
#include "common.h"

//initialize new Huffman node
struct node* new_node(char data, int freq) {

	struct node *np = (struct node*) malloc(sizeof(struct node));

	np->data = data;
	np->freq = freq;
	np->next = NULL;
	np->left = NULL;
	np->right = NULL;

	return np;
}


