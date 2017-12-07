#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#include "test.h"
#include "sortedcontainer.h"

typedef int (*test_t)(FILE* );

#define ASSERT(c,s) do { \
    if(!(c)) { \
        fprintf(printFile, "ASSERT FAILED[%s:%i] %s: %s\n", __FILE__, __LINE__, #c, s); \
        return 1; \
    } \
} while(0)

int test1(FILE* printFile) {
    (void)printFile;

    sortedcontainer* sc = sortedcontainer_new();

    ASSERT(sc != NULL, "failed to create sorted container");
    ASSERT(sc->root == NULL, "root is not NULL");

    sortedcontainer_delete(sc);

    return 0;
}

int test2(FILE* printFile) {
    (void)printFile;

    sortedcontainer* sc = sortedcontainer_new();

    ASSERT(sc != NULL, "failed to create sorted container");
    ASSERT(sc->root == NULL, "root is not NULL");

    data* dat = data_new(10, "aap");
    sortedcontainer_insert(sc, dat);

    ASSERT(sc->root != NULL, "root is NULL");
    ASSERT(sc->root->data != NULL, "root->data is NULL");
    ASSERT(!data_compare(dat, sc->root->data), "data is not equivalent");
    ASSERT(dat == sc->root->data, "data is not the same instant");
    ASSERT(sc->root->left == NULL, "root->data->left is not NULL");
    ASSERT(sc->root->right == NULL, "root->data->right is not NULL");

    data* dataDifferent = data_new(20, "noot");
    data* dataCopy = data_new(10, "aap");

    ASSERT(sortedcontainer_contains(sc, dataCopy), "data is not in the container (sortedcontainer_contains)");
    ASSERT(!sortedcontainer_contains(sc, dataDifferent), "data should not be in the container");

    sortedcontainer_erase(sc, dataDifferent);

    ASSERT(sc->root->data != NULL, "data wrongly deleted");
    ASSERT(!data_compare(dat, sc->root->data), "data wrongly deleted");
    ASSERT(dat == sc->root->data, "data wrongly deleted");
    ASSERT(sortedcontainer_contains(sc, dataCopy), "data is not in the container anymore (sortedcontainer_contains)");
    ASSERT(!sortedcontainer_contains(sc, dataDifferent), "data should not be in the container");

    sortedcontainer_erase(sc, dataCopy);

    ASSERT(sc->root == NULL, "data not deleted");

    sortedcontainer_delete(sc);

    data_delete(dataDifferent);
    data_delete(dataCopy);

    return 0;
}

int test3(FILE* printFile) {
    (void)printFile;

    sortedcontainer* sc = sortedcontainer_new();

    data* aap = data_new(10, "aap");
    data* noot = data_new(20, "noot");
    data* mies = data_new(15, "mies");

    sortedcontainer_insert(sc, aap);
    sortedcontainer_insert(sc, noot);
    sortedcontainer_insert(sc, mies);

    ASSERT(sc != NULL, "failed to create sorted container");
    ASSERT(sc->root != NULL, "root is NULL");
    ASSERT(sc->root->data != NULL, "root->data is NULL");

    ASSERT(!data_compare(aap, sc->root->data), "data is not equivalent");
    ASSERT(aap == sc->root->data, "data is not the same instant");

    ASSERT(!data_compare(noot, sc->root->right->data), "data is not equivalent");
    ASSERT(noot == sc->root->right->data, "data is not the same instant");

    ASSERT(!data_compare(mies, sc->root->right->left->data), "data is not equivalent");
    ASSERT(mies == sc->root->right->left->data, "data is not the same instant");

    sortedcontainer_erase(sc, noot);

    ASSERT(!data_compare(aap, sc->root->data), "data is not equivalent");
    ASSERT(aap == sc->root->data, "data is not the same instant");

    ASSERT(!data_compare(mies, sc->root->right->data), "data is not deleted");
    ASSERT(mies == sc->root->right->data, "data is not deleted");

    ASSERT(sc->root->right->left == NULL, "left child of mies' node is not NULL");
    ASSERT(sc->root->right->right == NULL, "right child of mies' node is not NULL");

    ASSERT(sortedcontainer_contains(sc, aap), "data is not in the container anymore (sortedcontainer_contains)");
    ASSERT(sortedcontainer_contains(sc, mies), "data is not in the container anymore (sortedcontainer_contains)");

    sortedcontainer_delete(sc);

    return 0;
}

int test4(FILE* printFile) {
    (void)printFile;

    // Add a test in the style of test3 to test the deletion of a node with
    // two children

    sortedcontainer* sc = sortedcontainer_new();

    data* aap = data_new(10, "aap");
    data* noot = data_new(20, "noot");
    data* mies = data_new(5, "mies");

    sortedcontainer_insert(sc, aap);
    sortedcontainer_insert(sc, noot);
    sortedcontainer_insert(sc, mies);

    ASSERT(sc != NULL, "failed to create sorted container");
    ASSERT(sc->root != NULL, "root is NULL");
    ASSERT(sc->root->data != NULL, "root->data is NULL");

    ASSERT(!data_compare(aap, sc->root->data), "data is not equivalent");
    ASSERT(aap == sc->root->data, "data is not the same instant");

    ASSERT(!data_compare(noot, sc->root->right->data), "data is not equivalent");
    ASSERT(noot == sc->root->right->data, "data is not the same instant");

    ASSERT(!data_compare(mies, sc->root->left->data), "data is not equivalent");
    ASSERT(mies == sc->root->left->data, "data is not the same instant");

    sortedcontainer_erase(sc, aap);
    // sortedcontainer_print(sc, stdout);

    ASSERT(!data_compare(noot, sc->root->data), "data is not equivalent");
    ASSERT(noot == sc->root->data, "data is not the same instant");

    ASSERT(!data_compare(mies, sc->root->left->data), "data is not deleted");
    ASSERT(mies == sc->root->left->data, "data is not deleted");

    ASSERT(sc->root->left->left == NULL, "left child of mies' node is not NULL");
    ASSERT(sc->root->left->right == NULL, "right child of mies' node is not NULL");

    ASSERT(sortedcontainer_contains(sc, noot), "data is not in the container anymore (sortedcontainer_contains)");
    ASSERT(sortedcontainer_contains(sc, mies), "data is not in the container anymore (sortedcontainer_contains)");

    sortedcontainer_delete(sc);

    return 0;
}

int test5(FILE* printFile) {
    (void)printFile;

    // Add a test in the style of test3 to test the deletion of a node with
    // two children, who each have two children as well
    
    sortedcontainer* sc = sortedcontainer_new();

    data* aap = data_new(10, "aap");
    data* noot = data_new(20, "noot");
    data* noot_l = data_new(15, "noot_left");
    data* noot_r = data_new(25, "noot_right");
    data* mies = data_new(5, "mies");
    data* mies_l = data_new(0, "mies_left");
    data* mies_r = data_new(7, "mies_right");

    sortedcontainer_insert(sc, aap);
    sortedcontainer_insert(sc, noot);
    sortedcontainer_insert(sc, noot_l);
    sortedcontainer_insert(sc, noot_r);
    sortedcontainer_insert(sc, mies);
    sortedcontainer_insert(sc, mies_l);
    sortedcontainer_insert(sc, mies_r);
    // sortedcontainer_print(sc, stdout);

    ASSERT(sc != NULL, "failed to create sorted container");
    ASSERT(sc->root != NULL, "root is NULL");
    ASSERT(sc->root->data != NULL, "root->data is NULL");

    ASSERT(!data_compare(aap, sc->root->data), "data is not equivalent");
    ASSERT(aap == sc->root->data, "data is not the same instant");

    ASSERT(!data_compare(noot, sc->root->right->data), "data is not equivalent");
    ASSERT(noot == sc->root->right->data, "data is not the same instant");

    ASSERT(!data_compare(mies, sc->root->left->data), "data is not equivalent");
    ASSERT(mies == sc->root->left->data, "data is not the same instant");

    sortedcontainer_erase(sc, aap);
    // sortedcontainer_print(sc, stdout);

    ASSERT(!data_compare(noot_l, sc->root->data), "data is not equivalent");
    ASSERT(noot_l == sc->root->data, "data is not the same instant");

    ASSERT(!data_compare(mies, sc->root->left->data), "data is not deleted");
    ASSERT(mies == sc->root->left->data, "data is not deleted");

    ASSERT(!data_compare(mies_l, sc->root->left->left->data), "left child of mies' node is not mies_left");
    ASSERT(mies_l == sc->root->left->left->data, "data is not the same instant");
    ASSERT(!data_compare(mies_r, sc->root->left->right->data), "right child of mies' node is not mies_right");
    ASSERT(mies_r == sc->root->left->right->data, "data is not the same instant");
    ASSERT(!data_compare(noot, sc->root->right->data), "Right child of root is not noot");
    ASSERT(noot == sc->root->right->data, "data is not the same instant");
    ASSERT(!data_compare(noot_r, sc->root->right->right->data), "Right child of noot is not noot_right");
    ASSERT(noot_r == sc->root->right->right->data, "data is not the same instant");

    ASSERT(sortedcontainer_contains(sc, noot), "data is not in the container anymore (sortedcontainer_contains)");
    ASSERT(sortedcontainer_contains(sc, noot_l), "data is not in the container anymore (sortedcontainer_contains)");
    ASSERT(sortedcontainer_contains(sc, noot_r), "data is not in the container anymore (sortedcontainer_contains)");
    ASSERT(sortedcontainer_contains(sc, mies), "data is not in the container anymore (sortedcontainer_contains)");
    ASSERT(sortedcontainer_contains(sc, mies_r), "data is not in the container anymore (sortedcontainer_contains)");
    ASSERT(sortedcontainer_contains(sc, mies_l), "data is not in the container anymore (sortedcontainer_contains)");

    sortedcontainer_delete(sc);

    // printf("%s", "done test5");

    return 0;
}

// If you want to add test6 and onwards, create the test6 function above and
// add it to this list
test_t tests[] = {test1, test2, test3, test4, test5};

void test(FILE* printFile) {
    fprintf(printFile, "Testing...\n");
    int max = sizeof(tests)/sizeof(*tests);
    int lmax = 1 + log10(max);
    // tests[4](printFile); // <- test5 invokation before segmentation-fault
    for(int i = 0; i < max; ++i) {
        int r = tests[i](printFile);
        fprintf(printFile, "[%*i/%i] ", lmax, i+1, max);
        if(r) {
            fprintf(printFile, "FAIL\n");
        } else {
            fprintf(printFile, "PASS\n");
        }
    }
}
