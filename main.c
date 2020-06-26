#include <stdio.h>
#include <stdlib.h>
#include "Headers/Stack.h"

int main() {
    Stack  *s = StackInitalization(sizeof(float));
    float *p,j=0.5;
    p=&j;
    for(int i=0;i<=50;i++,j=i){
        pushStack(s,p);
    }

    while(!isEmptyStack(s)){
        printf("%f\n",*(float*)popStack(s));
    }
    StackClear(s);
    StackDestroy(s);
}