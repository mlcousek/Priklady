#include <stdio.h>
#include <stdlib.h>
#include <string.h>


typedef struct node{
    int data;
    struct node *next;
} Node;

typedef struct list{
    Node *firstnode;
} List;

int length(struct list seznam){
    int pom = 1;

    while(seznam.firstnode->next){
        seznam.firstnode = seznam.firstnode->next;
        pom += 1;
    }
    
return pom;
}

void print_list(List seznam){
    for(seznam; seznam.firstnode; seznam.firstnode = seznam.firstnode->next){ 
        if (!seznam.firstnode->next){
            printf("%d", seznam.firstnode->data);
        }

        else {
            printf("%d, ", seznam.firstnode->data);
        }
    }
    printf("\n");
}

void add_start(struct list *seznam, int data){
    Node* new_node;
    new_node = (Node*) malloc(sizeof(Node));
    new_node->data = data;
    new_node->next = seznam->firstnode;
    seznam->firstnode = new_node;
}

void add_end(struct list *seznam, int data){
    Node* new_node;
    new_node = (Node*) malloc(sizeof(Node));
    new_node->data = data;
    new_node->next = NULL;
    List *seznam2;
    seznam2 = (List*) malloc(sizeof(List));
    seznam2->firstnode = seznam->firstnode;
    while(seznam->firstnode->next){
        seznam->firstnode = seznam->firstnode->next;
    }
    seznam->firstnode->next = new_node;
    seznam->firstnode = seznam2->firstnode;
}

void add_position(List *seznam, int data, int position){
    Node* new_node;
    new_node = (Node*) malloc(sizeof(Node));
    new_node->data = data;

    int pom = position - 1;
    int help = 0;
    List *seznam2;
    seznam2 = (List*) malloc(sizeof(List));
    seznam2->firstnode = seznam->firstnode;
    List *seznam3;
    seznam3 = (List*) malloc(sizeof(List));

    while(pom != 0 && seznam->firstnode != NULL){
        help = 1;
        seznam3->firstnode = seznam->firstnode;
        seznam->firstnode = seznam->firstnode->next;
        pom = pom - 1;
        if(pom == 0 || seznam->firstnode == NULL){
            seznam->firstnode = seznam3->firstnode;
        }
        //seznam->firstnode = seznam->firstnode->next;
    }
    if (help == 0){
        add_start(seznam, data);
        free(new_node);
        new_node = NULL;
    }
    else{
    new_node->next = seznam->firstnode->next;

    seznam->firstnode->next = new_node;  
    seznam->firstnode = seznam2->firstnode; 
    }    
}

int remove_start(struct list *seznam){
if(seznam->firstnode == NULL){
    return -1;
}
else if (seznam->firstnode->next == NULL){
    seznam->firstnode = NULL;
    return 0;
}
else {
    seznam->firstnode = seznam->firstnode->next;
    return 0;
}
}

int remove_end (struct list *seznam){
    List *seznam2;
    seznam2 = (List*) malloc (sizeof(List));
    seznam2->firstnode = seznam->firstnode;
    List *seznam3;
    seznam3 = (List*) malloc (sizeof(List));
if(seznam->firstnode == NULL){
    return -1;
}
else if (seznam->firstnode->next == NULL){
    seznam->firstnode = NULL;
    return 0;
}
else {
    while(seznam->firstnode->next != NULL){
        seznam3->firstnode = seznam->firstnode;
        seznam->firstnode = seznam->firstnode->next;
    }
    seznam->firstnode = seznam3->firstnode;
    seznam->firstnode->next = NULL;
    seznam->firstnode = seznam2->firstnode;
    return 0;
}
}

int search_key(List *seznam, int data){
    List *seznam2;
    seznam2 = (List*) malloc (sizeof(List*));
    seznam2->firstnode = seznam->firstnode;
    int pom = 1;
    int help = 0;
    if (seznam->firstnode == NULL){
        return -1;
    }
    else if(seznam->firstnode->next == NULL){
        if(seznam->firstnode->data == data){
            return 1;
        }
        else{
            return -1;
        }
    }
    else{
        while(seznam->firstnode != NULL && help != 1){
            //seznam->firstnode = seznam->firstnode->next;
            //pom++;
            if(seznam->firstnode->data == data){
                help = 1;
            }
            seznam->firstnode = seznam->firstnode->next;
            if (help !=  1){
                pom++;
            }
        }
        if(help == 1){
            seznam->firstnode = seznam2->firstnode;
            return pom;
        }
        else{
            seznam->firstnode = seznam2->firstnode;
            return -1;
            }  
    }

}

int remove_node(List *seznam, int data){
    List *seznam2;
    seznam2 = (List*) malloc (sizeof(List));
    seznam2->firstnode = seznam->firstnode;
    List *seznam3;
    seznam3 = (List*) malloc (sizeof(List));
    seznam3->firstnode = seznam->firstnode;
    int help = 0;
    int help2 = 0;
    if (seznam->firstnode == NULL){
        return -1;
    }
    else if(seznam->firstnode->next == NULL){
        if(seznam->firstnode->data == data){
            seznam->firstnode = NULL;
            return 0;
        }
        else{
            return -1;
        }
    }
    else{
        while(seznam2->firstnode != NULL && help != 1){
            if(seznam2->firstnode->data == data){
                help = 1;
            }
            if (help != 1){ 
                seznam2->firstnode = seznam2->firstnode->next;
            }
            if(help2 > 0 && help != 1){
                seznam->firstnode = seznam->firstnode->next;
            }
            help2 ++;
            
        }
        if (seznam2->firstnode == NULL){
            seznam->firstnode = seznam3->firstnode;
            return -1;
        }
        else{
           seznam->firstnode->next = seznam2->firstnode->next;
           if(help2 == 1){
                seznam->firstnode = seznam3->firstnode->next;
 
           }
            else{
                seznam->firstnode = seznam3->firstnode;
            }
           return 0;            
        }
        

    }
}


typedef struct tree_node{
int value;
struct tree_node *left_child;
struct tree_node *right_child;
}Tree_node;

typedef struct tree{
Tree_node *root;
} Tree;

void add_t(Tree *t1, int data){
    Tree *t2, *t3, *t4;
    t2 = (Tree*) malloc(sizeof(Tree));
    t3 = (Tree*) malloc(sizeof(Tree));
    t4 = (Tree*) malloc(sizeof(Tree));
    t4->root = t1->root;
    Tree_node *node;
    node = (Tree_node*) malloc(sizeof(Tree_node));
    node->left_child = NULL;
    node->right_child = NULL;
    node->value = data;
    t2->root = NULL;
    t3->root = t1->root;
    while (t3->root != NULL){
        t2->root = t3->root;
        if(node->value < t3->root->value){
            t3->root = t3->root->left_child;
        }
        else{
            t3->root = t3->root->right_child;
        }
    }
    if(t2->root == NULL){
        t1->root = node;
    }
    else if(node->value < t2->root->value){
        t2->root->left_child = node;
    }
    else{
        t2->root->right_child = node;
    }
    //t1->root = t4->root;
}

void print_in_order(Tree *t1){

    Tree *t2;
    t2 = (Tree*) malloc(sizeof(Tree));
    t2->root = t1->root;

    /*int help;
    for(int i = 0; t1->root->right_child != NULL; t1->root = t1->root->right_child)
    help = t1->root->value;
    t1->root = t2->root;
*/
    if(t1->root->left_child == NULL){
        
        printf("%d ", t1->root->value);

        if(t1->root->right_child == NULL){}

        else{
            t1->root = t1->root->right_child;
            print_in_order(t1);
            t1->root = t2->root;
        }
    }
    else {
        t1->root = t1->root->left_child;
        print_in_order(t1);
        //printf("%d ", t1->root->value);

        t1->root = t2->root;
        printf("%d ", t1->root->value);
        if(t1->root->right_child == NULL){}
        else{

            t1->root = t1->root->right_child;
            print_in_order(t1);

            t1->root = t2->root;
        }

    }

}


void print_in_order1(Tree *t1){
    Tree * t2;
    t2 = (Tree*) malloc(sizeof(Tree));
    t2->root = t1->root;
    if(t1 != NULL){
        if(t1->root->left_child != NULL){
            t1->root = t1->root->left_child;
            print_in_order1(t1); 
            t1->root = t2->root; 
        }
        printf("%d ", t1->root->value);

        if(t1->root->right_child != NULL) {
            t1->root = t1->root->right_child;
            print_in_order1(t1);
            t1->root = t2->root; 
        }
    }
    t1->root = t2->root;
}

int depth (Tree *t){
    Tree *t2, *t3;
    t2 = (Tree*) malloc(sizeof(Tree));
    t2->root = t->root;
    t3 = (Tree*) malloc(sizeof(Tree));
    t3->root = t->root;

    if(t->root == NULL){
        return -1;
    }
    else{
        t2->root = t->root->left_child;
        int leftdepth = depth(t2);
        t3->root = t->root->right_child;
        int rightdepth = depth(t3);

        if(leftdepth > rightdepth){
            return (leftdepth + 1);
        }
        else{
            return (rightdepth + 1);
        }
    }
}

int main(){

List *seznam = (List*) malloc(sizeof(List));
/*
print_list(*seznam);
add_start(seznam, 5);
print_list(*seznam);
add_start(seznam, 6);
print_list(*seznam);
add_start(seznam, 7);
add_start(seznam, 8);
add_start(seznam, 9);
print_list(*seznam);
add_end(seznam, 4);
print_list(*seznam);
add_position(seznam, 10, 2);
print_list(*seznam);
remove_start(seznam);
print_list(*seznam);
remove_end(seznam);
print_list(*seznam);
printf("%d\n", search_key(seznam, 7));
remove_node(seznam, 6);
print_list(*seznam);
remove_node(seznam, 7);
remove_node(seznam, 5);
print_list(*seznam);
printf("%d\n", remove_node(seznam, 55));
print_list(*seznam);
add_end(seznam, 99);
add_position(seznam, 500, 3);
print_list(*seznam);
printf("%d\n", remove_node(seznam, 500));
print_list(*seznam);
*/

Tree *strom = (Tree*) malloc (sizeof(Tree));

add_t(strom, 6);
add_t(strom, 8);
add_t(strom, 3);
add_t(strom, 4);
add_t(strom, 20);
add_t(strom, 25);
add_t(strom, 15);
add_t(strom, 1);
add_t(strom, 10);


printf("%d\n", strom->root->right_child->right_child->left_child->left_child->value);

print_in_order(strom);
printf("\n");
print_in_order1(strom);
printf("\n");
printf("%d\n", depth(strom));
add_t(strom, 30);
add_t(strom, 50);
printf("%d\n", depth(strom));
print_in_order1(strom);
printf("\n");


    return 0;
}