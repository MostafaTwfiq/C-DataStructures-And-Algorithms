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
        fprintf(stderr, NULL_POINTER_MESSAGE, "first passed char", "sub string algorithm");
        exit(NULL_POINTER);
    } else if (sString == NULL) {
        fprintf(stderr, NULL_POINTER_MESSAGE, "comparator function", "sub string algorithm");
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


