#include <stdio.h>
#include <stdlib.h>

void put_enter(){
    printf("\n");
}

typedef struct tree_node{
int value;
struct tree_node *left_child;
struct tree_node *right_child;
struct tree_node *parent;
int height;
}Tree_node;

typedef struct tree{
Tree_node *root;
} AVL_Tree;

int subtree_high(Tree_node *node1){
    int h = 0;
    Tree_node *node2;
    node2 = node1; 
    if (node1 == NULL){
        return -1;
    }
    else {
        node1 = node1->left_child;
        int lheight = subtree_high(node1);
        node1 = node2;
        node1 = node1->right_child;
        int rheight = subtree_high(node1);
        node1 = node2;

        if (lheight > rheight){ 
            return (lheight + 1);
        }
        else{ 
            return (rheight + 1);
        }
    }
}

int node_balance_fun(Tree_node *node1){
    if(node1->left_child == NULL && node1->right_child == NULL){
        return 0;
    }
    else if(node1->left_child == NULL){
        return (-1 - (node1->right_child->height));
    }
    else if(node1->right_child == NULL){
        return ((node1->left_child->height) - (-1));
    }
    else{
        return ((node1->left_child->height) - (node1->right_child->height));
    }
}

int bigger_height(Tree_node *node1, Tree_node *node2){
    if(node1 != NULL && node2 != NULL){
        if(node1->height < node2->height){
            return node2->height;
        }
        else{
            return node1->height;
        }
    }
    else if(node1 != NULL){
        return node1->height;
    }
    else if(node2 != NULL){
        return node2->height;
    }
    else{
        return -1;
    }
}

void update_height(Tree_node *node){
    while(node != NULL){
        node->height = bigger_height(node->left_child, node->right_child) + 1;
        node = node->parent;
    }
}

void rotation_right(Tree_node *node1){
    Tree_node *node_nr;
    node_nr = node1->left_child;
    //rodic
    node_nr->parent = node1->parent;
    if(node1->parent != NULL){
        if(node1->parent->value < node1->value){
            node1->parent->right_child = node_nr;
        }
        else{
            node1->parent->left_child = node_nr;
        }
    }
    node1->parent = node_nr;

    //left child
    node1->left_child = node_nr->right_child;

    //right child
    node_nr->right_child = node1;
}

void rotation_left(Tree_node *node1){
    Tree_node *node_nr;
    node_nr = node1->right_child;
    //rodic
    node_nr->parent = node1->parent;
    if(node1->parent != NULL){
        if(node1->parent->value < node1->value){
            node1->parent->right_child = node_nr;
        }
        else{
            node1->parent->left_child = node_nr;
        }
    }
    node1->parent = node_nr;

    //right child
    node1->right_child = node_nr->left_child;

    //left child
    node_nr->left_child = node1;
}

void set_root(Tree_node *node, AVL_Tree *tree){
    if(node->parent->parent == NULL){
        tree->root = node->parent;
    }
}

void AVL_add(AVL_Tree *t1, int data){    
    int pom = 0;
    AVL_Tree *t2, *t3;
    t2 = (AVL_Tree*) malloc(sizeof(AVL_Tree));
    t3 = (AVL_Tree*) malloc(sizeof(AVL_Tree));
    Tree_node *node, *node1;
    node = (Tree_node*) malloc(sizeof(Tree_node));
    node->left_child = NULL;
    node->right_child = NULL;
    node->parent = NULL;
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
        node->height = 0;
       
        t1->root = node;
    }
    else if(node->value < t2->root->value){
        t2->root->left_child = node;
        node->parent = t2->root;
    }
    else{
        t2->root->right_child = node;
        node->parent = t2->root;
    }
    node1 = node;
    node->height = subtree_high(node);
    update_height(node);
    while(node != NULL){
        if(node_balance_fun(node)== 1 || node_balance_fun(node)== -1 || node_balance_fun(node)== 0){}
        else{             
                if(node_balance_fun(node) == 2 && node_balance_fun(node->left_child) == -1){
                    pom = 1;
                    node = node->left_child;
                    rotation_left(node);
                    node = node->parent->parent;
                    rotation_right(node); 
                    set_root(node, t1);  
                    node = node;
                    update_height(node);                                     
                }
                else if(node_balance_fun(node) == -2 && node_balance_fun(node->right_child) == 1){
                    pom = 1;
                    node = node->right_child;
                    rotation_right(node);
                    node = node->parent->parent;
                    rotation_left(node); 
                    set_root(node, t1);
                    update_height(node);
                }               
            if(pom != 1){
                if(node1->value > node->value){
                    rotation_left(node);
                    set_root(node, t1);
                    update_height(node);
                }
                else{
                    rotation_right(node);
                    set_root(node, t1);
                    update_height(node);
                }
            }
        }
        node1 = node;
        node = node->parent;
        pom = 0;
    }      
}

void print_in_order1(AVL_Tree *t1){
    AVL_Tree * t2;
    t2 = (AVL_Tree*) malloc(sizeof(AVL_Tree));
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
    free(t2);
}

int height(AVL_Tree *t1){
    AVL_Tree *t2;
    t2 = (AVL_Tree*) malloc(sizeof(AVL_Tree));
    t2->root = t1->root;
    if (t1->root == NULL){
        return 0;
    }
    else {
        t1->root = t1->root->left_child;
        int lheight = height(t1);
        t1->root = t2->root;
        t1->root = t1->root->right_child;
        int rheight = height(t1);
        t1->root = t2->root;

        if (lheight > rheight){ 
            return (lheight + 1);
        }
        else{ 
            return (rheight + 1);
        }
    }
}

void printcurrentlevel(AVL_Tree *t1, int level){
    AVL_Tree *t2;
    t2 = (AVL_Tree*) malloc (sizeof(AVL_Tree));
    t2->root = t1->root;
    if(t1->root == NULL){
        return;
    }
     
    if (level == 1){
        printf("%d ", t1->root->value);
    }

    else if (level > 1){
        t1->root = t1->root->left_child;
        printcurrentlevel(t1, level - 1);
        t1->root = t2->root;
        t1->root = t1->root->right_child;
        printcurrentlevel(t1, level - 1);
        t1->root = t2->root;
    }
}

void print_bft(AVL_Tree *t1){
    int h = height(t1);
    for(int i = 1; i <= h; i++){ 
        printcurrentlevel(t1, i);
    }
    printf("\n");
}

int main(){


    AVL_Tree *stromek;
    stromek = (AVL_Tree*) malloc (sizeof(AVL_Tree));

    AVL_add(stromek, 20);
    AVL_add(stromek, 25);
    AVL_add(stromek, 5);
    AVL_add(stromek, 3);
    AVL_add(stromek, 2);
    AVL_add(stromek, 15);

    print_in_order1(stromek);
    put_enter();
    print_bft(stromek);


    return 0;
}