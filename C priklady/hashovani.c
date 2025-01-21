//! *** VARDY`S on FIRE   ***//

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <stdbool.h>

#define QUANTITY 10
#define MAX_STRING_SIZE 256
#define ERROR "Error in alocation\n"
typedef int (*HASH)(char*);
typedef int (*PROBE)(int, int);

typedef struct Linked_list{
    struct Linked_list *prev;
    struct Linked_list *next;
    char *data;
}Linked_list;

typedef struct{
    Linked_list *first_element;
}List;


void print_enter(){
    printf("\n");
}

int linked_list_add(List* list, char* value) {
    Linked_list* elem = (Linked_list*)malloc(sizeof(Linked_list));
    if(elem){
        elem->next = list->first_element;
        elem->data = (char*) malloc(15 * sizeof(char));
        elem->data = value;
        list->first_element = elem;
        return 1;
    }
    return 0;
}

int remove_first(List* list) {
    Linked_list* elem = list->first_element;
    if(elem){
        list->first_element = list->first_element->next;
        free(elem);
        return 1;
    } else{
        return 0;
    } 
}

int linked_list_delete(List* list, char value[]){
    Linked_list* elem = list->first_element;
    if(elem){
        int a = strcmp(elem->data, value);
        if(a == 0){
            return remove_first(list);
        }
        Linked_list *elem1 = list->first_element;
        while(elem1->next != NULL){
                if(elem1->next->data == value){
                    elem1->next = elem1->next->next;
                    free(elem);
                    return 1;
                } else{
                    elem1 = elem1->next;
                }
            }
    }
    return 0;
}

int linked_list_search(List* list, char* value){
    Linked_list* elem = list->first_element;
    while(elem != NULL){
        if(elem->data){
        int a = strcmp(elem->data, value);
        if (a == 0){
            return 1;
        }
        elem = elem->next;
        return 0;
        }
    }
    return 0;
}

int hash_f(char *data) {
    size_t length = strnlen (data, MAX_STRING_SIZE);
    int value = 0;
    for (int i=0; i < length; i++){
        value += data [i];
        value= (value * data [i]) % QUANTITY;
    }
    return value;
}

int l_hash(int key, int index) {
    return ((key % QUANTITY) + index) % QUANTITY;
}

int my_pow(int a, int b){
    int pom = 1;
    for(int i = b; i > 0; i--){
        pom = pom * a;
    }
    return pom;
}

int q_hash(int key, int index) {
    int c1 = 1;
    int c2 = 1;
    int pom = my_pow(index, 2);
    return ((key % QUANTITY) + (c1*index) + (c2*pom)) % QUANTITY;
}


typedef struct chaining_table{
    int size;
    List **data;
    HASH function;
} chaining_table;

typedef struct oa_table{
    int size;
    char **data;
    HASH hash_function;
    PROBE probe_function;
    bool *deleted;
} oa_table;



//? kolize retezenim
chaining_table* create_chaining_table(int size, int (*hash)(char*)){    
    chaining_table* hasht = malloc(sizeof(chaining_table));
    if(!hasht){
        printf(ERROR);
        return NULL;
    }
    hasht->data = malloc(size * sizeof(List*));
    if(hasht->data == NULL){
		free(hasht->data);
        printf(ERROR); 
		return NULL;
	}
    hasht->size = size;
    for(int i = 0; i < size; i++){
		hasht->data[i] = (List*) malloc(sizeof(List));
        if(!hasht->data[i]){
            printf(ERROR);
            return NULL;
        }
        hasht->data[i]->first_element = NULL;
    }
    hasht->function = hash;
	return hasht;
}

int add_ct(unsigned char* data, chaining_table* table){
    int i = table->function(data);
    return linked_list_add(table->data[i], data);
}

int remove_ct(char* data, chaining_table* table){
    int i = table->function(data);
    return linked_list_delete(table->data[i], data);
}

int contains_ct(char* data, chaining_table* table){
    int i = table->function(data);
    return linked_list_search(table->data[i], data);
}

//? kolize otevrenym adresovanim
oa_table* create_oa_table(int size, int (*hash)(char*), int (*probe)(int, int)){
    oa_table* table = (oa_table*) malloc(sizeof(oa_table));
    if(!table){
        printf(ERROR);
        return NULL;
    }
    table->size = size;
    table->data = malloc(size * sizeof(char*));
    bool *delete_array = calloc(size, sizeof(bool));
    if(!table->data || !delete_array) {
        printf(ERROR);
        return NULL;
    }
    for(int i = 0; i < table->size; i++){
        table->data[i] = 0;
        delete_array[i] = true;
    }
    table->hash_function = hash;
    table->probe_function = probe;
    table->deleted = delete_array;
    return table;
}

int add_oat(char* data, oa_table* table) {
    int pom = hash_f(data);
    for(int i = 0; i < QUANTITY; i++){
        int in = table->probe_function(pom, i);
        if(table->data[in] == NULL){
            table->data[in] = data;
            table->deleted[in] = false;
            return 1;
        }
    }
    return 0;
}

int remove_oat(char* data, oa_table* table) {
    int pom = hash_f(data);
    for(int i = 0; i < QUANTITY; i++){
        int in = table->probe_function(pom, i);
        if(table->data[in] != NULL){
            int pomm = strcmp(table->data[in], data);
            if(pomm == 0){
                table->data[in] = NULL;
                table->deleted[in] = true;
                return 1;
            }
        }
    }
    return 0;
}

int contains_oat(char* data, oa_table* table){
    int pom = hash_f(data);    
    for(int i = 0; i < table->size; i++){
        int in = table->probe_function(pom, i);
        if(table->data[in] == data && table->deleted[in] == false){
            return 1;
        }
        if(table->data[in] == NULL){
        return 0;
        }
    }
    return 0;
}


int main(){

    chaining_table* table = create_chaining_table(QUANTITY, hash_f);
    printf("HASHOVACI TABULKY NAD RETEZCI S RESENIM KOLIZI RETEZENIM\n");
    printf("Pridani slova Messi: %d\n", add_ct("Messsi", table));
    printf("Pridani slova Ronaldo: %d\n", add_ct("Ronaldo", table));
    printf("Pridani slova Vardy: %d\n", add_ct("Vardy", table));
    printf("Pridani slova Lewandovski: %d\n", add_ct("Lewandovski", table));
    printf("Pridani slova Haaland: %d\n", add_ct("Haaland", table));
    printf("Pridani slova Werner: %d\n", add_ct("Wernerr", table));
    printf("Pridani slova Pedri: %d\n", add_ct("Pedri", table));
    printf("Pridani slova Mbappe: %d\n", add_ct("Mbappe", table));
    printf("Pridani slova Nico: %d\n", add_ct("Nico", table));
    printf("Hledani slova Nico: %d\n",  contains_ct("Nico", table));
    printf("Mazani slova Nico: %d\n", remove_ct("Nico", table));
    printf("Hledani slova Nico: %d\n",  contains_ct("Nico", table));
    printf("Mazani slova Ronaldo: %d\n", remove_ct("Ronaldo", table));
    printf("Mazani slova Pedri: %d\n", remove_ct("Pedri", table));
    printf("Hledani slova Vardy: %d\n",  contains_ct("Vardy", table));
    printf("Hledani slova Neymar: %d\n",  contains_ct("Neymar", table));
    printf("Hledani slova Haaland: %d\n",  contains_ct("Haaland", table));
    printf("Hledani slova Werner: %d\n",  contains_ct("Wernerr", table));
    printf("Hledani slova Ronaldo: %d\n",  contains_ct("Ronaldo", table));
    
    print_enter();
    print_enter();

    printf("HASHOVACI TABULKY NAD RETEZCI S RESENIM KOLIZI OTEVRENYM ADRESOVANIM (LINEARNI FUNKCE)\n");
    oa_table* l_table = create_oa_table(QUANTITY, hash_f, l_hash);
    printf("Pridani slova Messi: %d\n", add_oat("Messi", l_table));
    printf("Pridani slova Ronaldo: %d\n", add_oat("Ronaldo", l_table));
    printf("Pridani slova Lewandovski: %d\n", add_oat("Lewandovski", l_table));
    printf("Pridani slova Haaland: %d\n", add_oat("Haaland", l_table));
    printf("Pridani slova Werner: %d\n", add_oat("Werner", l_table));
    printf("Pridani slova Pedri: %d\n", add_oat("Pedri", l_table));
    printf("Pridani slova Mbappe: %d\n", add_oat("Mbappe", l_table));
    printf("Pridani slova Nico: %d\n", add_oat("Nico", l_table));
    printf("Hledani slova Nico: %d\n",  contains_oat("Nico", l_table));
    printf("Mazani slova Nico: %d\n", remove_oat("Nico", l_table));
    printf("Hledani slova Nico: %d\n",  contains_oat("Nico", l_table));
    printf("Mazani slova Ronaldo: %d\n", remove_oat("Ronaldo", l_table));
    printf("Mazani slova Pedri: %d\n", remove_oat("Pedri", l_table));
    printf("Hledani slova Messi: %d\n",  contains_oat("Messi", l_table));
    printf("Hledani slova Neymar: %d\n",  contains_oat("Neymar", l_table));
    printf("Hledani slova Haaland: %d\n",  contains_oat("Haaland", l_table));
    printf("Hledani slova Ronaldo: %d\n",  contains_oat("Ronaldo", l_table));

    print_enter();
    print_enter();

    printf("HASHOVACI TABULKY NAD RETEZCI S RESENIM KOLIZI OTEVRENYM ADRESOVANIM (KVADRATICKA FUNKCE)\n");
    oa_table* q_table = create_oa_table(QUANTITY, hash_f, q_hash);
    printf("Pridani slova Messi: %d\n", add_oat("Messi", q_table));
    printf("Pridani slova Ronaldo: %d\n", add_oat("Ronaldo", q_table));
    printf("Pridani slova Lewandovski: %d\n", add_oat("Lewandovski", q_table));
    printf("Pridani slova Haaland: %d\n", add_oat("Haaland", q_table));
    printf("Pridani slova Werner: %d\n", add_oat("Werner", q_table));
    printf("Pridani slova Pedri: %d\n", add_oat("Pedrii", q_table));
    printf("Pridani slova Mbappe: %d\n", add_oat("Mbappe", q_table));
    printf("Pridani slova Nico: %d\n", add_oat("Nico", q_table));
    printf("Hledani slova Nico: %d\n",  contains_oat("Nico", q_table));
    printf("Mazani slova Nico: %d\n", remove_oat("Nico", q_table));
    printf("Hledani slova Nico: %d\n",  contains_oat("Nico", q_table));
    printf("Mazani slova Ronaldo: %d\n", remove_oat("Ronaldo", q_table));
    printf("Mazani slova Pedri: %d\n", remove_oat("Pedrii", q_table));
    printf("Hledani slova Messi: %d\n",  contains_oat("Messi", q_table));
    printf("Hledani slova Neymar: %d\n",  contains_oat("Neymar", q_table));
    printf("Hledani slova Haaland: %d\n",  contains_oat("Haaland", q_table));
    printf("Hledani slova Werner: %d\n",  contains_oat("Werner", q_table));
    printf("Hledani slova Ronaldo: %d\n",  contains_oat("Ronaldo", q_table));
    printf("Hledani slova Pedri: %d\n",  contains_oat("Pedrii", q_table));




    return 0;
}