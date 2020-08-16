#ifndef C_DATASTRUCTURES_STRING_H
#define C_DATASTRUCTURES_STRING_H

#include <stdio.h>

#ifdef __cplusplus
extern "C" {
#endif


/** @struct String
*  @brief This structure implements a basic String.
*  @var String::string
*  Member 'string' is a pointer to the string char array.
*  @var String::count
*  Member 'count' holds the current number of characters.
*  @var String::length
*  Member 'length' holds the current length of the allocated char array.
*/

typedef struct String {
    char *string;
    int count;
    int length;
} String;

String *stringInitialization(int initialLength);

void stringAppendChar(String *string, char c);

void stringAddChar(String *string, int index, char c);

void stringUpdateChar(String *string, int index, char c);

void stringRemove(String *string, int index);

void stringAppendC(String *string, char *charArr);

void stringAppendS(String *string, String *newString);

void stringChangeStringC(String *string, char *newCharArr);

void stringChangeStringS(String *string, String *newString);

int stringGetIndex(String *string, char c);

char stringGet(String *string, int index);

int stringSubStringC(String *string, char *charArr);

int stringSubStringS(String *string, String *sString);

char *stringToCharArray(String *string);

char *stringToCustomCharArray(String *string, int startIndex, int endIndex);

int stringEqualsC(String *string, char *charArr);

int stringEqualsS(String *string, String *sString);

int stringCompareC(String *string, char *charArr);

int stringCompareS(const void *string, const void *sString);

int stringGetLength(String *string);

void stringCustomTrimStart(String *string, char *specialCharacters);

void stringTrimStart(String *string);

void stringCustomTrimEnd(String *string, char *specialCharacters);

void stringTrimEnd(String *string);

void stringTrim(String *myString);

void stringCustomTrim(String *string, char *specialCharacters);

void stringScanInput(String *string, FILE *dir);

void printString(String *string, FILE *dir);

struct Vector *stringSplit(String *string, char *splitCharacters);

void clearString(String *string);

void destroyString(void *myString);

#ifdef __cplusplus
}
#endif

#endif //C_DATASTRUCTURES_STRING_H
