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
    node* n = node_new(data);
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
    *n_compare = n;
    
}

int sortedcontainer_erase(sortedcontainer* sc, data* data) {
    // Implement this
    (void)sc;
    (void)data;
    return 0;
}


int sortedcontainer_contains(sortedcontainer* sc, data* data) {
    // Implement this
    return sc->root != NULL && find_parent(&sc->root, data) != NULL;
}

node** find_parent(node** n, data* data) {

    if (((*n)->left != NULL && data_compare((*n)->left->data, data) == 0) || ((*n)->right != NULL && data_compare((*n)->right->data, data) == 0)) {
        return n;
    }
    int cmp = data_compare((*n)->data, data);
    // if (cmp == 0) {
    //     return n;
    // }
    if (cmp > 0 && (*n)->left != NULL) {
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
