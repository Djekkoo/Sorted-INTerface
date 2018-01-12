#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "sortedcontainer.h"

int data_compare(data* d1, data* d2) {
    assert(d1);
    assert(d2);
    if(d1->age < d2->age) return -1;
    if(d1->age > d2->age) return 1;
    return strcmp(d1->name, d2->name);
}

// Do not change
void data_print(data* d, FILE* f) {
    fprintf(f, "%i %s", d->age, d->name);
}

data* data_new(int age, char const* name) {
    data* d = (data*)malloc(sizeof(data));
    d->age = age;
    strncpy(d->name, name, NAME_LENGTH);
    return d;
}

void data_delete(data* d) {
    free(d);
}

node* node_new(data* d) {
    // Implement this (done?)
    node* n = (node*)malloc(sizeof(node));
    n->data = d;
    n->left = NULL;
    n->right = NULL;
    return n;
}

void node_delete(node* n) {
    // Implement this (done?)
    data_delete(n->data);
    free(n);
}

sortedcontainer* sortedcontainer_new() {
    sortedcontainer* d = (sortedcontainer*)malloc(sizeof(sortedcontainer));
    d->root = NULL;
    return d;
}

void sortedcontainer_insert(sortedcontainer* sc, data* data) {
    // Implement this
    node** n_compare = &sc->root;
    while(*n_compare != NULL) {
        int cmp = data_compare((*n_compare)->data, data) ;
        if (cmp == 0) return;
        if (cmp > 0) {
            n_compare = &(*n_compare)->left;
        } else {
            n_compare = &(*n_compare)->right;
        }
    }
    node* n = node_new(data);
    *n_compare = n;
}

int sortedcontainer_erase(sortedcontainer* sc, data* data) {
    if (sc->root == NULL) {
        return 0;
    }

    int result;
    node* aux_root = node_new(data_new(0, "asdflajsdflkjasdlfja393940293fdlsjkvnaldkjfa"));
    if (data_compare(sc->root->data, aux_root->data) > 0) {
        aux_root->right = sc->root;        
    } else {         
        aux_root->left = sc->root;
    }
    sc->root = aux_root;

    node** parent_pointer = find_parent(&aux_root, data);
    // printf("%p", (void*)parentf_pointer);
    if (parent_pointer != NULL) {
        node* parent_node = *parent_pointer;
        node** target_pointer;
        node* target_node;

        // Get target node
        if (parent_node->left != NULL && data_compare(parent_node->left->data, data) == 0) {
            target_node = parent_node->left;
            target_pointer = &parent_node->left;
        } else {
            target_node = parent_node->right;
            target_pointer = &parent_node->right;
        }
        
        // Case 1: no children
        
        if (target_node->left == NULL && target_node->right == NULL) {
            node_delete(target_node);
            *target_pointer = NULL;
            result = 1;
        }
        // Case 3: Two children
        else if (target_node->left != NULL && target_node->right != NULL) {
            node* lmc = target_node->right;
            node** target_replace = &target_node->right;
            while (lmc->left != NULL) {
                target_replace = &lmc->left;
                lmc = lmc->left;
            }
            // data_delete(target_node->data);
            // target_node->data = data_new(lmc->data->age, lmc->data->name);
            // if (lmc->right != NULL) {
            *target_replace = lmc->right;
            *target_pointer = lmc;
            lmc->right = target_node->right;
            lmc->left = target_node->left;
            node_delete(target_node);
            // }
            // node_delete(lmc);
            result = 1;
        }
        // Case 2: One child
        else {

            // sortedcontainer_print(sc, stdout);
            if (target_node->left != NULL) {
                *target_pointer = target_node->left;
            } else {
                *target_pointer = target_node->right;
            }
            
            node_delete(target_node);

    // sortedcontainer_print(sc, stdout);
            result = 1;
        }
    } else {
        result = 0;
    }
     
    if(aux_root->left != NULL) {
        sc->root = aux_root->left;
    } else {
        sc->root = aux_root->right;
    }
    node_delete(aux_root);
    return result;
}



int sortedcontainer_contains(sortedcontainer* sc, data* data) {
    // Implement this
    return sc->root != NULL && (data_compare(sc->root->data, data) == 0 || find_parent(&sc->root, data) != NULL);
}

node** find_parent(node** n, data* data) {
    if (((*n)->left != NULL && data_compare((*n)->left->data, data) == 0) || ((*n)->right != NULL && data_compare((*n)->right->data, data) == 0)) {
        return n;
    }
    int cmp = data_compare((*n)->data, data);
    // if (cmp == 0) {
    //     return n;
    // }
    if (cmp > 0 &&(*n)->left != NULL) {
        return find_parent(&(*n)->left, data);
    }
    else if (cmp < 0 && (*n)->right != NULL) {
        return find_parent(&(*n)->right, data);
    }
    return NULL;
}


// Do not change
static void node_printtree(node* n, int level, FILE* printFile) {
    fprintf(printFile, "%*s ", level, "");
    if(n) {
        data_print(n->data, printFile);
        fprintf(printFile, "\n");
        node_printtree(n->left, level+1, printFile);
        node_printtree(n->right, level+1, printFile);
    } else {
        fprintf(printFile, "(nil)\n");
    }
}

// Do not change
void sortedcontainer_print(sortedcontainer* sc, FILE* printFile) {
    node_printtree(sc->root, 0, printFile);
}

static void node_deletetree(node* n) {
    if(n) {
        node* left = n->left;
        node* right = n->right;
        node_delete(n);
        node_deletetree(left);
        node_deletetree(right);
    }
}

void sortedcontainer_delete(sortedcontainer* sc) {
    node_deletetree(sc->root);
    free(sc);
}
