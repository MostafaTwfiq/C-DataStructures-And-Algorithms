#ifndef C_DATASTRUCTURES_TXTFILELOADER_H
#define C_DATASTRUCTURES_TXTFILELOADER_H


#include <stdio.h>


typedef struct TxtFileLoader {
    char *dir;
    FILE *fileP;
} TxtFileLoader;


TxtFileLoader *txtFileLoaderInitialization(char *fileDir);

struct String *txtLoaderReadFileS(TxtFileLoader *txtFileLoader);

char *txtLoaderReadFileC(TxtFileLoader *txtFileLoader);

struct Vector *txtLoaderReadFileLines(TxtFileLoader *txtFileLoader);

struct Vector *txtLoaderReadFileWthDelimiter(TxtFileLoader *txtFileLoader, char *delimiter);

int txtLoaderCountLines(TxtFileLoader *txtFileLoader);

struct String *txtLoaderReadLineS(TxtFileLoader *txtFileLoader, int lineIndex);

char *txtLoaderReadLineC(TxtFileLoader *txtFileLoader, int lineIndex);

void txtLoaderWriteC(TxtFileLoader *txtFileLoader, char *data);

void txtLoaderWriteS(TxtFileLoader *txtFileLoader, struct String *data);

void txtLoaderAppendC(TxtFileLoader *txtFileLoader, char *data);

void txtLoaderAppendS(TxtFileLoader *txtFileLoader, struct String *data);

void txtLoaderAppendAllC(TxtFileLoader *txtFileLoader, struct Vector *newLines);

void txtLoaderAppendAllS(TxtFileLoader *txtFileLoader, struct Vector *newLines);

void txtLoaderAppendToLineC(TxtFileLoader *txtFileLoader, char *lineToAppend, int index);

void txtLoaderAppendToLineS(TxtFileLoader *txtFileLoader, struct String *stringToAppend, int index);

void txtLoaderAddLineC(TxtFileLoader *txtFileLoader, char *line, int index);

void txtLoaderAddLineS(TxtFileLoader *txtFileLoader, struct String *line, int index);

void txtLoaderAddAllC(TxtFileLoader *txtFileLoader, struct Vector *newLines, int index);

void txtLoaderAddAllS(TxtFileLoader *txtFileLoader, struct Vector *newLines, int index);

void txtLoaderUpdateLineC(TxtFileLoader *txtFileLoader, char *line, int index);

void txtLoaderUpdateLineS(TxtFileLoader *txtFileLoader, struct String *line, int index);

void txtLoaderRemoveLine(TxtFileLoader *txtFileLoader, int index);

void txtLoaderClearFile(TxtFileLoader *txtFileLoader);

void txtLoaderChangeFile(TxtFileLoader *txtFileLoader, char *newFileDir);

void destroyTxtFileLoader(void *txtFileLoader);

#endif //C_DATASTRUCTURES_TXTFILELOADER_H