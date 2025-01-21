#include <math.h>


#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define VEL 10  
#define VEL1 100 
#define VEL2 1000  
#define VEL3 10000 
int porovnani = 0;
int posunuti = 0; 



//nahodne naplni pole nachystane pro "velikost" prvku hodnotami 0-99
void napln_pole(int pole[], int velikost){
    time_t t;
    srand((unsigned) time(&t));
    for (int i = 0; i < velikost; i++){
      pole[i] = rand() % 1001;  //% 100 zajistuje rozsah 0-99. pro rozsah 0-1000 pouzijte % 1001
    }
}


//vypise pole obshaujici "velikost" prvku
void vypis_pole(int pole[], int velikost){
    for (int i  =  0; i < velikost; i++){
        printf("%d, ", pole[i]);
    }
}
//insertion sort
void insertion_sort (int pole[], int velikost){

//int porovnani = 0;
//int posunuti = 0;
int t = 0;
int i = 0;
int k = 0;



for(int j = 1; j < velikost; j++){
    t = pole[j];
    i = j - 1;
    
   if(pole[i]< t && i >= 0){
       porovnani++;
   }
    while (i >= 0 && pole[i] > t){
        //printf("%d\n", i);
        porovnani++;
        pole[i+1] = pole[i];
        posunuti++;
        i--;
        if(pole[i]<t && i>=0){
            porovnani++;
        }
    }
    pole[i+1] = t;
     
}
//printf("porovnani: %d\n", porovnani);
//printf("posunuti: %d\n", posunuti);



}
//partition-qs
int partition(int A[], int p, int r){
int x, i, pom, pomm;
x = A[r];
i = (p - 1);
for(int j = p; j < r; j++){
    if(A[j] >x){
        porovnani++;
    }
    if(A[j] <= x){
        porovnani++;
        i = i + 1;
        pom = A[j];
        A[j] = A[i];
        A[i] =  pom;
        posunuti++;
    }
}

pomm = A[r];
A[r] = A[i+1];
A[i + 1] = pomm;
posunuti++;

return i+1;    
}
//quicksort
void quicksort(int A[], int p, int r){

    if(p < r){
       int q = partition(A, p, r);
        quicksort(A, p, q-1);
        quicksort(A, q+1, r);
    }
}
//parent-hs
int parent(int i){
    int x = (floor((i - 1)/ 2));
    return x;
}
//left-hs
int left (int i){
    int x = 2 * i + 1;
    return x;
}
//right-hs
int right (int i){
    int x = 2 * i + 2;
    return x;
}
//max heapify-hs
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


if (largest != index){
    int pom;
    pom = a[index];
    a[index] = a [largest];
    a[largest] = pom;
    posunuti++;
    max_heapify(a, largest, n);
}
}
//build max heap-hs
void build_max_heap(int a[], int n){
for(int i = (floor(n/2)) - 1; i >= 0; i--){
    max_heapify(a, i, n);
}
}
//heap sort
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

int main(void){
    //vytvorime, naplnime a vypiseme pole
    int ipole[VEL];
    int ipole1[VEL1];
    int ipole2[VEL2];
    int ipole3[VEL3];

    napln_pole(ipole, VEL);
    napln_pole(ipole1, VEL1);
    napln_pole(ipole2, VEL2);
    napln_pole(ipole3, VEL3);

    //vypis_pole(ipole, VEL);


    insertion_sort(ipole, VEL);
    int i_por =  porovnani;
    porovnani = 0;
    int i_pos = posunuti;
    posunuti = 0;
    insertion_sort(ipole1, VEL1);
    int i_por1 = porovnani;
    porovnani = 0;
    int i_pos1 = posunuti;
    posunuti = 0;
    insertion_sort(ipole2, VEL2);
    int i_por2 = porovnani;
    porovnani = 0;
    int i_pos2 = posunuti;
    posunuti = 0;
    insertion_sort(ipole3, VEL3);
    int i_por3 = porovnani;
    porovnani = 0;
    int i_pos3 = posunuti;
    posunuti = 0;



    //printf("%d\n", i_pos);
   // printf("%d\n", i_por);
   // printf("%d\n", posunuti);
   // printf("%d\n", i_por);
   // printf("%d\n", i_por1);
   // printf("%d\n", i_por2);
   // printf("%d\n", i_por3);

    int qpole[VEL];
    int qpole1[VEL1];
    int qpole2[VEL2];
    int qpole3[VEL3];

    napln_pole(qpole, VEL);
    napln_pole(qpole1, VEL1);
    napln_pole(qpole2, VEL2);
    napln_pole(qpole3, VEL3);

    quicksort(qpole, 0, VEL - 1);
    int q_por = porovnani;
    porovnani = 0;
    int q_pos = posunuti;
    posunuti = 0;
    quicksort(qpole1, 0, VEL1 - 1);
    int q_por1 = porovnani;
    porovnani = 0;
    int q_pos1 = posunuti;
    posunuti = 0;
    quicksort(qpole2, 0, VEL2 - 1);
    int q_por2 = porovnani;
    porovnani = 0;
    int q_pos2 = posunuti;
    posunuti = 0;
    quicksort(qpole3, 0, VEL3 - 1);
    int q_por3 = porovnani;
    porovnani = 0;
    int q_pos3 = posunuti;
    posunuti = 0;
   


    int hpole[VEL];
    int hpole1[VEL1];
    int hpole2[VEL2];
    int hpole3[VEL3];

    napln_pole(hpole, VEL);
    napln_pole(hpole1, VEL1);
    napln_pole(hpole2, VEL2);
    napln_pole(hpole3, VEL3);

    heap_sort(hpole, VEL);
    int h_por = porovnani;
    porovnani = 0;
    int h_pos = posunuti;
    posunuti = 0;
    heap_sort(hpole1, VEL1);
    int h_por1 = porovnani;
    porovnani = 0;
    int h_pos1 = posunuti;
    posunuti = 0;
    heap_sort(hpole2, VEL2);
    int h_por2 = porovnani;
    porovnani = 0;
    int h_pos2 = posunuti;
    posunuti = 0;
    heap_sort(hpole3, VEL3);
    int h_por3 = porovnani;
    porovnani = 0;
    int h_pos3 = posunuti;
    posunuti = 0;

    printf("\n");

    printf("Pocet porovnani:      10          100          1000          10000\n");
    printf("Insertion Sort:       %d          %d         %d        %d\n", i_por, i_por1, i_por2, i_por3);
    printf("Quick Sort:           %d          %d          %d         %d\n", q_por, q_por1, q_por2, q_por3);
    printf("Heap Sort:            %d          %d         %d         %d\n", h_por, h_por1, h_por2, h_por3);



    printf("\n");
    printf("Pocet posunuti:       10          100          1000          10000\n");
    printf("Insertion Sort:       %d          %d         %d        %d\n", i_pos, i_pos1, i_pos2, i_pos3);
    printf("Quick Sort:           %d          %d          %d          %d\n", q_pos, q_pos1, q_pos2, q_pos3);
    printf("Heap Sort:            %d          %d          %d          %d\n", h_pos, h_pos1, h_pos2, h_pos3);




//vypis_pole(ipole, VEL);


    return 0;
}