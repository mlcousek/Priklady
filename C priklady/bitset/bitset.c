#include <stdlib.h>
#include <stdio.h>
#include "bitset.h"

void print_enter(){
    printf("\n");
}

int find_size (int size){
    int arr_size = 0;
    while(0 <= size){
        size = size - 32;
        arr_size++;
    }
    return arr_size;
}

Bitset* create_bitset(size_t size){
    Bitset* bitset1 = (Bitset*) malloc(sizeof(Bitset));
    if(bitset1){
        bitset1->size = size;
        int pom = find_size(size);
        bitset1->array = malloc (pom * sizeof(int));
        if(bitset1->array){
            for(int i = 0; i < pom; i++){
                bitset1->array[i] = 0;
            }
            return bitset1;
        }
    }
    printf(ERR);
    return NULL;
}

int dva_na_en(int n){
    int pom = 1;
    for(int i = n; i > 0; i--){
        pom = pom * 2;
    }
    return pom;
}

void set_insert(Bitset *bitset, int element){
    int pom = find_size(element);
    if(bitset->size < pom * 32){
        bitset->size = pom * 32;
        bitset->array = realloc (bitset->array, (pom * sizeof(int)));
    }
    bitset->array[pom-1] = bitset->array[pom-1] | dva_na_en(element % 32);
}

Bitset* create_bitset_with_values(size_t size, const int *values, size_t array_size){
    Bitset *bitset1 = create_bitset(size);
    for(int i = 0; i < array_size; i++){
        set_insert(bitset1, values[i]);
    }
    return bitset1;
}

Bitset* create_bitset_with_range(size_t size, int upto){
    int upto_pom = upto - 1;
    Bitset *bitset1 = create_bitset(size);
    for(int i = 0; i <= upto_pom; i++){
        bitset1->array[find_size(i) - 1] = bitset1->array[find_size(i) - 1] | dva_na_en(i % 32);
    }
    return bitset1;
}

void set_remove(Bitset *bitset, int element){
    int help = element % 32; 
    int pom = find_size(element);
    bitset->array[pom-1] = bitset->array[pom-1] ^ dva_na_en(help);
}

int contains(Bitset *Bitset, int element){
    int help = find_size(element) -1;
    int pom = Bitset->array[help];
    pom = pom & dva_na_en(element % 32);
    if(pom == 0){
        return 0;
    } else{
        return 1;
    }
}

int size_h(int size){
   if(size % 32 == 0){
        return size/32;
    } else{
        return size/32 + 1;
    } 
}

int size_fun(int size1, int size2){
    if(size1 >= size2){
        return size_h(size1);
    } else{
        return size_h(size2);
    }
}

void form(Bitset *left, Bitset *right, char op){
    if(left->size < right->size){
        left->size = right->size;
        left->array = realloc (left->array, (((left->size/32)+1) * sizeof(int)));
    }
    for(int i = 0; i <= (left->size/32)+1; i++){
        if(op == '&'){
            left->array[i] = left->array[i] & right->array[i];
        } else if (op == '|'){
            left->array[i] = left->array[i] | right->array[i];
        } else{
            printf(ERR1);
        }
    }   
}

void form_intersection(Bitset *left, Bitset *right){
    form(left, right, '&');
}

int size_fun_hh(Bitset *left, Bitset *right, char op){
    int size_help;
    if(op == '>'){
        if(left->size > right->size){
            size_help = left->size;
        } else{
            size_help = right->size;
        }
        return size_help;
    } else if(op == '<'){
       if(left->size < right->size){
            size_help = left->size;
        } else{
            size_help = right->size;
        }
        return size_help; 
    } else {

    }
}

Bitset* get_larger_set(Bitset *left, Bitset *right){
    Bitset *bitset1 = create_bitset(size_fun_hh(left, right, '>'));  
    return bitset1;
}

Bitset* get_smaller_set(Bitset *left, Bitset *right){
    Bitset *bitset1 = create_bitset(size_fun_hh(left, right, '<'));  
    return bitset1;
}

Bitset* set(Bitset *left, Bitset *right, char op){
    Bitset *bitset1;
    if(op == '|'){
        bitset1 = get_larger_set(left, right);
    } else if(op == '&'){
        bitset1 = get_smaller_set(left, right);
    } else {
        printf(ERR1);
        return NULL;
    }
    int pom = size_h(bitset1->size);
    for(int i = 0; i <= pom - 1; i++){
        if(op == '&'){
            bitset1->array[i] = left->array[i] & right->array[i];
        } else if (op == '|'){            
            bitset1->array[i] = left->array[i] | right->array[i];
        } else{
            printf(ERR1);
        }
    }
    return bitset1;    
}

Bitset* set_intersection(Bitset *left, Bitset *right){
    return set(left, right, '&');
}
void form_union(Bitset *left, Bitset *right){
    form(left, right, '|');
}
Bitset* set_union(Bitset *left, Bitset *right){
    return set(left, right, '|');
}

Bitset* difference(Bitset *left, Bitset *right, char pom){
    int x = size_fun(left->size, right->size) * 32;
    if(pom == 's'){
        Bitset* bitset1 = create_bitset(left->size);
        for(int i = 0; i <= x; i++){
            if(contains(left, i) == 1 && contains(right, i)==0){
                set_insert(bitset1, i);
            }
        }
        return bitset1;
    } else if(pom == 'f'){
        for(int i = 0; i <= x; i++){
            if(contains(left, i) == 1 && contains(right, i) == 1){
                set_remove(left, i);
            }
        }   
    } else{
        printf(ERR1);
        return NULL;
    }
}

void form_difference(Bitset *left, Bitset *right){
    difference(left, right, 'f');
}

Bitset* set_difference(Bitset *left, Bitset *right){
    return difference(left, right, 's');
}

int is_subset(Bitset *left, Bitset *right){
    int pom = 1;
    int help = size_fun_hh(left, right, '>');
    for(int i = 0; i <= help; i++){
        if(contains(left, i)){
            if(!contains(right, i)){
                return 0;
            }
        }
    }
    return 1;
}

void print_bitset(Bitset *bitset){
    int pp = 0;
    int pom = size_h(bitset->size);
    for(int i = 0; i < pom; i++){
        for(int j = 0; j < 32; j++){
            int help = 1 << j;
            int pomm = help & bitset->array[i];
            if(pomm != 0){
                int k = (i*32)+j;
                printf("%d ", k);
                pp = 1;
            }
        }
    }
    if(pp == 1){
        print_enter();
    }
}

int save_bitsets_to_file(char *file, Bitset **bitsets, size_t bitsets_count){
    FILE* file1 = fopen(file, "w");
        int i = 0;
        int x = 0;
    if (file1){
        while(i != bitsets_count){
            x = 0;
            int pom = size_h(bitsets[i]->size);
            for(int q = 0; q <= pom; q++){
                for(int j = 0; j < 32; j++){
                    int help = 1 << j;
                    int pomm = help & bitsets[i]->array[q];
                    if(pomm != 0){
                        if(fprintf(file1, "%d ", (q*32)+j) < 0){
                            if (fclose(file1) == EOF) {
                                return 3;
                            }
                            return 2;
                        }
                        x = 1;
                    }
                }
            }
                if(x == 1){
                    if(fprintf(file1, "\n") < 0){
                        if (fclose(file1) == EOF) {
                            return 3;
                        }
                        return 2;
                    } 
                }
            i++;
        }
        if(i == bitsets_count){
            if (fclose(file1) == EOF) {
                return 3;
            }   
            return 0;
        }
        
     if (fclose(file1) == EOF) {
            return 3;
        }
    }
    else {
        return 1;
    }
}
