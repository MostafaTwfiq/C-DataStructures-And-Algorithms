#ifndef C_DATASTRUCTURES_TXTFILELOADER_H
#define C_DATASTRUCTURES_TXTFILELOADER_H

#include "../System/Utils.h"



typedef struct TxtFileLoader {
    FILE *dir;
} TxtFileLoader;


TxtFileLoader *txtFileLoaderInitialization(char *fileDir);

struct String *txtLoaderReadFileString(TxtFileLoader *txtFileLoader);

struct Vector *txtLoaderReadFileLines(TxtFileLoader *txtFileLoader);

char *txtLoaderReadFileCharArr(TxtFileLoader *txtFileLoader);

#endif //C_DATASTRUCTURES_TXTFILELOADER_H
