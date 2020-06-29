#include "Headers/AVLTree.h"
#define TRACE 0
#define MAX_SEARCH_ITEMS 10

void fillTree(AVLTree **tree);
void fillSearchValues( int *valArray);
int mycmp(const void * v1, const void*v2);


void myPrint(void * var){
    printf("%d , ",*(int*)var);
}


void fillTree(AVLTree** tree){
    printf( "Constructing tree\n\n" );
    int* key2Insert;
    for(int i=0; i<10; i++){
        key2Insert=calloc(1,sizeof(int));
        *key2Insert =i;
        (*tree)->root= insertAVLTree(*tree, (*tree)->root, key2Insert);
        if(TRACE) printf("key: %d,",*(int*)(*tree)->root->key);
    }

    (*tree)->nodeCount = getSizeAVLTree((*tree)->root);
    printf( "\n\nTree constructed\n\n" );
}

void fillSearchValues( int *valArray){
    for(int i=0; i<10; i++){
        if(i>MAX_SEARCH_ITEMS) break;
        valArray[i]= i;
        if (TRACE)printf ("%d read; inserted\n", valArray[i] );

    }
}
int comp(const void *p1, const void *p2) {
    return *((int *)p1) - *((int *)p2);
}


int main(){
    AVLTree *tree = AVLTreeInitialize(sizeof(int), comp);
    fillTree(&tree);
    printAVLTree(tree->root, myPrint);

    //some Tree stats
    printf( "\nSummary of AVL tree\n=============================\n" );
    printAVLTreeStats(tree);
    printf( "=============================\n\n\n" );

    printf( "TreeDump (inOrder)\n=============================\n" );
    printInOrderAVLTree(tree->root, myPrint);
    printf( "\n=============================\n\n" );

    int values[MAX_SEARCH_ITEMS+1];
    fillSearchValues(values);


    printf( "\n search and replace\n=============================\n" );
    for(int o=0;o<MAX_SEARCH_ITEMS;o++) {
        tree->root = insertAVLTree(tree, tree->root, values + o);
    }


    int found =0, lost =0;
    for(int i=0;i<MAX_SEARCH_ITEMS;i++){
        if(tree->nodeCount-1<i)  break;
        if(isPresentInAVLTree(tree, tree->root, (void *) (values + i))){
            if (TRACE)printf("found search value %d\n",values[i]);
            found++;
        }else{
            lost++;
            if(TRACE)printf("didnot find search value %s\n",values[i]);
        }
    }

    printf( "\nSummary of search\n=============================\n" );
    printf("found %d of %d while lost %d\n\n\n", found,MAX_SEARCH_ITEMS,lost);

    printf("\nConverting Tree to array: \n=================================\n");
    int* array = AVLTreeToArray(tree);
    printf("global node count: %d\n",tree->nodeCount);
    printf("data: ");
    for(unsigned int p=0;p<tree->nodeCount;p++){
        printf("[key:%d ] ", *((int*)(array+p)));
    }
    printf("\n\n\n");


    printAVLTreeStats(tree);




    printf("\nFreeing Tree: \n=================================\n");
    freeAVLTree(&tree->root);

    if(tree->root==NULL) printf("Tree has been freed successfully\n");
    else printf("Failed to free tree \n");
    found =0, lost =0;
    for(int i=0;i<MAX_SEARCH_ITEMS;i++){
        if(isPresentInAVLTree(tree, tree->root, values[i])){
            if (TRACE)printf("found search value %d\n",values[i]);
            found++;
        }else{
            lost++;
            if(TRACE)printf("didnot find search value %d\n",values[i]);
        }
    }
    printf("found %d of %d while cleared %d\n", found,MAX_SEARCH_ITEMS,lost);
    free(tree);
    return 0;
}
