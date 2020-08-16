#include "../Headers/String.h"
#include "../../../System/Utils.h"
#include "../../Lists/Headers/Vector.h"
#include "../../../Unit Test/CuTest/CuTest.h"


/** This function will take the initial length of the string as a parameter,
 * then it will initialize a new String pointer and return it.
 *
 * @param initialLength the string initial length
 * @return it will return the initialized string
 */

String *stringInitialization(int initialLength) {
    if (initialLength <= 0) {
#ifdef C_DATASTRUCTURES_ERRORSTESTSTRUCT_H
        ERROR_TEST->errorCode = INVALID_ARG;
        return NULL;
#else
        fprintf(stderr, INVALID_ARG_MESSAGE, "initial length", "string data structure");
        exit(INVALID_ARG);
#endif

    }

    String *myString = (String *) malloc(sizeof(String));
    if (myString == NULL) {
#ifdef C_DATASTRUCTURES_ERRORSTESTSTRUCT_H
        ERROR_TEST->errorCode = FAILED_ALLOCATION;
        return NULL;
#else
        fprintf(stderr, FAILED_ALLOCATION_MESSAGE, "string", "string data structure");
        exit(FAILED_ALLOCATION);
#endif

    }

    myString->string = (char *) malloc(sizeof(char) * (initialLength + 1));
    if (myString->string == NULL) {
#ifdef C_DATASTRUCTURES_ERRORSTESTSTRUCT_H
        ERROR_TEST->errorCode = FAILED_ALLOCATION;
        return NULL;
#else
        fprintf(stderr, FAILED_ALLOCATION_MESSAGE, "string array", "string data structure");
        exit(FAILED_ALLOCATION);
#endif

    }

    myString->string[0] = '\0';
    myString->count = 0;
    myString->length = initialLength;

    return myString;
}


/** This function will take the string address, and the new character as a parameter,
 * then it will put the new character in the end of the string.
 *
 * @param string the string address
 * @param c the new character
 */

void stringAppendChar(String *string, char c) {
    if (string == NULL) {
#ifdef C_DATASTRUCTURES_ERRORSTESTSTRUCT_H
        ERROR_TEST->errorCode = NULL_POINTER;
        return;
#else
        fprintf(stderr, NULL_POINTER_MESSAGE, "string", "string data structure");
        exit(NULL_POINTER);
#endif

    }

    if (string->count == string->length) {
        string->length *= 2;
        string->string = realloc(string->string, sizeof(char) * (string->length + 1));
        if (string->string == NULL) {
#ifdef C_DATASTRUCTURES_ERRORSTESTSTRUCT_H
            ERROR_TEST->errorCode = FAILED_REALLOCATION;
            return;
#else
            fprintf(stderr, FAILED_REALLOCATION_MESSAGE, "string array", "string data structure");
            exit(FAILED_REALLOCATION);
#endif

        }

    }

    string->string[string->count++] = c;
    string->string[string->count] = '\0';

}


/** This function will take the string address, index, and the new character as a parameters,
 * then it will put the new character in the given index.
 *
 * Note: if the index is out of the string range the program will terminate.
 *
 * @param string the string address
 * @param index the new character index
 * @param c the new character
 */

void stringAddChar(String *string, int index, char c) {
    if (string == NULL) {
#ifdef C_DATASTRUCTURES_ERRORSTESTSTRUCT_H
        ERROR_TEST->errorCode = NULL_POINTER;
        return;
#else
        fprintf(stderr, NULL_POINTER_MESSAGE, "string", "string data structure");
        exit(NULL_POINTER);
#endif

    } else if (string->count <= index || index < 0) {
#ifdef C_DATASTRUCTURES_ERRORSTESTSTRUCT_H
        ERROR_TEST->errorCode = OUT_OF_RANGE;
        return;
#else
        fprintf(stderr, OUT_OF_RANGE_MESSAGE, "string data structure");
        exit(OUT_OF_RANGE);
#endif

    }

    if (string->count == string->length) {

        string->length *= 2;
        string->string = (char *) realloc(string->string, sizeof(char) * (string->length + 1));

        if (string->string == NULL) {
#ifdef C_DATASTRUCTURES_ERRORSTESTSTRUCT_H
            ERROR_TEST->errorCode = FAILED_REALLOCATION;
            return;
#else
            fprintf(stderr, FAILED_REALLOCATION_MESSAGE, "string char array", "string data structure");
            exit(FAILED_REALLOCATION);
#endif

        }

    }

    for (int i = string->count++; i > index; i--)
        string->string[i] = string->string[i - 1];

    string->string[index] = c;
    string->string[string->count] = '\0';

}


/** This function will take the string address, index, and the a character as a parameters,
 * then it will update the character at the provided index with the new passed character.
 *
 * Note: if the index is out of the string range the program will terminate.
 *
 * @param string the string address
 * @param index the character index
 * @param c the new character
 */

void stringUpdateChar(String *string, int index, char c) {

    if (string == NULL) {
#ifdef C_DATASTRUCTURES_ERRORSTESTSTRUCT_H
        ERROR_TEST->errorCode = NULL_POINTER;
        return;
#else
        fprintf(stderr, NULL_POINTER_MESSAGE, "string", "string data structure");
        exit(NULL_POINTER);
#endif

    } else if (string->count <= index || index < 0) {
#ifdef C_DATASTRUCTURES_ERRORSTESTSTRUCT_H
        ERROR_TEST->errorCode = OUT_OF_RANGE;
        return;
#else
        fprintf(stderr, OUT_OF_RANGE_MESSAGE, "string data structure");
        exit(OUT_OF_RANGE);
#endif

    }

    string->string[index] = c;

}


/** This function will take the string address, and the index as a parameter,
 * then it will remove the character in the given index.
 * 
 * Note: if the index is out of the string range the program will terminate.
 * 
 * @param string the string address
 * @param index the index of the char that will be removed
 */

void stringRemove(String *string, int index) {
    if (string == NULL) {
#ifdef C_DATASTRUCTURES_ERRORSTESTSTRUCT_H
        ERROR_TEST->errorCode = NULL_POINTER;
        return;
#else
        fprintf(stderr, NULL_POINTER_MESSAGE, "string", "string data structure");
        exit(NULL_POINTER);
#endif

    } else if (string->count <= index || index < 0) {
#ifdef C_DATASTRUCTURES_ERRORSTESTSTRUCT_H
        ERROR_TEST->errorCode = OUT_OF_RANGE;
        return;
#else
        fprintf(stderr, OUT_OF_RANGE_MESSAGE, "string data structure");
        exit(OUT_OF_RANGE);
#endif

    }

    for (int i = index; i < string->count; i++)
        string->string[i] = string->string[i + 1];

    string->count--;

}


/** This function will take the string address, and the new char array pointer as a parameters,
 * then it will add the new array of characters at the end of the original string.
 * 
 * @param string the string address
 * @param charArr the char array address
 */

void stringAppendC(String *string, char *charArr) {
    if (string == NULL) {
#ifdef C_DATASTRUCTURES_ERRORSTESTSTRUCT_H
        ERROR_TEST->errorCode = NULL_POINTER;
        return;
#else
        fprintf(stderr, NULL_POINTER_MESSAGE, "string", "string data structure");
        exit(NULL_POINTER);
#endif

    } else if (charArr == NULL) {
#ifdef C_DATASTRUCTURES_ERRORSTESTSTRUCT_H
        ERROR_TEST->errorCode = INVALID_ARG;
        return;
#else
        fprintf(stderr, INVALID_ARG_MESSAGE, "char array pointer", "string data structure");
        exit(INVALID_ARG);
#endif

    }

    char *currentChar = charArr;
    while (*currentChar != '\0') {
        stringAppendChar(string, *currentChar);
        currentChar++;
    }

}


/** This function will take the string address, and the new string pointer array as a parameters,
 * then it will add the new string at the end of the original string.
 *
 * @param string the string address
 * @param newString the string pointer
 */

void stringAppendS(String *string, String *newString) {
    if (string == NULL) {
#ifdef C_DATASTRUCTURES_ERRORSTESTSTRUCT_H
        ERROR_TEST->errorCode = NULL_POINTER;
        return;
#else
        fprintf(stderr, NULL_POINTER_MESSAGE, "string", "string data structure");
        exit(NULL_POINTER);
#endif

    } else if (newString == NULL) {
#ifdef C_DATASTRUCTURES_ERRORSTESTSTRUCT_H
        ERROR_TEST->errorCode = INVALID_ARG;
        return;
#else
        fprintf(stderr, INVALID_ARG_MESSAGE, "string pointer", "string data structure");
        exit(INVALID_ARG);
#endif

    }

    char *currentChar = newString->string;
    while (*currentChar != '\0') {
        stringAppendChar(string, *currentChar);
        currentChar++;
    }

}


/** This function will take the string address, and the new char pointer array as a parameters,
 * then it will change the string to the new char pointer array.
 *
 * @param string the string address
 * @param newCharArr a char array address
 */

void stringChangeStringC(String *string, char *newCharArr) {
    if (string == NULL) {
#ifdef C_DATASTRUCTURES_ERRORSTESTSTRUCT_H
        ERROR_TEST->errorCode = NULL_POINTER;
        return;
#else
        fprintf(stderr, NULL_POINTER_MESSAGE, "string", "string data structure");
        exit(NULL_POINTER);
#endif

    } else if (newCharArr == NULL) {
#ifdef C_DATASTRUCTURES_ERRORSTESTSTRUCT_H
        ERROR_TEST->errorCode = INVALID_ARG;
        return;
#else
        fprintf(stderr, INVALID_ARG_MESSAGE, "new char array pointer", "string data structure");
        exit(INVALID_ARG);
#endif

    }

    string->count = 0;
    string->string[string->count] = '\0';

    while (*newCharArr != '\0')
        stringAppendChar(string, *newCharArr++);

}


/** This function will take string address, and the the new string address as a parameters,
 * then it will change the first string to the second string.
 *
 * @param string the string address
 * @param newString the new string address
 */

void stringChangeStringS(String *string, String *newString) {
    if (string == NULL) {
#ifdef C_DATASTRUCTURES_ERRORSTESTSTRUCT_H
        ERROR_TEST->errorCode = NULL_POINTER;
        return;
#else
        fprintf(stderr, NULL_POINTER_MESSAGE, "string", "string data structure");
        exit(NULL_POINTER);
#endif

    } else if (newString == NULL) {
#ifdef C_DATASTRUCTURES_ERRORSTESTSTRUCT_H
        ERROR_TEST->errorCode = INVALID_ARG;
        return;
#else
        fprintf(stderr, INVALID_ARG_MESSAGE, "new string pointer", "string data structure");
        exit(INVALID_ARG);
#endif

    }

    string->count = 0;
    string->string[string->count] = '\0';

    for (int i = 0; i < stringGetLength(newString); i++)
        stringAppendChar(string, stringGet(newString, i));


}


/** This function will take the string address, and the character as a parameters,
 * then it will return the first occur of this character in the string and will return it's index,
 * other wise it will return minus one (-1).
 *
 * @param string the string address
 * @param c the character value
 * @return it will return the first index of the provided character if found, other wise it will return -1
 */

int stringGetIndex(String *string, char c) {
    if (string == NULL) {
#ifdef C_DATASTRUCTURES_ERRORSTESTSTRUCT_H
        ERROR_TEST->errorCode = NULL_POINTER;
        return -1;
#else
        fprintf(stderr, NULL_POINTER_MESSAGE, "string", "string data structure");
        exit(NULL_POINTER);
#endif

    }

    for (int i = 0; i < string->count; i++) {
        if (string->string[i] == c)
            return i;

    }

    return -1;

}


/** This function will take the string address, and the index as a parameters,
 * then it will return the character at the given index.
 *
 * Note: if the index is out of the string range the program will terminate.
 *
 * @param string the string address
 * @param index the index of the wanted character
 * @return it will return the character at the provided index
 */

char stringGet(String *string, int index) {
    if (string == NULL) {
#ifdef C_DATASTRUCTURES_ERRORSTESTSTRUCT_H
        ERROR_TEST->errorCode = NULL_POINTER;
        return '\0';
#else
        fprintf(stderr, NULL_POINTER_MESSAGE, "string", "string data structure");
        exit(NULL_POINTER);
#endif

    } else if (string->count <= index || index < 0) {
#ifdef C_DATASTRUCTURES_ERRORSTESTSTRUCT_H
        ERROR_TEST->errorCode = OUT_OF_RANGE;
        return '\0';
#else
        fprintf(stderr, OUT_OF_RANGE_MESSAGE, "string data structure");
        exit(OUT_OF_RANGE);
#endif

    }

    return string->string[index];

}


/** This function will take the charArr address, and a char pointer array as a parameters,
 * then it will return one (1) if the second char array is a substring of the first charArr,
 * other wise it will return zero (0).
 *
 * @param string the string address
 * @param charArr a char array address
 * @return it will return one if the provided char array are a substring of the original charArr
 */

int stringSubStringC(String *string, char *charArr) {
    if (string == NULL) {
#ifdef C_DATASTRUCTURES_ERRORSTESTSTRUCT_H
        ERROR_TEST->errorCode = NULL_POINTER;
        return -1;
#else
        fprintf(stderr, NULL_POINTER_MESSAGE, "string", "string data structure");
        exit(NULL_POINTER);
#endif

    } else if (charArr == NULL) {
#ifdef C_DATASTRUCTURES_ERRORSTESTSTRUCT_H
        ERROR_TEST->errorCode = INVALID_ARG;
        return -1;
#else
        fprintf(stderr, INVALID_ARG_MESSAGE, "char array pointer", "string data structure");
        exit(INVALID_ARG);
#endif

    }

    char *stringPointer = string->string;

    while (*stringPointer != '\0') {

        if (*charArr == *stringPointer) {

            int counter = 0;
            while (charArr[counter] != '\0' && stringPointer[counter] != '\0') {

                if (charArr[counter] != stringPointer[counter])
                    break;
                else if (charArr[counter + 1] == '\0')
                    return 1;

                counter++;

            }

        }

        stringPointer++;

    }

    return 0;

}


/** This function will take a string address, and another string pointer as a parameters,
 * then it will return one (1) if the second string is a substring of the first string,
 * other wise it will return zero (0).
 *
 * @param string the string address
 * @param sString the second string pointer
 * @return it will return one if the provided string are a substring of the original string
 */

int stringSubStringS(String *string, String *sString) {
    if (string == NULL) {
#ifdef C_DATASTRUCTURES_ERRORSTESTSTRUCT_H
        ERROR_TEST->errorCode = NULL_POINTER;
        return -1;
#else
        fprintf(stderr, NULL_POINTER_MESSAGE, "string", "string data structure");
        exit(NULL_POINTER);
#endif

    } else if (sString == NULL) {
#ifdef C_DATASTRUCTURES_ERRORSTESTSTRUCT_H
        ERROR_TEST->errorCode = INVALID_ARG;
        return -1;
#else
        fprintf(stderr, INVALID_ARG_MESSAGE, "second string pointer", "string data structure");
        exit(INVALID_ARG);
#endif

    }

    char *stringPointer = string->string;
    char *secondStringPointer = sString->string;

    while (*stringPointer != '\0') {

        if (*secondStringPointer == *stringPointer) {

            int counter = 0;
            while (secondStringPointer[counter] != '\0' && stringPointer[counter] != '\0') {

                if (secondStringPointer[counter] != stringPointer[counter])
                    break;
                else if (secondStringPointer[counter + 1] == '\0')
                    return 1;

                counter++;

            }

        }

        stringPointer++;

    }

    return 0;

}


/** This function will take the string address as a parameter,
 * then it will convert it to a char pointer array, and return it.
 *
 * @param string the string address
 * @return it will return a pointer to char array that has the same string of string
 */

char *stringToCharArray(String *string) {
    if (string == NULL) {
#ifdef C_DATASTRUCTURES_ERRORSTESTSTRUCT_H
        ERROR_TEST->errorCode = NULL_POINTER;
        return NULL;
#else
        fprintf(stderr, NULL_POINTER_MESSAGE, "string", "string data structure");
        exit(NULL_POINTER);
#endif

    }

    char *arrayOfCharacters = (char *) malloc(sizeof(char) * (string->count + 1));
    if (arrayOfCharacters == NULL) {
#ifdef C_DATASTRUCTURES_ERRORSTESTSTRUCT_H
        ERROR_TEST->errorCode = FAILED_ALLOCATION;
        return NULL;
#else
        fprintf(stderr, FAILED_ALLOCATION_MESSAGE, "to array of characters", "string data structure");
        exit(FAILED_ALLOCATION);
#endif

    }

    for (int i = 0; i <= string->count; i++)
        arrayOfCharacters[i] = string->string[i];

    return arrayOfCharacters;
}


/** This method will take the string address, start index, and end index as a parameters,
 * then it will convert the string from the start index to the end index to a char pointer array, then return it.
 *
 * @param string the string address
 * @param startIndex the start index
 * @param endIndex the end index
 * @return it will return a pointer to character array, that has copy of the from the start index to the end index
 */

char *stringToCustomCharArray(String *string, int startIndex, int endIndex) {
    if (string == NULL) {
#ifdef C_DATASTRUCTURES_ERRORSTESTSTRUCT_H
        ERROR_TEST->errorCode = NULL_POINTER;
        return NULL;
#else
        fprintf(stderr, NULL_POINTER_MESSAGE, "string", "string data structure");
        exit(NULL_POINTER);
#endif

    }

    if (startIndex > endIndex
        || startIndex < 0 || startIndex >= string->count
        || endIndex < 0 || endIndex >= string->count) {

#ifdef C_DATASTRUCTURES_ERRORSTESTSTRUCT_H
        ERROR_TEST->errorCode = OUT_OF_RANGE;
        return NULL;
#else
        fprintf(stderr, OUT_OF_RANGE_MESSAGE, "string data structure");
        exit(OUT_OF_RANGE);
#endif

    }


    char *newCharArray = (char *) malloc(sizeof(char) * (endIndex - startIndex + 2));
    if (string == NULL) {
#ifdef C_DATASTRUCTURES_ERRORSTESTSTRUCT_H
        ERROR_TEST->errorCode = FAILED_ALLOCATION;
        return NULL;
#else
        fprintf(stderr, FAILED_ALLOCATION_MESSAGE, "string to custom char array", "string data structure");
        exit(FAILED_ALLOCATION);
#endif

    }

    newCharArray[endIndex - startIndex + 1] = '\0';
    for (int i = 0; i <= endIndex - startIndex; i++)
        newCharArray[i] = string->string[startIndex + i];

    return newCharArray;

}


/** This function will take the string address as a parameter,
 * then it will return the string length.
 *
 * @param string the string address
 * @return it will return the length of the string
 */

int stringGetLength(String *string) {
    if (string == NULL) {
#ifdef C_DATASTRUCTURES_ERRORSTESTSTRUCT_H
        ERROR_TEST->errorCode = NULL_POINTER;
        return -1;
#else
        fprintf(stderr, NULL_POINTER_MESSAGE, "string", "string data structure");
        exit(NULL_POINTER);
#endif

    }

    return string->count;
}


/** This function will take the charArr address, and a char pointer array as a parameters,
 * then it will return one (1) if the charArr is equal to the char array,
 * other wise it will return zero (0).
 *
 * @param string the string address
 * @param charArr a character array pointer
 * @return it will return one if the provided char array is equal to the charArr, other wise in will return zero
 */

int stringEqualsC(String *string, char *charArr) {
    if (string == NULL) {
#ifdef C_DATASTRUCTURES_ERRORSTESTSTRUCT_H
        ERROR_TEST->errorCode = NULL_POINTER;
        return -1;
#else
        fprintf(stderr, NULL_POINTER_MESSAGE, "string", "string data structure");
        exit(NULL_POINTER);
#endif

    } else if (charArr == NULL) {
#ifdef C_DATASTRUCTURES_ERRORSTESTSTRUCT_H
        ERROR_TEST->errorCode = INVALID_ARG;
        return -1;
#else
        fprintf(stderr, INVALID_ARG_MESSAGE, "char array pointer", "string data structure");
        exit(INVALID_ARG);
#endif

    }

    char *fS = string->string;
    char *sS = charArr;

    while (*fS != '\0' && *sS != '\0') {

        if (*fS != *sS)
            return 0;

        fS++;
        sS++;

    }

    return *fS == '\0' && *sS == '\0' ? 1 : 0;

}


/** This function will take the string address, and second string address as a parameters,
 * then it will return one (1) if the first string is equal to the second string,
 * other wise it will return zero (0).
 *
 * @param string the string address
 * @param sString the other sString address
 * @return it will return one if the second sString is equal to the original sString, other wise in will return zero
 */

int stringEqualsS(String *string, String *sString) {
    if (string == NULL) {
#ifdef C_DATASTRUCTURES_ERRORSTESTSTRUCT_H
        ERROR_TEST->errorCode = NULL_POINTER;
        return -1;
#else
        fprintf(stderr, NULL_POINTER_MESSAGE, "string", "string data structure");
        exit(NULL_POINTER);
#endif

    } else if (sString == NULL) {
#ifdef C_DATASTRUCTURES_ERRORSTESTSTRUCT_H
        ERROR_TEST->errorCode = INVALID_ARG;
        return -1;
#else
        fprintf(stderr, INVALID_ARG_MESSAGE, "second string pointer", "string data structure");
        exit(INVALID_ARG);
#endif

    }

    int stringLength = stringGetLength(sString);
    if (string->count != stringLength)
        return 0;

    for (int i = 0; i < stringLength; i++) {

        if (string->string[i] != sString->string[i])
            return 0;

    }

    return 1;

}


/** This function will take the string address, and a char pointer array as a parameters,
 * then it will compare them and it will return a zero if they are equal,
 * negative number if the second one is bigger, and positive number if the first is bigger.
 *
 * @param string the string address
 * @param charArr a character array pointer
 * @return it will return a zero if they are equal, negative number if the second one is bigger, and positive number if the first is bigger.
*/

int stringCompareC(String *string, char *charArr) {
    if (string == NULL) {
#ifdef C_DATASTRUCTURES_ERRORSTESTSTRUCT_H
        ERROR_TEST->errorCode = NULL_POINTER;
        return -1;
#else
        fprintf(stderr, NULL_POINTER_MESSAGE, "string", "string data structure");
        exit(NULL_POINTER);
#endif

    } else if (charArr == NULL) {
#ifdef C_DATASTRUCTURES_ERRORSTESTSTRUCT_H
        ERROR_TEST->errorCode = INVALID_ARG;
        return -1;
#else
        fprintf(stderr, INVALID_ARG_MESSAGE, "second char array pointer", "string data structure");
        exit(INVALID_ARG);
#endif

    }

    char *fS = string->string;
    char *sS = charArr;

    while (*fS != '\0' && *sS != '\0') {

        if (*fS != *sS)
            return *fS - *sS;

        fS++;
        sS++;

    }

    if (*fS == '\0' && *sS == '\0')
        return 0;

    return *fS == '\0' ? -1 * (int) *sS : (int) *fS;

}


/** This function will take the string address, and second string address as a parameters,
 * then it will compare the strings and it will return a zero if they are equal,
 * negative number if the second one is bigger, and positive number if the first is bigger.
 *
 * @param string the string address
 * @param sString the other string address
 * @return it will return a zero if they are equal, negative number if the second one is bigger, and positive number if the first is bigger.
*/

int stringCompareS(const void *string, const void *sString) {
    if (string == NULL) {
#ifdef C_DATASTRUCTURES_ERRORSTESTSTRUCT_H
        ERROR_TEST->errorCode = NULL_POINTER;
        return -1;
#else
        fprintf(stderr, NULL_POINTER_MESSAGE, "string", "string data structure");
        exit(NULL_POINTER);
#endif

    } else if (sString == NULL) {
#ifdef C_DATASTRUCTURES_ERRORSTESTSTRUCT_H
        ERROR_TEST->errorCode = INVALID_ARG;
        return -1;
#else
        fprintf(stderr, INVALID_ARG_MESSAGE, "second string pointer", "string data structure");
        exit(INVALID_ARG);
#endif

    }

    char *fS = ((String *) string)->string;
    char *sS = ((String *) sString)->string;

    while (*fS != '\0' && *sS != '\0') {

        if (*fS != *sS)
            return *fS - *sS;

        fS++;
        sS++;

    }

    if (*fS == '\0' && *sS == '\0')
        return 0;

    return *fS == '\0' ? -1 * (int) *sS : (int) *fS;

}


/** This function will return one (1) if the passed characters is a part of the passed character array,
 * other wise if will return zero (0).
 *
 * @param charArr the char array pointer
 * @param c the character value, that the function will search for
 * @return it will return one if the character value exist in the char array, other wise it will return zero
 */

int charArrContains(char *charArr, char c) {

    while (*charArr != '\0') {
        if (*charArr++ == c)
            return 1;

    }

    return 0;

}


/** This function will take string pointer,
 * then it will removes characters specified in the second array of characters parameter,
 * from the beginning of the string.
 *
 * ex of specialCharacters array:
 * " \t\n", the function will remove any ' ', '\t', and '\n' characters from the beginning.
 *
 * @param string the string pointer
 * @param specialCharacters the special characters array pointer
 */

void stringCustomTrimStart(String *string, char *specialCharacters) {

    if (string == NULL) {
#ifdef C_DATASTRUCTURES_ERRORSTESTSTRUCT_H
        ERROR_TEST->errorCode = NULL_POINTER;
        return;
#else
        fprintf(stderr, NULL_POINTER_MESSAGE, "string", "string data structure");
        exit(NULL_POINTER);
#endif

    } else if (specialCharacters == NULL) {
#ifdef C_DATASTRUCTURES_ERRORSTESTSTRUCT_H
        ERROR_TEST->errorCode = INVALID_ARG;
        return;
#else
        fprintf(stderr, INVALID_ARG_MESSAGE, "special characters array", "string data structure");
        exit(INVALID_ARG);
#endif
    }

    char *charArr = string->string;
    while (*charArr != '\0') {

        if (charArrContains(specialCharacters, *charArr)) {
            char *tempPointer = charArr;

            do {
                *tempPointer = *(tempPointer + 1);
            } while (*tempPointer++ != '\0');

            string->count--;

        } else
            break;

    }


}


/** This function will take string pointer,
 * then it will remove ' ', '\t' and '\n' characters,
 * from the beginning of the string.
 *
 * @param string the string pointer
 */

void stringTrimStart(String *string) {

    if (string == NULL) {
#ifdef C_DATASTRUCTURES_ERRORSTESTSTRUCT_H
        ERROR_TEST->errorCode = NULL_POINTER;
        return;
#else
        fprintf(stderr, NULL_POINTER_MESSAGE, "string", "string data structure");
        exit(NULL_POINTER);
#endif
    }

    stringCustomTrimStart(string, " \n\t");

}


/** This function will take string pointer,
 * then it will removes characters specified in the second array of characters parameter,
 * from the end of the string.
 *
 * ex of specialCharacters array:
 * " \t\n", the function will remove any ' ', '\t', and '\n' characters from the end.
 *
 * @param string the string pointer
 * @param specialCharacters the special characters array pointer
 */

void stringCustomTrimEnd(String *string, char *specialCharacters) {

    if (string == NULL) {
#ifdef C_DATASTRUCTURES_ERRORSTESTSTRUCT_H
        ERROR_TEST->errorCode = NULL_POINTER;
        return;
#else
        fprintf(stderr, NULL_POINTER_MESSAGE, "string", "string data structure");
        exit(NULL_POINTER);
#endif

    } else if (specialCharacters == NULL) {
#ifdef C_DATASTRUCTURES_ERRORSTESTSTRUCT_H
        ERROR_TEST->errorCode = INVALID_ARG;
        return;
#else
        fprintf(stderr, INVALID_ARG_MESSAGE, "special characters array", "string data structure");
        exit(INVALID_ARG);
#endif
    }

    char *charArr = string->string;
    char *startPointer = string->string;

    while (*charArr != '\0')
        charArr++;

    while (startPointer - sizeof(char) != --charArr && charArrContains(specialCharacters, *charArr)) {
        *charArr = '\0';
        string->count--;
    }

}


/** This function will take string pointer,
 * then it will remove ' ', '\t' and '\n' characters,
 * from the end of the string.
 *
 *
 * @param string the string pointer
 */

void stringTrimEnd(String *string) {

    if (string == NULL) {
#ifdef C_DATASTRUCTURES_ERRORSTESTSTRUCT_H
        ERROR_TEST->errorCode = NULL_POINTER;
        return;
#else
        fprintf(stderr, NULL_POINTER_MESSAGE, "string", "string data structure");
        exit(NULL_POINTER);
#endif
    }

    stringCustomTrimEnd(string, " \n\t");

}


/** This function will take string pointer,
 * then it will remove ' ', '\t' and '\n' characters,
 * from the beginning and the end of the string.
 *
 *
 * @param myString the string pointer
 */

void stringTrim(String *myString) {

    if (myString == NULL) {
#ifdef C_DATASTRUCTURES_ERRORSTESTSTRUCT_H
        ERROR_TEST->errorCode = NULL_POINTER;
        return;
#else
        fprintf(stderr, NULL_POINTER_MESSAGE, "string", "string data structure");
        exit(NULL_POINTER);
#endif
    }

    stringCustomTrimStart(myString, " \n\t");
    stringCustomTrimEnd(myString, " \n\t");

}


/** This function will take string pointer,
 * then it will removes characters specified in the second array of characters parameter,
 * from the beginning and the end of the string.
 *
 * ex of specialCharacters array:
 * " \t\n", the function will remove any ' ', '\t', and '\n' characters from the beginning and the end.
 *
 * @param string the string pointer
 * @param specialCharacters the special characters array pointer
 */

void stringCustomTrim(String *string, char *specialCharacters) {

    if (string == NULL) {
#ifdef C_DATASTRUCTURES_ERRORSTESTSTRUCT_H
        ERROR_TEST->errorCode = NULL_POINTER;
        return;
#else
        fprintf(stderr, NULL_POINTER_MESSAGE, "string", "string data structure");
        exit(NULL_POINTER);
#endif
    } else if (specialCharacters == NULL) {
#ifdef C_DATASTRUCTURES_ERRORSTESTSTRUCT_H
        ERROR_TEST->errorCode = INVALID_ARG;
        return;
#else
        fprintf(stderr, INVALID_ARG_MESSAGE, "special characters array", "string data structure");
        exit(INVALID_ARG);
#endif
    }

    stringCustomTrimStart(string, specialCharacters);
    stringCustomTrimEnd(string, specialCharacters);

}


/** This function will take the string address as a parameter,
 * then it will read the input from the passed file and put it in the string.
 *
 * @param string the string address
 * @param dir the file pointer the the function will scan the input from it
 */

void stringScanInput(String *string, FILE *dir) {
    if (string == NULL) {
#ifdef C_DATASTRUCTURES_ERRORSTESTSTRUCT_H
        ERROR_TEST->errorCode = NULL_POINTER;
        return;
#else
        fprintf(stderr, NULL_POINTER_MESSAGE, "string", "string data structure");
        exit(NULL_POINTER);
#endif

    } else if (dir == NULL) {
#ifdef C_DATASTRUCTURES_ERRORSTESTSTRUCT_H
        ERROR_TEST->errorCode = INVALID_ARG;
        return;
#else
        fprintf(stderr, INVALID_ARG_MESSAGE, "file pointer", "string data structure");
        exit(INVALID_ARG);
#endif

    }

    char c;

    while (1) {
        c = fgetc(dir);

        if (c == '\n' || c == EOF)
            break;

        stringAppendChar(string, c);
    }

    if (string->string[string->count - 1] == '\r')
        stringRemove(string, string->count - 1);

    fseek(dir, 0, SEEK_END);

}


/** This function will take the string address as a parameter,
 * then it will print the string in the stdout file.
 *
 * @param string the string address
 * @param dir the file pointer that the function will print the string in it
 */

void printString(String *string, FILE *dir) {

    if (string == NULL) {
#ifdef C_DATASTRUCTURES_ERRORSTESTSTRUCT_H
        ERROR_TEST->errorCode = NULL_POINTER;
        return;
#else
        fprintf(stderr, NULL_POINTER_MESSAGE, "string", "string data structure");
        exit(NULL_POINTER);
#endif

    } else if (dir == NULL) {
#ifdef C_DATASTRUCTURES_ERRORSTESTSTRUCT_H
        ERROR_TEST->errorCode = INVALID_ARG;
        return;
#else
        fprintf(stderr, INVALID_ARG_MESSAGE, "file pointer", "string data structure");
        exit(INVALID_ARG);
#endif

    }

    fprintf(dir, "%s", string->string);

}


/** This function will take a string,
 * then it will split it by the passed split characters array.
 *
 * ex of split characters array:
 * " \t\n", the function will split the string when ever it see ' ', '\t', or '\n' characters.
 *
 * @param string the string pointer
 * @param splitCharacters the split characters array pointer
 * @return it will return a vector contains the strings after split
 */

Vector *stringSplit(String *string, char *splitCharacters) {

    if (string == NULL) {
#ifdef C_DATASTRUCTURES_ERRORSTESTSTRUCT_H
        ERROR_TEST->errorCode = NULL_POINTER;
        return NULL;
#else
        fprintf(stderr, NULL_POINTER_MESSAGE, "string", "string data structure");
        exit(NULL_POINTER);
#endif

    } else if (splitCharacters == NULL) {
#ifdef C_DATASTRUCTURES_ERRORSTESTSTRUCT_H
        ERROR_TEST->errorCode = INVALID_ARG;
        return NULL;
#else
        fprintf(stderr, INVALID_ARG_MESSAGE, "split characters array", "string data structure");
        exit(INVALID_ARG);
#endif
    }


    Vector *stringsVector = vectorInitialization(5, destroyString, stringCompareS);
    vectorAdd(stringsVector, stringInitialization(5));

    for (int i = 0; i < stringGetLength(string); i++) {

        if (charArrContains(splitCharacters, stringGet(string, i))) {

            if (stringGetLength(vectorGet(stringsVector, vectorGetLength(stringsVector) - 1)) != 0)
                vectorAdd(stringsVector, stringInitialization(5));

            continue;
        }

        stringAppendChar(vectorGet(stringsVector, vectorGetLength(stringsVector) - 1), stringGet(string, i));

    }

    return stringsVector;

}


/** This function will clear the string.
 *
 * @param string the string pointer
 */

void clearString(String *string) {

    if (string == NULL) {
#ifdef C_DATASTRUCTURES_ERRORSTESTSTRUCT_H
        ERROR_TEST->errorCode = NULL_POINTER;
        return;
#else
        fprintf(stderr, NULL_POINTER_MESSAGE, "string", "string data structure");
        exit(NULL_POINTER);
#endif

    }

    string->count = 0;
    string->string[string->count] = '\0';

}


/** This function will take the string address as a parameter,
 * then it will destroy and free the string from the memory.
 *
 * @param myString the string address
 */

void destroyString(void *myString) {
    if (myString == NULL) {
#ifdef C_DATASTRUCTURES_ERRORSTESTSTRUCT_H
        ERROR_TEST->errorCode = NULL_POINTER;
        return;
#else
        fprintf(stderr, NULL_POINTER_MESSAGE, "string", "string data structure");
        exit(NULL_POINTER);
#endif

    }

    free(((String *) myString)->string);
    free(myString);

}