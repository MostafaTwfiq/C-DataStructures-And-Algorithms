#include "../Headers/IntegerAlg.h"
#include "../../../System/Utils.h"
#include <math.h>



/** This function will an integer,
 * then it will return the number of digits of the integer, without considering the sign.
 * @param num the integer value
 * @return it will return the number of digits
 */

int integerNumOfDigits(int num) {
    if (num == 0)
        return 1;

    return (int) floor(log10( num < 0 ? num * -1 : num ) + 1);

}









/** This function will take an integer number,
 * then it will return a char array pointer, that consist of the passed integer.
 * @param num the number value
 * @return it will return the integer value as a char array pointer
 */

char *intToCharArr(int num) {

    short negativeNumFlag = num < 0 ? 1 : 0;
    int numOfDigits = integerNumOfDigits(num);
    char *numCharArr = (char *) malloc(sizeof(char) * ( numOfDigits + 1 + negativeNumFlag ) );
    numCharArr[numOfDigits + negativeNumFlag] = '\0';
    if (negativeNumFlag) {
        *numCharArr = '-';
        num *= -1;
    }

    for (int i = 0; i < numOfDigits; i++, num /= 10)
        numCharArr[numOfDigits + negativeNumFlag - 1 - i] = (num % 10) + '0';

    return numCharArr;

}