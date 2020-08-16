#ifndef C_DATASTRUCTURES_INPUTSCANNER_H
#define C_DATASTRUCTURES_INPUTSCANNER_H

#include <stdio.h>

struct String *scanStrS(FILE *dir);

char *scanStrC(FILE *dir);

char scanChar(FILE *dir);

int scanInt(FILE *dir);

double scanDouble(FILE *dir);

float scanFloat(FILE *dir);

long scanLong(FILE *dir);

long long scanLongLong(FILE *dir);

short scanShort(FILE *dir);


#endif //C_DATASTRUCTURES_INPUTSCANNER_H
