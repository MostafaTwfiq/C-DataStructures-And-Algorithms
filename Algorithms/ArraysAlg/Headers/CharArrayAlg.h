#ifndef C_DATASTRUCTURES_CHARARRAYALG_H
#define C_DATASTRUCTURES_CHARARRAYALG_H


int isSubString(const char *fString, int fLength, const char *sString, int sLength);

void charArrayReverseWords(char *charArr);

void charArrTrimStartC(char *charArr, char *specialCharacters);

void charArrTrimStart(char *charArr);

void charArrTrimEndC(char *charArr, char *specialCharacters);

void charArrTrimEnd(char *charArr);

void charArrTrim(char *charArr);

void charArrTrimC(char *charArr, char *specialCharacters);

int charArrContainsChar(char *charArr, char c);

void charArrRemoveCharacters(char *charArr, char *specialCharactersToRemove);

int isInteger(char *string);

int isFloatingPointNum(char *string);

int charArrSumASCII(char *ch);

int charArrHashFun(const void *ch);

char *generateCharPointerP(char *ch, int length);

char *generateCharPointerC(char c);

int isAlphabetC(char c);

int isAlphabetP(const char *c);

int charComparatorP(const void *c1, const void *c2);

int charComparator(char c1, char c2);

struct Vector *charArrSplitS(char *string, char *splitCharacters);

struct Vector *charArrSplitC(char *string, char *splitCharacters);

char mostRepeatedCharacter(char *string);

#endif //C_DATASTRUCTURES_CHARARRAYALG_H
