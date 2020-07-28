#ifndef C_DATASTRUCTURES_STRING_H
#define C_DATASTRUCTURES_STRING_H

#ifdef __cplusplus
extern "C" {
#endif

typedef struct String {
    char *string;
    int count;
    int length;
} String;

String *stringInitialization(int initialLength);

void stringAddCharAtLast(String *myString, char c);

void stringAddCharAtIndex(String *myString, int index, char c);

void stringRemoveCharAtIndex(String *myString, int index);

void stringAddCharArrayAtLast(String *myString, char *charArr);

void stringAddStringAtLast(String *myString, String *newString);

void stringChangeStringByCharArray(String *string, char *newString);

void stringChangeStringByString(String *string, String *newString);

int stringFindCharIndex(String *myString, char c);

char stringGetCharAtIndex(String *myString, int index);

int stringSubString(String *myString, char *string);

char *stringToArrayOfCharacters(String *myString);

char *stringGetStringBetweenTwoIndices(String *myString, int startIndex, int endIndex);

int stringIsEqualsToCharArray(String *myString, char *string);

int stringIsEqualsToMyString(String *myString, String *string);

int stringGetLength(String *myString);

//void stringTrim(String *myString);

void stringTrimStartC(String *myString, char *specialCharacters);

void stringTrimStart(String *myString);

void stringTrimEndC(String *myString, char *specialCharacters);

void stringTrimEnd(String *myString);

void stringTrim(String *myString);

void stringTrimC(String *myString, char *specialCharacters);

void stringFGetS(String *myString);

void printString(String *string);

struct Vector *stringSplit(String *string, char *splitCharacters);

void clearString (String *string);

void destroyString(String *myString);

#ifdef __cplusplus
}
#endif

#endif //C_DATASTRUCTURES_STRING_H
