#include <stdio.h>
#include <math.h>

int porovnani = 0;
int posunuti = 0;

void printpole(int A[], int size) {
  for (int i = 0; i < size; ++i) {
    printf("%d  ", A[i]);
  }
  printf("\n");
}


int parent(int i){
    int x = (floor((i - 1)/ 2));
    return x;
}

int left (int i){
    int x = 2 * i + 1;
    return x;
}

int right (int i){
    int x = 2 * i + 2;
    return x;
}

void max_heapify(int a[], int index, int n){
int largest = index;
int l = left(index);
int r = right(index);
if (l < n && a[l] <= a[largest]){
    
    porovnani++;
}

if (l < n && a[l] > a[largest]){
    largest = l;
    porovnani++;
}
if (r < n && a[r] <= a[largest]){
    porovnani++;
}

if (r < n && a[r] > a[largest]){
    largest = r;
    porovnani++;
}
printf("largest je: %d\n", largest);
printf("index je: %d\n", index);

if (largest != index){
    int pom;
    pom = a[index];
    a[index] = a [largest];
    a[largest] = pom;
    posunuti++;
    max_heapify(a, largest, n);
}
}

void build_max_heap(int a[], int n){
for(int i = (floor(n/2)) - 1; i >= 0; i--){
    max_heapify(a, i, n);
}
}

void heap_sort (int a[], int n){
    build_max_heap(a, n);
    for(int i = n - 1; i > 0; i--){
        int pom;
        pom = a[0];
        a[0] = a[i];
        a[i] = pom;
        posunuti++; 

        max_heapify(a, 0, i);
       
    }
}







int main(){
int a[] = {1, 2, 3, 8, 9, 55, 0};
int n = sizeof(a) / sizeof(a[0]);
printf("puvodni pole:        ");
printpole(a, n);

heap_sort(a, n);

printf("nove setrizene pole: ");
printpole(a, n);

printf("porovnani je: %d\n", porovnani);
printf("n je: %d\n", n);
printf("posunuti je: %d\n", posunuti);


    return 0;
}