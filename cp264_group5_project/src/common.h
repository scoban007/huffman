/*
 -------------------------------------
 File:    common.h
 Project: cp264_group5_project

 * CP 264 Huffman Coding
 *
 * This file contains function headers for a Huffman node
 * structure

 -------------------------------------
 Authors (Group 5): Scoban Pham, Mohammad Safi, Prithvi Pandya, Owen Read, Owen Hagen
 -------------------------------------
 */

#ifndef COMMON_H_
#define COMMON_H_

/* node structure for postfix expression by queue and evaluation by stack */
struct node {
	char data; // data can be int operant or a operator
	int freq; //frequency of symbol in the file
	char weight; //weight of node; 1 or 0
	struct node *left; //left node added (for BST)
	struct node *right; //right node added (for BST)
	struct node *next; //next node
};

struct node* new_node(char data, int freq);


#endif /* COMMON_H_ */
