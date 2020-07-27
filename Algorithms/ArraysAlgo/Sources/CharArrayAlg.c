#include "../Headers/CharArrayAlg.h"
#include "../../../System/Utils.h"
#include "../../../DataStructure/Strings/Headers/String.h"
#include "../../../DataStructure/Lists/Headers/Vector.h"









/** This function will take two chars arrays,
 * then it will check if the second string is a substring from the first string,
 * if it was the function will return one (1), other wise it will return zero (0).
 *
 * Time Complexity: O (n) and n is the length of the first char array.
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
        fprintf(stderr, NULL_POINTER_MESSAGE, "first passed char array", "sub string algorithm");
        exit(NULL_POINTER);
    } else if (sString == NULL) {
        fprintf(stderr, NULL_POINTER_MESSAGE, "second passed char array", "sub string algorithm");
        exit(NULL_POINTER);
    } else if (fLength < 0) {
        fprintf(stderr, INVALID_ARG_MESSAGE, "first passed char array length", "sub string algorithm");
        exit(INVALID_ARG);
    } else if (sLength < 0) {
        fprintf(stderr, INVALID_ARG_MESSAGE, "second passed char array length", "sub string algorithm");
        exit(INVALID_ARG);
    }

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

    Vector *wordsVector = vectorInitialization(5, destroyString, NULL);
    char *charArrStartPointer = charArr;
    int wordsCounter = 0;

    while (*charArr != '\0') {
        if (vectorIsEmpty(wordsVector) || vectorGet(wordsVector, wordsCounter) == NULL)
            vectorAdd(wordsVector, stringInitialization(5));

        if (*charArr == ' ') {
            wordsCounter++;
            vectorAdd(wordsVector, stringInitialization(5));
            while (*(charArr + 1) == ' ')
                charArr++;

        }
        else
            stringAddCharAtLast( (String *) vectorGet(wordsVector, wordsCounter), *charArr);

        charArr++;

    }

    for (int i = vectorGetLength(wordsVector) - 1; i >= 0; i--) {

        String *currentWord = vectorGet(wordsVector, i);

        for (int j = 0; j < stringGetLength(currentWord); j++)
            *charArrStartPointer++ = stringGetCharAtIndex(currentWord, j);

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

    char *startPointer = charArr;

    while (*charArr != '\0')
        charArr++;

    while ( startPointer - sizeof(char) != --charArr && charArrContainsChar(specialCharacters, *charArr) )
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
    charArrTrimStartC(charArr, specialCharacters);
    charArrTrimEndC(charArr, specialCharacters);
}









/** This function will return one (1) if the passed characters is a part of the passed character array,
 * other wise if will return zero (0).
 * @param charArr the char array pointer
 * @param c the character value, that the function will search for
 * @return it will return one if the character value exist in the char array, other wise it will return zero
 */

int charArrContainsChar(char *charArr, char c) {

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
 * @param string the char array pointer
 * @param length the length of the char array
 * @return it will return one if the char array is integer other wise it will return zero
 */

int isInteger(const char *string, int length) {

    if (string == NULL) {
        fprintf(stderr, NULL_POINTER_MESSAGE, "passed char array", "isInteger function");
        exit(NULL_POINTER);
    } else if (length < 0) {
        fprintf(stderr, INVALID_ARG_MESSAGE, "passed char array length", "isInteger algorithm");
        exit(INVALID_ARG);
    }

    for (int i = 0; i < length; i++) {
        if ( i == 0 && ( string[i] == '-' || string[i] == '+' ) )
            continue;
        else if ( !(string[i] >= '0' && string[i] <= '9') )
            return 0;

    }

    return 1;

}








/** This function will check if the passed char array is a floating point number,
 * then it will return one (1), if it was a valid floating point number, other wise it will return zero (0).
 * @param string the char array pointer
 * @param length the length if the char array
 * @return
 */

int isFloatingPointNum(const char *string, int length) {

    if (string == NULL) {
        fprintf(stderr, NULL_POINTER_MESSAGE, "passed char array", "isFloatingPointNum function");
        exit(NULL_POINTER);
    } else if (length < 0) {
        fprintf(stderr, INVALID_ARG_MESSAGE, "passed char array length", "isFloatingPointNum algorithm");
        exit(INVALID_ARG);
    }

    short dotFlag = 0;

    for (int i = 0; i < length; i++) {

        if ( i == 0 && ( string[i] == '-' || string[i] == '+' ) )
            continue;

        else if (string[i] == '.') {

            if (dotFlag == 0)
                dotFlag = 1;
            else
                return 0;

        }

        else if ( !(string[i] >= '0' && string[i] <= '9') )
            return 0;

    }

    return 1;

}






/** This function will take an char array pointer,
 * then it will return the sum of the ASCII value of the array characters.
 * @param ch the char array pointer
 * @return it will return the sum of the ASCII value of the array characters.
 */

int charArrSumASCII(char *ch) {

    if (ch == NULL) {
        fprintf(stderr, NULL_POINTER_MESSAGE, "char array", "char array sum ASCII");
        exit(NULL_POINTER);
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

int charArrHashFun(char *ch) {
    charArrSumASCII(ch);
}







/** This function will take a char array
 * then it will allocate a new one and copy the original char array into the new one,
 * and finally return the new allocated char array.
 * @param ch the char array pointer
 * @param length the length of the char array
 * @return it will return the new allocated char array pointer
 */

char *generateCharPointerP(char *ch, int length) {

    if (ch == NULL) {
        fprintf(stderr, NULL_POINTER_MESSAGE, "char array", "generate char pointer function");
        exit(NULL_POINTER);
    } else if (length < 0) {
        fprintf(stderr, INVALID_ARG_MESSAGE, "char array length", "generate char pointer function");
        exit(INVALID_ARG);
    }

    char *newCh = (char *) malloc( sizeof(char) * (length + 1) );
    if (newCh == NULL) {
        fprintf(stderr, FAILED_ALLOCATION_MESSAGE, "new char pointer", "generate char pointer function");
        exit(FAILED_ALLOCATION);
    }

    strcpy(newCh, ch);

    return newCh;

}








/** this function will allocate a new char array pointer,
 * the assign it's value with the passed char.
 * @param c the char value
 * @return it will return the new allocated char array
 */

char *generateCharPointerC(char c) {

    char *newCh = (char *) malloc( sizeof(char) * 2 );
    if (newCh == NULL) {
        fprintf(stderr, FAILED_ALLOCATION_MESSAGE, "new char pointer", "generate char pointer function");
        exit(FAILED_ALLOCATION);
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
    return (c >= 'a' && c <= 'z') || ( c >= 'A' && c <= 'Z');
}










/** This function will take a character pointer,
 * then it will return one (1) if the pointer value is an alphabet, other wise it will return zero (0).
 * @param c the char value
 * @return it will return one if the pointer value is an alphabet, other wise it will return zero.
 */

int isAlphabetP(const char *c) {
    return (*c >= 'a' && *c <= 'z') || ( *c >= 'A' && *c <= 'Z');
}
