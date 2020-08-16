#include "../Headers/CharArrayAlg.h"
#include "../../../System/Utils.h"
#include "../../../DataStructure/Strings/Headers/String.h"
#include "../../../DataStructure/Lists/Headers/Vector.h"
#include "../Headers/ArraysAlg.h"
#include "../../../Unit Test/CuTest/CuTest.h"


int charArrAlgStrcmp(const void *c1, const void *c2) {
    return strcmp(c1, c2);
}


/** This function will take two chars arrays,
 * then it will check if the second string is a substring from the first string,
 * if it was the function will return one (1), other wise it will return zero (0).
 *
 * Time Complexity: O (n) and n is the length of the first char array.
 *
 * Space Complexity: O (1).
 *
 * @param fString the first char array pointer
 * @param fLength the length of the first char array (without the '\0' character)
 * @param sString the second char array pointer
 * @param sLength the length of the second char array (without the '\0' character)
 * @return it will return one if the second string is a substring of the first one, other wise it will return zero
 */

int isSubString(const char *fString, int fLength, const char *sString, int sLength) {

    if (fString == NULL) {
#ifdef C_DATASTRUCTURES_ERRORSTESTSTRUCT_H
        ERROR_TEST->errorCode = NULL_POINTER;
        return -1;
#else
        fprintf(stderr, NULL_POINTER_MESSAGE, "first passed char array", "sub string algorithm");
        exit(NULL_POINTER);
#endif

    } else if (sString == NULL) {
#ifdef C_DATASTRUCTURES_ERRORSTESTSTRUCT_H
        ERROR_TEST->errorCode = NULL_POINTER;
        return -1;
#else
        fprintf(stderr, NULL_POINTER_MESSAGE, "second passed char array", "sub string algorithm");
        exit(NULL_POINTER);
#endif

    } else if (fLength < 0) {
#ifdef C_DATASTRUCTURES_ERRORSTESTSTRUCT_H
        ERROR_TEST->errorCode = INVALID_ARG;
        return -1;
#else
        fprintf(stderr, INVALID_ARG_MESSAGE, "first passed char array length", "sub string algorithm");
        exit(INVALID_ARG);
#endif

    } else if (sLength < 0) {
#ifdef C_DATASTRUCTURES_ERRORSTESTSTRUCT_H
        ERROR_TEST->errorCode = INVALID_ARG;
        return -1;
#else
        fprintf(stderr, INVALID_ARG_MESSAGE, "second passed char array length", "sub string algorithm");
        exit(INVALID_ARG);
#endif
    }

    if (sLength == 0)
        return 1;

    for (int i = 0; i <= fLength - sLength; i++) {

        if (fString[i] != *sString)
            continue;

        for (int j = 0; j < sLength; j++) {
            if (fString[i + j] != sString[j])
                break;
            else if (j == sLength - 1 && fString[i + j] == sString[j])
                return 1;

        }

    }

    return 0;

}


/** This function will take a char array,
 * then it will reverse the char array words.
 *
 * ex: original char array: "one two three", after reversing: "three two one".
 *
 * @param charArr the char array pointer
 */

void charArrayReverseWords(char *charArr) {

    if (charArr == NULL) {

#ifdef C_DATASTRUCTURES_ERRORSTESTSTRUCT_H
        ERROR_TEST->errorCode = NULL_POINTER;
        return;
#else
        fprintf(stderr, NULL_POINTER_MESSAGE, "char array", "char array reverse words");
        exit(NULL_POINTER);
#endif

    }


    Vector *wordsVector = vectorInitialization(5, destroyString, NULL);
    vectorAdd(wordsVector, stringInitialization(5));
    char *charArrStartPointer = charArr;

    while (*charArr != '\0') {

        if (*charArr == ' ') {

            while (*(charArr + 1) == ' ')
                charArr++;

            if (stringGetLength(vectorGet(wordsVector, vectorGetLength(wordsVector) - 1)) != 0)
                vectorAdd(wordsVector, stringInitialization(5));

        } else
            stringAppendChar((String *) vectorGet(wordsVector, vectorGetLength(wordsVector) - 1), *charArr);


        charArr++;

    }

    for (int i = vectorGetLength(wordsVector) - 1; i >= 0; i--) {

        String *currentWord = vectorGet(wordsVector, i);

        for (int j = 0; j < stringGetLength(currentWord); j++)
            *charArrStartPointer++ = stringGet(currentWord, j);

        if (i != 0 && stringGetLength(currentWord) != 0)
            *charArrStartPointer++ = ' ';
        else
            *charArrStartPointer = '\0';

    }

    destroyVector(wordsVector);

}


/** This function will take an char array,
 * then it will removes characters specified in the second array of characters parameter,
 * from the beginning of a first array of characters parameter.
 *
 * ex of specialCharacters array: " \t\n", the function will remove any ' ', '\t', and '\n' characters from the beginning.
 *
 * @param charArr the characters array pointer
 * @param specialCharacters the special characters array pointer
 */

void charArrTrimStartC(char *charArr, char *specialCharacters) {

    if (charArr == NULL) {
#ifdef C_DATASTRUCTURES_ERRORSTESTSTRUCT_H
        ERROR_TEST->errorCode = NULL_POINTER;
        return;
#else
        fprintf(stderr, NULL_POINTER_MESSAGE, "char array", "char array custom trim start");
        exit(NULL_POINTER);
#endif

    } else if (specialCharacters == NULL) {
#ifdef C_DATASTRUCTURES_ERRORSTESTSTRUCT_H
        ERROR_TEST->errorCode = INVALID_ARG;
        return;
#else
        fprintf(stderr, INVALID_ARG_MESSAGE, "special character array", "char array custom trim start");
        exit(INVALID_ARG);
#endif
    }

    while (*charArr != '\0') {

        if (charArrContainsChar(specialCharacters, *charArr)) {
            char *tempPointer = charArr;

            do {
                *tempPointer = *(tempPointer + 1);
            } while (*tempPointer++ != '\0');

        } else
            break;

    }


}


/** This function will take an char array,
 * then it will remove ' ', '\t' and '\n' characters,
 * from the beginning of the array of characters.
 *
 *
 * @param charArr the characters array pointer
 */

void charArrTrimStart(char *charArr) {

    if (charArr == NULL) {
#ifdef C_DATASTRUCTURES_ERRORSTESTSTRUCT_H
        ERROR_TEST->errorCode = NULL_POINTER;
        return;
#else
        fprintf(stderr, NULL_POINTER_MESSAGE, "char array", "char array trim start");
        exit(NULL_POINTER);
#endif

    }

    charArrTrimStartC(charArr, " \n\t");
}


/** This function will take an char array,
 * then it will removes characters specified in the second array of characters parameter,
 * from the end of the first array of characters parameter.
 *
 * ex of specialCharacters array: " \t\n", the function will remove any ' ', '\t', and '\n' characters from the end.
 *
 * @param charArr the characters array pointer
 * @param specialCharacters the special characters array pointer
 */

void charArrTrimEndC(char *charArr, char *specialCharacters) {

    if (charArr == NULL) {
#ifdef C_DATASTRUCTURES_ERRORSTESTSTRUCT_H
        ERROR_TEST->errorCode = NULL_POINTER;
        return;
#else
        fprintf(stderr, NULL_POINTER_MESSAGE, "char array", "char array custom trim end");
        exit(NULL_POINTER);
#endif

    } else if (specialCharacters == NULL) {
#ifdef C_DATASTRUCTURES_ERRORSTESTSTRUCT_H
        ERROR_TEST->errorCode = INVALID_ARG;
        return;
#else
        fprintf(stderr, INVALID_ARG_MESSAGE, "special character array", "char array custom trim end");
        exit(INVALID_ARG);
#endif
    }

    char *startPointer = charArr;

    while (*charArr != '\0')
        charArr++;

    while (startPointer - sizeof(char) != --charArr && charArrContainsChar(specialCharacters, *charArr))
        *charArr = '\0';

}


/** This function will take an char array,
 * then it will remove ' ', '\t' and '\n' characters,
 * from the end of the array of characters.
 *
 *
 * @param charArr the characters array pointer
 */

void charArrTrimEnd(char *charArr) {

    if (charArr == NULL) {
#ifdef C_DATASTRUCTURES_ERRORSTESTSTRUCT_H
        ERROR_TEST->errorCode = NULL_POINTER;
        return;
#else
        fprintf(stderr, NULL_POINTER_MESSAGE, "char array", "char array trim end");
        exit(NULL_POINTER);
#endif

    }

    charArrTrimEndC(charArr, " \n\t");
}


/** This function will take an char array,
 * then it will remove ' ', '\t' and '\n' characters,
 * from the beginning and the end of the array of characters.
 *
 *
 * @param charArr the characters array pointer
 */

void charArrTrim(char *charArr) {

    if (charArr == NULL) {
#ifdef C_DATASTRUCTURES_ERRORSTESTSTRUCT_H
        ERROR_TEST->errorCode = NULL_POINTER;
        return;
#else
        fprintf(stderr, NULL_POINTER_MESSAGE, "char array", "char array trim");
        exit(NULL_POINTER);
#endif

    }

    charArrTrimStartC(charArr, " \n\t");
    charArrTrimEndC(charArr, " \n\t");

}


/** This function will take an char array,
 * then it will removes characters specified in the second array of characters parameter,
 * from the beginning and the end of the first array of characters parameter.
 *
 * ex of specialCharacters array: " \t\n", the function will remove any ' ', '\t', and '\n' characters from the beginning and the end.
 *
 * @param charArr the characters array pointer
 * @param specialCharacters the special characters array pointer
 */

void charArrTrimC(char *charArr, char *specialCharacters) {

    if (charArr == NULL) {
#ifdef C_DATASTRUCTURES_ERRORSTESTSTRUCT_H
        ERROR_TEST->errorCode = NULL_POINTER;
        return;
#else
        fprintf(stderr, NULL_POINTER_MESSAGE, "char array", "char array custom trim");
        exit(NULL_POINTER);
#endif

    } else if (specialCharacters == NULL) {
#ifdef C_DATASTRUCTURES_ERRORSTESTSTRUCT_H
        ERROR_TEST->errorCode = INVALID_ARG;
        return;
#else
        fprintf(stderr, INVALID_ARG_MESSAGE, "special character array", "char array custom trim");
        exit(INVALID_ARG);
#endif
    }

    charArrTrimStartC(charArr, specialCharacters);
    charArrTrimEndC(charArr, specialCharacters);

}


/** This function will return one (1) if the passed characters is a part of the passed character array,
 * other wise if will return zero (0).
 *
 * @param charArr the char array pointer
 * @param c the character value, that the function will search for
 * @return it will return one if the character value exist in the char array, other wise it will return zero
 */

int charArrContainsChar(char *charArr, char c) {

    if (charArr == NULL) {
#ifdef C_DATASTRUCTURES_ERRORSTESTSTRUCT_H
        ERROR_TEST->errorCode = NULL_POINTER;
        return -1;
#else
        fprintf(stderr, NULL_POINTER_MESSAGE, "char array", "char array contains char");
        exit(NULL_POINTER);
#endif

    }

    while (*charArr != '\0') {
        if (*charArr++ == c)
            return 1;

    }

    return 0;

}


/** This function will take an array of characters,
 * and a special characters array, then it will remove every special character from the first passed char array.
 *
 * ex of specialCharacters array: " \t\n", the function will remove any ' ', '\t', ' ' character from the char array.
 *
 * @param charArr the char array pointer
 * @param specialCharactersToRemove the special characters array pointer
 */

void charArrRemoveCharacters(char *charArr, char *specialCharactersToRemove) {

    if (charArr == NULL) {
#ifdef C_DATASTRUCTURES_ERRORSTESTSTRUCT_H
        ERROR_TEST->errorCode = NULL_POINTER;
        return;
#else
        fprintf(stderr, NULL_POINTER_MESSAGE, "char array", "char array remove character");
        exit(NULL_POINTER);
#endif

    } else if (specialCharactersToRemove == NULL) {
#ifdef C_DATASTRUCTURES_ERRORSTESTSTRUCT_H
        ERROR_TEST->errorCode = INVALID_ARG;
        return;
#else
        fprintf(stderr, INVALID_ARG_MESSAGE, "special character to remove array", "char array remove character");
        exit(INVALID_ARG);
#endif
    }

    while (*charArr != '\0') {
        if (charArrContainsChar(specialCharactersToRemove, *charArr)) {

            char *tempPointer = charArr;

            do {
                *tempPointer = *(tempPointer + 1);
            } while (*tempPointer++ != '\0');

        } else
            charArr++;

    }

}


/** This function will take a char array,
 * then it will check if the array is an integer number,
 * and if it was the function will return one (1), other wise it will return zero (0).
 *
 * @param string the char array pointer
 * @return it will return one if the char array is integer other wise it will return zero
 */

int isInteger(char *string) {

    if (string == NULL) {
#ifdef C_DATASTRUCTURES_ERRORSTESTSTRUCT_H
        ERROR_TEST->errorCode = NULL_POINTER;
        return -1;
#else
        fprintf(stderr, NULL_POINTER_MESSAGE, "passed char array", "isInteger function");
        exit(NULL_POINTER);
#endif
    }


    if (*string == '\0')
        return 0;


    char *tempPointer = string;

    while (*tempPointer != '\0') {
        if (tempPointer == string && (*tempPointer == '-' || *tempPointer == '+')) {
            tempPointer++;
            continue;
        } else if (!(*tempPointer >= '0' && *tempPointer <= '9'))
            return 0;

        tempPointer++;

    }

    return 1;

}


/** This function will check if the passed char array is a floating point number,
 * then it will return one (1), if it was a valid floating point number, other wise it will return zero (0).
 *
 * @param string the char array pointer
 * @return
 */

int isFloatingPointNum(char *string) {

    if (string == NULL) {
#ifdef C_DATASTRUCTURES_ERRORSTESTSTRUCT_H
        ERROR_TEST->errorCode = NULL_POINTER;
        return -1;
#else
        fprintf(stderr, NULL_POINTER_MESSAGE, "passed char array", "isFloatingPointNum function");
        exit(NULL_POINTER);
#endif
    }


    if (*string == '\0')
        return 0;


    short dotFlag = 0;

    char *tempPointer = string;

    while (*tempPointer != '\0') {

        if (tempPointer == string && (*tempPointer == '-' || *tempPointer == '+')) {
            tempPointer++;
            continue;
        } else if (*tempPointer == '.') {

            if (dotFlag == 0)
                dotFlag = 1;
            else
                return 0;

        } else if (!(*tempPointer >= '0' && *tempPointer <= '9'))
            return 0;

        tempPointer++;

    }

    return 1;

}


/** This function will take an char array pointer,
 * then it will return the sum of the ASCII value of the array characters.
 *
 * @param ch the char array pointer
 * @return it will return the sum of the ASCII value of the array characters.
 */

int charArrSumASCII(char *ch) {

    if (ch == NULL) {
#ifdef C_DATASTRUCTURES_ERRORSTESTSTRUCT_H
        ERROR_TEST->errorCode = NULL_POINTER;
        return -1;
#else
        fprintf(stderr, NULL_POINTER_MESSAGE, "char array", "char array sum ASCII");
        exit(NULL_POINTER);
#endif
    }

    int ASCIISum = 0;
    while (*ch != '\0')
        ASCIISum += *ch++;

    return ASCIISum;

}


/** This function will take an char array pointer,
 * then it will return the sum of the ASCII value of the array characters.
 *
 * Note: this function will be useful to use in the hash set and hash map data structures.
 *
 * @param ch the char array pointer
 * @return it will return the sum of the ASCII value of the array characters.
 */

int charArrHashFun(const void *ch) {
    return charArrSumASCII((char *) ch);
}


/** This function will take a char array
 * then it will allocate a new one and copy the original char array into the new one,
 * and finally return the new allocated char array.
 *
 * @param ch the char array pointer
 * @param length the length of the char array
 * @return it will return the new allocated char array pointer
 */

char *generateCharPointerP(char *ch, int length) {

    if (ch == NULL) {
#ifdef C_DATASTRUCTURES_ERRORSTESTSTRUCT_H
        ERROR_TEST->errorCode = NULL_POINTER;
        return NULL;
#else
        fprintf(stderr, NULL_POINTER_MESSAGE, "char array", "generate char pointer function");
        exit(NULL_POINTER);
#endif
    } else if (length < 0) {
#ifdef C_DATASTRUCTURES_ERRORSTESTSTRUCT_H
        ERROR_TEST->errorCode = INVALID_ARG;
        return NULL;
#else
        fprintf(stderr, INVALID_ARG_MESSAGE, "char array length", "generate char pointer function");
        exit(INVALID_ARG);
#endif
    }

    char *newCh = (char *) malloc(sizeof(char) * (length + 1));
    if (newCh == NULL) {
        fprintf(stderr, FAILED_ALLOCATION_MESSAGE, "new char pointer", "generate char pointer function");
        exit(FAILED_ALLOCATION);
    }

    strcpy(newCh, ch);

    return newCh;

}


/** this function will allocate a new char array pointer,
 * the assign it's value with the passed char.
 *
 * @param c the char value
 * @return it will return the new allocated char array
 */

char *generateCharPointerC(char c) {

    char *newCh = (char *) malloc(sizeof(char) * 2);
    if (newCh == NULL) {
#ifdef C_DATASTRUCTURES_ERRORSTESTSTRUCT_H
        ERROR_TEST->errorCode = NULL_POINTER;
        return NULL;
#else
        fprintf(stderr, FAILED_ALLOCATION_MESSAGE, "new char pointer", "generate char pointer function");
        exit(FAILED_ALLOCATION);
#endif
    }

    *newCh = c;
    *(newCh + 1) = '\0';

    return newCh;

}


/** This function will take a character,
 * then it will return one (1) if the character is an alphabet, other wise it will return zero (0).
 * @param c the char value
 * @return it will return one if the character is an alphabet, other wise it will return zero.
 */

int isAlphabetC(char c) {
    return (c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z');
}


/** This function will take a character pointer,
 * then it will return one (1) if the pointer value is an alphabet, other wise it will return zero (0).
 *
 * @param c the char value
 * @return it will return one if the pointer value is an alphabet, other wise it will return zero.
 */

int isAlphabetP(const char *c) {

    if (c == NULL) {
#ifdef C_DATASTRUCTURES_ERRORSTESTSTRUCT_H
        ERROR_TEST->errorCode = NULL_POINTER;
        return -1;
#else
        fprintf(stderr, NULL_POINTER_MESSAGE, "character", "is alphabet function");
        exit(NULL_POINTER);
#endif
    }


    return (*c >= 'a' && *c <= 'z') || (*c >= 'A' && *c <= 'Z');

}


/**  This function will take two characters pointers,
 * then it will compare the two characters.
 *
 * The function will return negative number if the first character is bigger in ASCII,
 * zero if they are equal, and positive number of the first character bigger.
 *
 * @param c1 the first character pointer
 * @param c2 te second character pointer
 * @return it will return negative number if the first character is bigger in ASCII, zero if they are equal, and positive number of the first character bigger
 */

int charComparatorP(const void *c1, const void *c2) {
    return *(char *) c1 - *(char *) c2;
}


/** This function will take two characters,
 * then it will compare the two characters.
 *
 * The function will return negative number if the first character is bigger in ASCII,
 * zero if they are equal, and positive number of the first character bigger.
 *
 * @param c1 the first character value
 * @param c2 the second character value
 * @return it will return negative number if the first character is bigger in ASCII, zero if they are equal, and positive number of the first character bigger
 */

int charComparator(char c1, char c2) {
    return c1 - c2;
}


/** This function will take a char array,
 * then it will split it by the passed split characters array.
 *
 * ex of split characters array: " \t\n", the function will split the string when ever it see ' ', '\t', or '\n' characters.
 *
 * @param string the char array pointer
 * @param splitCharacters the split characters array pointer
 * @return it will return a vector contains a strings after split
 */

Vector *charArrSplitS(char *string, char *splitCharacters) {

    if (string == NULL) {
#ifdef C_DATASTRUCTURES_ERRORSTESTSTRUCT_H
        ERROR_TEST->errorCode = NULL_POINTER;
        return NULL;
#else
        fprintf(stderr, NULL_POINTER_MESSAGE, "char array", "char array split function");
        exit(NULL_POINTER);
#endif
    } else if (splitCharacters == NULL) {
#ifdef C_DATASTRUCTURES_ERRORSTESTSTRUCT_H
        ERROR_TEST->errorCode = INVALID_ARG;
        return NULL;
#else
        fprintf(stderr, INVALID_ARG_MESSAGE, "split characters array", "char array split function");
        exit(INVALID_ARG);
#endif
    }


    Vector *wordsVector = vectorInitialization(5, destroyString, stringCompareS);
    vectorAdd(wordsVector, stringInitialization(5));

    while (*string != '\0') {

        if (charArrContainsChar(splitCharacters, *string)) {

            if (stringGetLength(vectorGet(wordsVector, vectorGetLength(wordsVector) - 1)) != 0)
                vectorAdd(wordsVector, stringInitialization(5));

        } else
            stringAppendChar(vectorGet(wordsVector, vectorGetLength(wordsVector) - 1), *string);

        string++;
    }

    if (stringGetLength(vectorGet(wordsVector, vectorGetLength(wordsVector) - 1)) == 0)
        vectorRemoveAtIndex(wordsVector, vectorGetLength(wordsVector) - 1);

    return wordsVector;

}


/** This function will take a char array,
 * then it will split it by the passed split characters array.
 *
 * ex of split characters array: " \t\n", the function will split the string when ever it see ' ', '\t', or '\n' characters.
 *
 * @param string the char array pointer
 * @param splitCharacters the split characters array pointer
 * @return it will return a vector contains a char arrays after split
 */

Vector *charArrSplitC(char *string, char *splitCharacters) {

    if (string == NULL) {
#ifdef C_DATASTRUCTURES_ERRORSTESTSTRUCT_H
        ERROR_TEST->errorCode = NULL_POINTER;
        return NULL;
#else
        fprintf(stderr, NULL_POINTER_MESSAGE, "char array", "char array split function");
        exit(NULL_POINTER);
#endif
    } else if (splitCharacters == NULL) {
#ifdef C_DATASTRUCTURES_ERRORSTESTSTRUCT_H
        ERROR_TEST->errorCode = INVALID_ARG;
        return NULL;
#else
        fprintf(stderr, INVALID_ARG_MESSAGE, "split characters array", "char array split function");
        exit(INVALID_ARG);
#endif
    }


    Vector *wordsVector = vectorInitialization(5, free, charArrAlgStrcmp);
    String *currentWord = stringInitialization(10);

    while (*string != '\0') {

        if (charArrContainsChar(splitCharacters, *string)) {

            if (stringGetLength(currentWord) != 0) {
                vectorAdd(wordsVector, stringToCharArray(currentWord));
                clearString(currentWord);
            }

        } else
            stringAppendChar(currentWord, *string);

        string++;

    }

    if (stringGetLength(currentWord) != 0)
        vectorAdd(wordsVector, stringToCharArray(currentWord));

    destroyString(currentWord);

    return wordsVector;

}


/** This function will take a char array,
 * then it will return the most repeated character.
 *
 * @param string the char array pointer
 * @return it will return the most repeated character
 */

char mostRepeatedCharacter(char *string) {

    if (string == NULL) {
#ifdef C_DATASTRUCTURES_ERRORSTESTSTRUCT_H
        ERROR_TEST->errorCode = NULL_POINTER;
        return '\0';
#else
        fprintf(stderr, NULL_POINTER_MESSAGE, "char array", "most repeated character function");
        exit(NULL_POINTER);
#endif
    }

    if (*string == '\0')
        return '\0';

    return *(char *) mostFrequentArrValueH(string, (int) strlen(string), sizeof(char), charComparatorP, charArrHashFun);

}


