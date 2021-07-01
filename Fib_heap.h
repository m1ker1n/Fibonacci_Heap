#pragma once
#include <stdlib.h>
#include <stdio.h>

typedef enum boolean {
	FALSE,
	TRUE
}boolean;

typedef struct Node_t {
	int key;
	struct Node_t* parent;
	struct Node_t* child;
	struct Node_t* left; //left&&right for circular doubly linked list
	struct Node_t* right;
	int degree; //amount of children
	boolean mark; //if its child was deleted because of changing key
} Node_t;

typedef struct Heap_t {
	Node_t* min; 
	int size; //amount of elements in root-list
} Heap_t;

Heap_t* Init_Heap();
void Fib_Heap_Insert(Heap_t* h, int key);
Node_t* Fib_Heap_Extract_Min(Heap_t* h);

//for tests
int Fib_Heap_Extract_Min_Key(Heap_t* h);
int Display_Root_List(Heap_t* h);