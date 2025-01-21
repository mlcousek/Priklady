#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include <stdbool.h>
#include <time.h>

#define ERROR 77777
#define MIN -1


////////////////////! TYPEDEF STRUCTS
typedef struct {	
	int* values;
	int size;
	int max_size;
} Binary_Heap;

typedef struct Binom_n{
	int key;	
	struct Binom_n* child; 
	struct Binom_n* sibling;
	struct Binom_n* parent;
	int degree;
} Binomial_Node;

typedef struct {		
	Binomial_Node *root;	
} Binomial_Heap;


////////////////////! HELP OPERATIONS 
// vrátí rodice
int parent(int i) {
    return (floor((i - 1)/ 2));
}

// return levého potomka
int left_child(int i) {
    return 2*i + 1;
}

// return pravého potomka
int right_child(int i) {
    return 2*i + 2;
}

// výměna
void swap(int *x, int *y) {
    int temp = *x;
    *x = *y;
    *y = temp;
}

////////////////////! BINARY HEAP

Binary_Heap* make_binary_Heap(int size) {
	Binary_Heap* heap = (Binary_Heap*)malloc(sizeof(Binary_Heap));
	if (heap) {			
		heap->values = (int*)malloc(size * sizeof(int));
		if (heap->values) {
			heap->max_size = size;
			heap->size = 0;			
			return heap;
		}
		free(heap);
	}
	printf("Problem with allocation!\n\n");
	return NULL;
}

void min_heapify(Binary_Heap* q, int i){
    //Nejvetsi prvek jsem dal do korene a ted ho posouvam na sve misto, tim ze probublava dolu
	int l = left_child(i);
	int r = right_child(i);
	int index_of_smallest;

	if ((l < q->size) && (q->values[l] < q->values[i])) { 
		index_of_smallest = l;
	}
	else {
		index_of_smallest = i;
	}

	if ((r < q->size) && (q->values[r] < q->values[index_of_smallest])) {
		index_of_smallest = r;
	}

	if (index_of_smallest != i) {
		swap(&q->values[index_of_smallest], &q->values[i]);
		min_heapify(q, index_of_smallest);
	}
}

int binary_remove_min(Binary_Heap* q){
	if (q->size < 1) {
		printf("The heap is already empty, cannot remove min\n");
		return ERROR;
	}
	int min = q->values[0];	
	q->values[0] = q->values[q->size - 1]; 
	q->size -= 1;
	min_heapify(q, 0);
	
	return min;	
}

void heap_key_decrease(Binary_Heap* q, int key) {
    //Prvek dam na konec a pak hledam jeho misto probublavanim nahoru, tak at kazdy prvek pod nim je vetsi
	int i = q->size - 1;
	q->values[i] = key; 
	int help;

	while ((i > 0) && (q->values[parent(i)] > q->values[i])){
		help = q->values[i];
		q->values[i] = q->values[parent(i)];
		q->values[parent(i)] = help;
		i = parent(i);
	}
}

void binary_insert(Binary_Heap* Heap, int key) {
    //vlozim klic na konec a probublava na sve misto
	if (Heap->size >= Heap->max_size) {
		int* new = realloc(Heap->values, 2 * Heap->max_size * sizeof(int));		
		if (new) {
            Heap->values = new;
        }
		Heap->max_size = 2 * Heap->max_size;
	} 

	Heap->size = Heap->size + 1;		
	heap_key_decrease(Heap, key);					
}

Binary_Heap* binary_union(Binary_Heap* heap1, Binary_Heap* heap2) 
{
	Binary_Heap* heap = make_binary_Heap(heap1->size + heap2->size);

	for (int i = 0; i < heap1->size; i++) {
		binary_insert(heap, heap1->values[i]);
	}

	for (int j = 0; j < heap2->size; j++) {
		binary_insert(heap, heap2->values[j]);
	}	

	return heap;
}

void print_binary_H(Binary_Heap* q) {
	for (int i = 0; i < q->size; i++) {
		printf("%d ", q->values[i]);
	}
	printf("\n");
}

void destroy_binary_heap(Binary_Heap* heap) {
	if (heap) {
		if (heap->values) {
			free(heap->values);
		}
		free(heap);
	}
}

////////////////////////////! BINOMIAL HEAP

Binomial_Heap* create_binomial_heap() {
	Binomial_Heap* heap = (Binomial_Heap*)malloc(sizeof(Binomial_Heap));
	if (heap) {
		heap->root = NULL;
		return heap;
	}
	printf("Problem with allocation!\n");
	return NULL;
}

Binomial_Node* create_binomial_node(int key) {
	Binomial_Node* node = (Binomial_Node*)malloc(sizeof(Binomial_Node));
	if (node) {
		node->key = key;
		node->degree = 0;
		node->sibling = NULL;
		node->child = NULL;
		node->parent = NULL;
		return node;
	}
	printf("Problem with allocation!\n");
	return NULL;
}

void binomial_linking(Binomial_Node* y, Binomial_Node* z) {
	y->parent = z;
	y->sibling = z->child;
	z->child = y;
	z->degree++;
}

Binomial_Node* binomial_merge(Binomial_Heap* heap1, Binomial_Heap* heap2) {
	if(!heap1 && !heap2) {
		return NULL;		
	}
	if(!heap2){	
		return heap1->root;
	}
	if(!heap1){	
		return heap2->root;
	}	
	if(heap1){
		if (!heap1->root) {
			return heap2->root;
		}
	}
	if(heap2){
		if (!heap2->root) {
			return heap1->root;
		}
	}
	Binomial_Node* head, *rest;
	Binomial_Node* heap1_node = heap1->root;
	Binomial_Node* heap2_node = heap2->root;

	if (heap1->root->degree < heap2->root->degree) {
		head = heap1->root;
		heap1_node = heap1_node->sibling;
	} else {
		head = heap2->root;
		heap2_node = heap2_node->sibling;
	}
	rest = head;
	while (heap1_node && heap2_node) {
		if (heap1_node->degree <= heap2_node->degree) {
			rest->sibling = heap1_node;
			heap1_node = heap1_node->sibling;
		} else {
			rest->sibling = heap2_node;
			heap2_node = heap2_node->sibling;
		}
		rest = rest->sibling;
	}

	if(heap1_node){
		rest->sibling = heap1_node;
	} else{
		rest->sibling = heap2_node;
	}

	return head;
}

void binomial_union(Binomial_Heap* heap1, Binomial_Heap* heap2) {
	if(!heap1 && !heap2) {
		return NULL;		
	}
	if(!heap2){	
		return;
	}
	if(!heap1){	
		return;
	}
	Binomial_Node* new_root = binomial_merge(heap1, heap2);
	heap1->root = NULL;
	heap2->root = NULL;
	if (!new_root) {
		printf("Problem with Binomial Merge!\n");
	}
	Binomial_Node* prev_x = NULL;
	Binomial_Node* x = new_root;
	Binomial_Node* next_x = x->sibling;
	while (next_x) {
		if ((x->degree != next_x->degree) || (next_x->sibling && next_x->sibling->degree == x->degree)) {
			prev_x = x;
			x = next_x;
		}
		else if (x->key >= next_x->key) {
			x->sibling = next_x->sibling;
			binomial_linking(next_x, x);
		}
		else {
			if (!prev_x) new_root = next_x;
			else prev_x->sibling = next_x;
			binomial_linking(x, next_x);
			x = next_x;
		}
		next_x = x->sibling;
	}
	heap1->root = new_root;
}

void binomial_insert(Binomial_Heap* heap, int key) {
	Binomial_Node* new_node = create_binomial_node(key);
	Binomial_Heap* new_heap = create_binomial_heap();
	new_heap->root = new_node;
	binomial_union(heap, new_heap);
	free(new_heap);
}

Binomial_Heap* binomial_reverse(Binomial_Node* root) {	
	Binomial_Node* child = root->child;
	Binomial_Node* actual_child = child;
	Binomial_Node* prev = NULL;
	Binomial_Node* next = NULL;	
	Binomial_Heap* heap = create_binomial_heap();
	free(root);
	if (actual_child) { 		
		while (actual_child)
		{
			actual_child->parent = NULL;
			next = actual_child->sibling; 
			actual_child->sibling = prev; 
			prev = actual_child;			
			actual_child = next;														
		}
		heap->root = prev;
		return heap;
	}
	return NULL;
}

int binomial_remove_min(Binomial_Heap* h) {

	if (!h->root) {
		return ERROR;
	}

	Binomial_Node* min = h->root;
	Binomial_Node* previous_min_node = NULL;
	Binomial_Node* help = h->root;
	
	while (help->sibling) {		
		if (help->sibling->key < min->key) {
			min = help->sibling;
			previous_min_node = help;
		}	
		help = help->sibling;
	}

	if (previous_min_node) {
		previous_min_node->sibling = min->sibling;		
	} else {
		h->root = min->sibling;
	}
	int key = min->key;
	binomial_union(h, binomial_reverse(min)); 
	return key;
}

void destroy_binomial_node(Binomial_Node* node) {
	if (node->child) {
		destroy_binomial_node(node->child);
	}
	if (node->sibling) {
		destroy_binomial_node(node->sibling);
	}
	free(node);
}

void destroy_binomial_heap(Binomial_Heap* heap) {
	if (heap) {
		if (heap->root) {
			destroy_binomial_node(heap->root);
		}
		free(heap);
	}
}

//////////////////////////! FIBONACCI

typedef struct Fib_Node {
	int key;
	struct Fib_Node* left;
	struct Fib_Node* right;
	struct Fib_Node* parent;
	struct Fib_Node* child;
	int degree;
	bool mark;
} Fibonacci_Node;

typedef struct {
	Fibonacci_Node* max;
	int n;
} Fibonacci_Heap;

Fibonacci_Node* fibonacci_create_node(int key) {
	Fibonacci_Node* node = (Fibonacci_Node*) malloc (sizeof(Fibonacci_Node));
	if (node) {
		node->key = key;
		node->left = node;
		node->right = node;
		node->parent = NULL;
		node->child = NULL;
		node->degree = 0;
		node->mark = false;
	}
	return node;
}

Fibonacci_Heap* fibonacci_create_heap() {
	Fibonacci_Heap* heap = (Fibonacci_Heap*) malloc (sizeof(Fibonacci_Heap));
	if (heap) {
		heap->max = NULL;
		heap->n = 0;

		return heap;
	}
	printf("Problem with allocation!\n");
	return NULL;
}

void fibonacci_remove_node(Fibonacci_Node* node) {
	if (node->left == node) {}
	if (node) {
		node->left->right = node->right;
		node->right->left = node->left;
	}
}

void fibonacci_new_insert(Fibonacci_Heap* heap, int h) {
	Fibonacci_Node* new_node = fibonacci_create_node(h);
	if (heap->max) {
		new_node->left = heap->max;
		new_node->right = heap->max->right;
		heap->max->right = new_node;
		new_node->right->left = new_node;
		if (heap->max->key < h)
			heap->max = new_node;
	}
	else {
		heap->max = new_node;
	}
	heap->n++;
}

void fibonacci_insert_node(Fibonacci_Heap* heap, Fibonacci_Node* node) {
	if (heap->max == NULL) {
		heap->max = node;
	}
	else {
		node->left = heap->max;
		node->right = heap->max->right;
		heap->max->right = node;
		node->right->left = node;
		if (node->key > heap->max->key) {
			heap->max = node;
		}
	}
}

Fibonacci_Node* fib_max(Fibonacci_Heap* heap) {
	return heap->max;
}

void fibonacci_union(Fibonacci_Heap* heap1, Fibonacci_Heap* heap2) {
	if (!heap1->max){
		heap1->max = heap2->max;
	} else if (heap2->max) {
		heap1->max->right->left = heap2->max->left;
		heap2->max->left->right = heap1->max->right;
		heap1->max->right = heap2->max;
		heap2->max->left = heap1->max;
		if (heap2->max->key > heap1->max->key) heap1->max = heap2->max;
	}
	heap1->n += heap2->n;
}

void fibonacci_linking(Fibonacci_Node* node1, Fibonacci_Node* node2) {
	fibonacci_remove_node(node2);
	node2->parent = node1;
	if (!node1->child) {
		node1->child = node2;
		node2->left = node2;
		node2->right = node2;
	} else {
		node2->left = node1->child;
		node2->right = node1->child->right;
		node1->child->right = node2;
		node2->right->left = node2;
	}
	node2->mark = false;
	node1->degree++;
}

//masakr
void fib_consolidate(Fibonacci_Heap* heap) {
	int degree = heap->n + 1;
	Fibonacci_Node** arr = malloc(degree * sizeof(Fibonacci_Node*));
	for (int i = 0; i < degree; i++) {
		arr[i] = NULL;
	}
	Fibonacci_Node* x = heap->max;
	int help = 1;
	while (x->right != heap->max) {
		help++;
		x = x->right;
	}
	Fibonacci_Node** arr2 = malloc(help * sizeof(Fibonacci_Node*));
	x = heap->max;
	for (int i = 0; i < help; i++) {
		arr2[i] = x;
		x = x->right;
	}
	x = heap->max;
	for (int i = 0; i < help; i++) {
		x = arr2[i];
		int deg = x->degree;
		while (arr[deg] != NULL && arr[deg] != x) {
			Fibonacci_Node* y = arr[deg];
			if (x->key < y->key) {
				Fibonacci_Node* help_node = x;
				x = y;
				y = help_node;
			}
			if (y == heap->max) {
				heap->max = x;
			}
			fibonacci_linking(x, y);
			if (x->right == x) heap->max = x;
			arr[deg] = NULL;
			deg++;
		}
		arr[deg] = x;
	}
	heap->max = NULL;
	for (int i = 0; i < degree; i++) {
		if (arr[i] != NULL) {
			arr[i]->left = arr[i];
			arr[i]->right = arr[i];
			if (heap->max != NULL) {
				heap->max->left->right = arr[i];
				arr[i]->right = heap->max;
				arr[i]->left = heap->max->left;
				heap->max->left = arr[i];
				if (arr[i]->key > heap->max->key) {
					heap->max = arr[i];
				}
			} else {
				heap->max = arr[i];
			} 
		}
	}
}

int fibonacci_remove_max(Fibonacci_Heap* heap) {
	Fibonacci_Node* max_node = heap->max;
	if (!max_node) {
		return NULL;
	}
	Fibonacci_Node* x = max_node->child;
	for (int i = 0; i < max_node->degree; i++) {
		Fibonacci_Node* ch = x->right;
		fibonacci_remove_node(x);
		x->parent = NULL;
		fibonacci_insert_node(heap, x);
		x = ch;
	}
	fibonacci_remove_node(max_node);
	heap->n--;
	heap->max = heap->n > 0 ? max_node->right : NULL;
	if (heap->max) {
		fib_consolidate(heap);
	}
	int max_key = max_node->key;
	free(max_node);
	return max_key;
}

void destroy_fibonacci_heap(Fibonacci_Heap* heap) {
	while (heap->max) {
		fibonacci_remove_max(heap);
	}
	free(heap);
}

//////////////////////////////////! TESTING
//urcuje kolikrat budeme vkladat prvky
#define INSERT_LOOPS 200

//urcuje kolik prvku vkladame do haldy v kazde iteraci a nasledne extrahujeme
#define INSERT 200

//urcuje kolik prvku obsahuje 1 fronta pri sjednocovani 2 front
#define UNION 10000

//urcuje kolikrat se ma provadet mereni
#define LOOPS 5


void fill_array(int arr[], int size) {
	for (int i = 0; i < size; i++) {
		arr[i] = rand() % 10000;
	}
}

void insertion_t(int arr[], void* heap, void (*insert_fun)(void*, int), double* insert_time, int shift) {
	clock_t begin = clock();
	for (int i = 0; i < INSERT; i++) {
		insert_fun(heap, arr[shift + i]);
	}
	*insert_time += (double)(clock() - begin) / CLOCKS_PER_SEC;
}

void delete_t(void* heap, int (*delete_fun)(void*), double* delete_time) {
	clock_t begin = clock();
	for (int i = 0; i < INSERT; i++) {
		delete_fun(heap);
	}
	*delete_time += (double)(clock() - begin) / CLOCKS_PER_SEC;
}

void union_t(void* h1, void* h2, void (*union_fun)(void*, void*), double* union_time) {
	clock_t begin = clock();
	union_fun(h1, h2);
	*union_time += (double)(clock() - begin) / CLOCKS_PER_SEC;
}

void binary_heap(int arr1[], double* insert_time, double* delete_time) {
	Binary_Heap* heap = make_binary_Heap(1);
	for (int i = 0; i < INSERT_LOOPS; i++) {
		insertion_t(arr1, heap, binary_insert, insert_time, i);
		delete_t(heap, binary_remove_min, delete_time);
	}
	destroy_binary_heap(heap);
}

void binomial_heap(int arr1[], double* insert_time, double* delete_time) {
	Binomial_Heap* heap = create_binomial_heap();
	for (int i = 0; i < INSERT_LOOPS; i++) {
		insertion_t(arr1, heap, binomial_insert, insert_time, i);
		delete_t(heap, binomial_remove_min, delete_time);
	}
	destroy_binomial_heap(heap);
}

void fibonacci_heap(int arr1[], double* insert_time, double* delete_time) {
	Fibonacci_Heap* heap = fibonacci_create_heap();
	for (int i = 0; i < INSERT_LOOPS; i++) {
		insertion_t(arr1, heap, fibonacci_new_insert, insert_time, i);
		delete_t(heap, fibonacci_remove_max, delete_time);
	}
	destroy_fibonacci_heap(heap);
}

void binary_union_t(int arr1[], int arr2[], double* union_time) {
	Binary_Heap* heap1 = make_binary_Heap(1);
	for (int i = 0; i < UNION; i++) {
		binary_insert(heap1, arr1[i]);
	}
	Binary_Heap* heap2 = make_binary_Heap(1);
	for (int i = 0; i < UNION; i++) {
		binary_insert(heap2, arr2[i]);
	}
	union_t(heap1, heap2, binary_union, union_time);
	destroy_binary_heap(heap1);
	destroy_binary_heap(heap2);
}

void binomial_union_t(int arr1[], int arr2[], double* union_time) {
	Binomial_Heap* heap1 = create_binomial_heap();
	for (int i = 0; i < UNION; i++) {
		binomial_insert(heap1, arr1[i]);
	}
	Binary_Heap* heap2 = create_binomial_heap();
	for (int i = 0; i < UNION; i++) {
		binomial_insert(heap2, arr2[i]);
	}
	union_t(heap1, heap2, binomial_union, union_time);
	destroy_binomial_heap(heap1);
	destroy_binomial_heap(heap2);
}

void fibonacci_union_t(int arr1[], int arr2[], double* union_time) {
	Fibonacci_Heap* heap1 = fibonacci_create_heap();
	for (int i = 0; i < UNION; i++) {
		fibonacci_new_insert(heap1, arr1[i]);
	}
	Fibonacci_Heap* heap2 = fibonacci_create_heap();
	for (int i = 0; i < UNION; i++) {
		fibonacci_new_insert(heap2, arr2[i]);
	}
	union_t(heap1, heap2, fibonacci_union, union_time);
	destroy_fibonacci_heap(heap1);
}

void heaps_test() {
	time_t t;
	srand((unsigned)time(&t));
	double binary_insert_time = 0;
	double binary_delete_time = 0;
	double binary_union_time = 0;

	double binomial_insert_time = 0;
	double binomial_delete_time = 0;
	double binomial_union_time = 0;

	double fib_insert_time = 0;
	double fib_delete_time = 0;
	double fib_union_time = 0;

	int arr[INSERT * INSERT_LOOPS];
	for (int i = 0; i < LOOPS; i++) {
		fill_array(arr, INSERT * INSERT_LOOPS);
		binary_heap(arr, &binary_insert_time, &binary_delete_time);
		binomial_heap(arr, &binomial_insert_time, &binomial_delete_time);
		fibonacci_heap(arr, &fib_insert_time, &fib_delete_time);
	}

	int arr1[UNION];
	int arr2[UNION];
	
	for (int i = 0; i < LOOPS; i++) {
		fill_array(arr1, UNION);
		fill_array(arr2, UNION);
		binary_union_t(arr1, arr2, &binary_union_time);
		binomial_union_t(arr1, arr2, &binomial_union_time);
		fibonacci_union_t(arr1, arr2, &fib_union_time);
	}


	printf("\nHeap:\t\t\t      Insert[s]\tDelete[s]\tUnion[s]");
	printf("\n------------------------------------------------------------------");
	printf("\nBinary heap:\t\t%f\t%f\t%f", binary_insert_time / LOOPS, binary_delete_time / LOOPS, binary_union_time / LOOPS);
	printf("\nBinomial heap:\t\t%f\t%f\t%f", binomial_insert_time / LOOPS, binomial_delete_time / LOOPS, binomial_union_time / LOOPS);
	printf("\nFibonacci heap:\t\t%f\t%f\t%f", fib_insert_time / LOOPS, fib_delete_time / LOOPS, fib_union_time / LOOPS);
}


////////////////////////////////////////////////////////////////////////!




//////////////////////////! MAIN
 
int main() {
/*
   printf("Hello, World! %f\n", floor(5.5));
    Binary_Heap* test = make_binary_Heap(3);
    binary_insert(test, 5);
    binary_insert(test, 3);
    binary_insert(test, 15);
    binary_insert(test, 2);
    print_binary_H(test);
    binary_insert(test, 1);
    print_binary_H(test);

*/

	heaps_test();

   return 0;
}
