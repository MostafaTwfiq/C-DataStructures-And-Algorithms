#include "Headers/AVLTree.h"
#define TRACE 0
#define MAX_SEARCH_ITEMS 20

void fillTree(AVLTree **tree);
void fillSearchValues( int **valArray);
int mycmp(void * v1, void*v2);


void myPrint(void * var){
    printf("%d , ",*(int*)var);
}


void fillTree(AVLTree** tree){
    printf( "Constructing tree\n\n" );
    int* key2Insert;
    for(int i=0; i<300; i++){
        key2Insert=calloc(1,sizeof(int));
        *key2Insert =i;
        (*tree)->root= insert(*tree,(*tree)->root,key2Insert);
        if(TRACE) printf("key: %d,",*(int*)*(*tree)->root->key);
    }

    (*tree)->nodeCount = getSizeBinaryTree((*tree)->root);
    printf( "\n\nTree constructed\n\n" );
}

void fillSearchValues( int **valArray){
    int* key2Insert;
    key2Insert=calloc(1,sizeof(int));
    for(int i=0; i<300; i++){
        if(i>MAX_SEARCH_ITEMS) break;
        *key2Insert=i;
        valArray[i]= key2Insert;
        if (TRACE)printf ("%d read; %d inserted\n", key2Insert, valArray[i] );

    }
}
int mycmp(void * v1, void*v2){
    if(*(int*)(v1)>*(int*)(v2)){
        return 1;
    }
    else if(*(int*)(v1)<*(int*)(v2)) {
        return -1;
    }
    return 0;
}


int main(){
    AVLTree *tree = createNewTree(sizeof(int),mycmp);
    fillTree(&tree);
    printTree(tree->root,myPrint);

    //some Tree stats
    printf( "\nSummary of AVL tree\n=============================\n" );
    printTreeStats(tree);
    printf( "=============================\n\n\n" );

    printf( "TreeDump (inOrder)\n=============================\n" );
    printInOrder(tree->root,myPrint);
    printf( "\n=============================\n\n" );

    int *values[MAX_SEARCH_ITEMS+1];
    fillSearchValues(&values[0]);


    printf( "\n search and replace\n=============================\n" );
    for(int o=0;o<MAX_SEARCH_ITEMS;o++) {
        tree->root = insert(tree,tree->root,(void *)&values[o]);
    }


    int found =0, lost =0;
    for(int i=0;i<MAX_SEARCH_ITEMS;i++){
        if(tree->nodeCount-1<i)  break;
        if(isPresent(tree,tree->root, (void *)values[i]) ){
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
    void** array = treeToArray(tree);
    printf("global node count: %d\n",tree->nodeCount);
    printf("data: ");
    for(unsigned int p=0;p<tree->nodeCount;p++){
        printf("[key:%d ] ", *(int*)array[p]);
    }
    printf("\n\n\n");



    for(int i=0;i<MAX_SEARCH_ITEMS;i++){
        if(tree->nodeCount-1<i)  break;
        if(isPresent(tree,tree->root,values[i])){
            if (1){
                tree->root = Delete(tree,tree->root,values[i]);
                tree->nodeCount--;
                printf("Deleting search value %d\n",values[i]);
            }
        }else{
            if(TRACE)printf("didnot find search value %d\n",values[i]);
        }
    }
    printTreeStats(tree);




    printf("\nFreeing Tree: \n=================================\n");
    freeTree(&tree->root);

    if(tree->root==NULL) printf("Tree has been freed successfully\n");
    else printf("Failed to free tree \n");
    found =0, lost =0;
    for(int i=0;i<MAX_SEARCH_ITEMS;i++){
        if(isPresent(tree,tree->root,values[i])){
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
