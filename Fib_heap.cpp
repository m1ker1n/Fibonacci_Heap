#include "Fib_heap.h"
#include <math.h>

void Consolidate(Heap_t* h);
void Fib_Heap_Link(Heap_t* h, Node_t* y, Node_t* x);

Heap_t* Init_Heap() {
	Heap_t* h = (Heap_t*)malloc(sizeof(Heap_t));
	h->min = NULL;
	h->size = 0;
	return h;
}

void Fib_Heap_Insert(Heap_t* h, int key) {
	Node_t* node = (Node_t*)malloc(sizeof(Node_t));
	node->key = key;
	node->degree = 0;
	node->child = 0;
	node->left = node;
	node->right = node;
	node->parent = NULL;
	node->mark = FALSE;

	if (h->min == NULL) {
		h->min = node;
	}
	else {
		//add from the left side
		Node_t* prevLeft = h->min->left;
		node->left = prevLeft;
		node->right = h->min;
		prevLeft->right = node;
		h->min->left = node;

		//check if node is a new min
		if (node->key < h->min->key) {
			h->min = node;
		}
	}
	h->size++;
}

Node_t* Fib_Heap_Extract_Min(Heap_t* h) {
	//check if heap is empty
	if (h->min == NULL) return h->min;
	
	Node_t* temp = h->min;
	Node_t* ptr = temp;
	Node_t* x = NULL;


	//for each child x of temp (that is min of heap)
	//	add x to the root list of h from the left side
	if (temp->child != NULL) {
		x = temp->child;
		do {
			ptr = x->right;
			Node_t* prevL = h->min->left;
			prevL->right = x;
			x->right = h->min;
			x->left = prevL;
			h->min->left = x;
			x->parent = NULL;
			
			x = ptr;
		} while (ptr != temp->child);
	}

	//delete temp from root list
	temp->left->right = temp->right;
	temp->right->left = temp->left;

	

	if (temp == temp->right) { //only 1 el in heap
		h->min = NULL;
	}
	else {
		//make temp->right min of heap temporary
		h->min = temp->right;
		Consolidate(h);
	}
	h->size--;
	return temp;
}

void Consolidate(Heap_t* h) {
	//array init
	int arr_size = (int)log2(h->size) + 1;
	Node_t** A = (Node_t**)malloc(arr_size * sizeof(Node_t*));
	if (!A) return;
	for (int i = 0; i < arr_size; i++) {
		A[i] = NULL;
	}
	
	Node_t* x = h->min;
	Node_t* y; 
	Node_t* z;
	int d;

	do {
		d = x->degree;
		while (A[d] != NULL) {
			y = A[d];
			if (x->key > y->key) {
				Node_t* temp = x;
				x = y;
				y = temp;
			}
			if (y == h->min) {
				h->min = x;
			}
			Fib_Heap_Link(h, y, x);
			if (y->right == x) {
				h->min = x;
			}
			A[d] = NULL;
			d++;
		}
		A[d] = x;
		x = x->right;
	} while (x != h->min);

	h->min = NULL;
	for (int i = 0;i < arr_size;i++) {
		if (A[i] != NULL) {
			A[i]->left = A[i];
			A[i]->right = A[i];
			if (h->min == NULL) {
				h->min = A[i];
			}
			else {
				h->min->left->right = A[i];
				A[i]->right = h->min;
				A[i]->left = h->min->left;
				h->min->left = A[i];
				if (A[i]->key < h->min->key) {
					h->min = A[i];
				}
			}

			if (h->min == NULL) {
				h->min = A[i];
			}
			else if (A[i]->key < h->min->key) {
				h->min = A[i];
			}
		}
	}
}

void Fib_Heap_Link(Heap_t* h, Node_t* y, Node_t* x) {
	//remove y from the root list of H
	y->right->left = y->left;
	y->left->right = y->right;
	
	if (x == x->right) {
		h->min = x;
	}
	
	//make y a child of x, incrementing degree(x)
	y->left = y;
	y->right = y;
	y->parent = x;

	if (x->child == NULL) {
		x->child = y;
	}
	
	y->right = x->child;
	y->left = x->child->left;
	x->child->left->right = y;
	x->child->left = y;

	if (y->key < x->child->key) {
		x->child = y;
	}

	x->degree++;
	//y->mark=false;
	y->mark = FALSE;
}


//for tests
int Fib_Heap_Extract_Min_Key(Heap_t* h) {
	Node_t* min = Fib_Heap_Extract_Min(h);
	if (min != NULL) {
		int res = min->key;
		printf("\n\n");
		printf("Extracted min key = %d", res);
		printf("\n\n");
		return res;
	}
	else {
		printf("\n\n");
		printf("Min = NULL");
		printf("\n\n");
		return -1;
	}
}

int Display_Root_List(Heap_t* h) {
	printf("\n\n");
	if (!h) {
		printf("No heap");
		printf("\n\n");
		return -1;
	}

	Node_t* temp = h->min;
	if (!temp) {
		printf("Empty heap");
	}
	else {
		do {
			printf("%d ", temp->key);
			temp = temp->right;
		} while (temp != h->min);
	}
	printf("\n\n");

	return h->size;
}