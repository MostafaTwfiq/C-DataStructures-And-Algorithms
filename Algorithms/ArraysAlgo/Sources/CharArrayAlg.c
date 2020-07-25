#include "../Headers/CharArrayAlg.h"
#include "../../../System/Utils.h"








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

