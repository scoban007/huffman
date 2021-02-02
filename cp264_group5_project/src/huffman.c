/*
 -------------------------------------
 File:    huffman.c
 Project: cp264_group5_project

 * CP 264 Huffman Coding
 *
 * This file contains the main program,the structure of the Huffman node
 * and user interface for running your Huffman Encoder/Decoder.

 -------------------------------------
 Authors (Group 5): Scoban Pham, Mohammad Safi, Prithvi Pandya, Owen Read, Owen Hagen
 -------------------------------------
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <math.h>
#include "queue.h"
#include "common.h"

#define MAX_SIZE 1000000 //maximum size of an array

//main function that performs the merge sort
void mergeSort(struct node **headref) {
	struct node *head = *headref; //references the head
	struct node *a; //pointer to the first sublist
	struct node *b; //pointer to the second sublist

	//checks if the list is either empty or only has a length of 1
	if ((head == NULL) || (head->next == NULL)) {
		return;
	}
	// splits head into 'a' and 'b' sublists
	frontBackSplit(head, &a, &b);
	//recursively sorts the sublists
	mergeSort(&a);
	mergeSort(&b);
	//merges the two sorted lists
	*headref = sortedMerge(a, b);
}

//is used to split nodes of the given list into front and back halves, using the fast/slow pointer strategy
void frontBackSplit(struct node *source, struct node **frontRef,
		struct node **backRef) {
	//initializes the fast and slow pointers
	struct node *fast;
	struct node *slow;
	slow = source;
	fast = source->next;
	// Advance 'fast' two node, and advance 'slow'one mode
	while (fast != NULL) {
		fast = fast->next;
		if (fast != NULL) {
			slow = slow->next;
			fast = fast->next;
		}
	}
	//'slow' is before the midpoint in the list, so split it in two as that point
	*frontRef = source;
	*backRef = slow->next;
	slow->next = NULL;
}

struct node* sortedMerge(struct node *a, struct node *b) {
	struct node *result = NULL;
	//Base Case
	if (a == NULL) {
		return (b);
	} else if (b == NULL) {
		return (a);
	}
	//picks either a or b, and recurses
	if (a->freq <= b->freq) {
		result = a;
		result->next = sortedMerge(a->next, b);
	} else {
		result = b;
		result->next = sortedMerge(a, b->next);
	}
	return (result);
}

//Merge queue nodes into a BST node
struct node* BSTmergeNodes(QUEUE *qp) {
	assert(qp->front != NULL); //checks if front is NULL, returns error if NULL, otherwise function continues normally

	struct node *mergedNode;
	int totalFreq;

	if (qp->front->next != NULL) {
		totalFreq = qp->front->freq+qp->front->next->freq;
		mergedNode = new_node('*', totalFreq); //create new node with only frequency and no value
		mergedNode->left = qp->front; //sets left as front (the lower frequency node)
		qp->front = qp->front->next; //sets front of queue to next node
		mergedNode->left->weight = '0'; //sets left node weight as 0
		mergedNode->left->next = NULL; //sets left node's next node to NULL (removes from queue)
		mergedNode->right = qp->front; //sets right as second from front (the higher frequency node)
		qp->front = qp->front->next; //sets front of queue to next node
		mergedNode->right->weight = '1'; //sets right node weight as 1
		mergedNode->right->next = NULL; //sets right node's next node to NULL (removes from queue)


		mergedNode->next = qp->front;
		qp->front = mergedNode;
		mergeSort(&qp->front);


	} else { //returns passed queue node if it is the only node in the queue
		mergedNode = qp->front;
	}
	return mergedNode;

}

//auxiliary function for encodeBits
void encodeBits_aux(struct node *root, char bits[],char toEncode,char* encoded){

		char bit[1000] = "";

		if ((root != NULL)){

			if (root->data == toEncode) {

				strcpy(bit,bits);
				strncat(bits, &root->weight,1);
				if (root->data != '\n'){
					printf("    %c:       %d     %s\n",root->data,root->freq, bits);//prints bits if leaf (letter) node is encountered
				} else {
					printf("    %s:       %d     %s\n","\\n",root->freq, bits);
				}

				strcat(encoded, bits);
				strcpy(bits,bit);

			} else {

				strcpy(bit,bits);
				strncat(bit, &root->weight,1);

			}

			encodeBits_aux(root->left, bit,toEncode,encoded); //traverse left subtree
			encodeBits_aux(root->right, bit,toEncode,encoded); //traverse right subtree
		}
}

//main encode function for user to call
void encodeBits(struct node *root,char fileName[]){

	char bits[MAX_SIZE] = "";
	char line[MAX_SIZE] = "";
	char encoded[MAX_SIZE] = "";

	FILE* fptr;
	fptr= fopen(fileName, "r"); //open text file for encoding

	FILE* fptr2;
	fptr2 = fopen("encoded.txt", "w"); //create encoded.txt to write to

	if (fptr == NULL) {
			printf("Error Opening File");
	} else {

		while (fgets(line, sizeof(line),fptr)){

			for (int i = 0; i < strlen(line); i++){
				encodeBits_aux(root,bits,line[i],encoded);
			}

		}
	}

	fprintf(fptr2,"%s\n",encoded);
	fclose(fptr2);
	fclose(fptr);

}



//recursively traverses BST to decode character given bits
void decodeBits_aux(struct node *root, char bits[], int i,struct node* top,char decoded[]) {

	if ((root != NULL)&&(i <= strlen(bits))){

		if ((root->left == NULL) && (root->right == NULL)){

			strncat(decoded,&root->data,1);

			decodeBits_aux(top, bits, i,top,decoded);

		}

		if (bits[i] == '0'){

			decodeBits_aux(root->left, bits, i + 1,top,decoded);

		} else{

			decodeBits_aux(root->right, bits, i + 1,top,decoded);

		}
	}


}

//main decode function for user to call
void decodeBits(struct node* root, char fileName[]){
	char decoded[MAX_SIZE]="";
	char line[MAX_SIZE]="";

	FILE* fptr;
	fptr= fopen(fileName, "r"); //open encoded file for reading

	FILE* fptr2;
	fptr2= fopen("decoded.txt", "w"); //create decoded.txt file to write to

	fgets(line, sizeof(line),fptr);
	decodeBits_aux(root,line,0,root,decoded);
	fprintf(fptr2,"%s\n",decoded); //prints decoded output to decoded.txt
	fclose(fptr2);
}


//returns the frequency of a specific character in a file
int countChar (char fileName[], char key) {
	int count = 0;
	FILE* fptr;
	fptr= fopen(fileName, "r");
	char line[MAX_SIZE];

	if (fptr == NULL) {
		printf("Error Opening File");
	} else {

		while (fgets(line, sizeof(line),fptr)){
			for (int i = 0; i < strlen(line); i++){
				if (line[i] == key){
				count += 1;
				}
			}
		}
	}
	return count;


}

//reads from file and fills queue with nodes and their frequencies
void fillQueue(char fileName[], QUEUE* queue){
	FILE* fptr;
	fptr= fopen(fileName, "r");
	char line[MAX_SIZE];

	if (fptr == NULL) {
		printf("Error Opening File");
	} else {

		while (fgets(line, sizeof(line),fptr)){

			for (int i = 0; i < strlen(line); i++){
				printf("%c",line[i]);
				struct node *new = new_node(line[i], countChar(fileName,line[i]));
				enqueue(queue,new);

			}
		}
	}
}

//prints a queue node by node
void printQueue(QUEUE* qp){
	struct node* curr = qp->front;

	while (curr != NULL){
		printf("[%c: %d] ",curr->data,curr->freq);
		curr = curr->next;
	}
	printf("\n");

}

//builds a Huffman tree
QUEUE* createTree(QUEUE* qp){

	if (qp->front->next != NULL){
		BSTmergeNodes(qp);
		createTree(qp);
	}

	return qp;

}

//main function for testing
int main() {
	setbuf(stdout, NULL);
	QUEUE queue = {NULL,NULL};
	char fileName[100] = "short.txt"; //name of text file to compress

	printf("FILE:\n");
	fillQueue(fileName,&queue); //fills queue with characters and frequencies

	printf("\nQUEUE: \n");
	printQueue(&queue); //prints unsorted queue

	printf("\nQUEUE SORTED AND CLEANED: \n");
	mergeSort(&queue.front); //sorts queue
	clean_queue(&queue); //cleans queue
	printQueue(&queue); //prints sorted and cleaned queue
	printf("\n");

	printf("BUILDING TREE... \n");
	createTree(&queue); //creates tree of Huffman nodes

	printf("\nENCODING... \n\nCHARACTER FREQUENCY  BITS\n");
	printf("=========  ======   ====\n");
	encodeBits(queue.front,fileName); //encodes text file and write to file called encoded.txt
	decodeBits(queue.front,"encoded.txt"); //decodes bits and writes to file called decoded.txt

	return 0;
}








