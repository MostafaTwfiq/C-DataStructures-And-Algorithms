#include "../Headers/InputScanner.h"
#include "../../DataStructure/Strings/Headers/String.h"
#include "../../Algorithms/ArraysAlg/Headers/CharArrayAlg.h"
#include "../../System/Utils.h"





/** This function will scan the input as string,
 * then it will return the char array of the string.
 * @return it will return the char array of the input
 */

String *scanStrS() {

    String *string = stringInitialization(10);
    stringScanInput(string);

    return string;

}





/** This function will scan the input as string,
 * then it will return the string pointer of the input.
 * @return it will return the string pointer of the input
 */

char *scanStrC() {

    String *string = stringInitialization(10);
    stringScanInput(string);

    char *charArr = stringToCharArray(string);

    destroyString(string);
    return charArr;

}





/** This function will scan the input as integer,
 * then it will return the integer of the input.
 * @return it will return the integer of the input
 */

int scanInt() {

    String *string = stringInitialization(10);
    stringScanInput(string);

    if (!isInteger(string->string, stringGetLength(string))) {
        fprintf(stderr, SOMETHING_WENT_WRONG_MESSAGE, "load the int", "scan int function");
        exit(SOMETHING_WENT_WRONG);
    }

    int integer = atoi(string->string);
    destroyString(string);

    return integer;

}






/** This function will scan the input as double,
 * then it will return the double of the input.
 * @return it will return the double of the input
 */

double scanDouble() {

    String *string = stringInitialization(10);
    stringScanInput(string);

    if (!isFloatingPointNum(string->string, stringGetLength(string))) {
        fprintf(stderr, SOMETHING_WENT_WRONG_MESSAGE, "load the double", "scan double function");
        exit(SOMETHING_WENT_WRONG);
    }

    double dl = atof(string->string);
    destroyString(string);

    return dl;

}





/** This function will scan the input as float,
 * then it will return the float of the input.
 * @return it will return the float of the input
 */

float scanFloat() {

    String *string = stringInitialization(10);
    stringScanInput(string);

    if (!isFloatingPointNum(string->string, stringGetLength(string))) {
        fprintf(stderr, SOMETHING_WENT_WRONG_MESSAGE, "load the float", "scan float function");
        exit(SOMETHING_WENT_WRONG);
    }

    float fl = (float) atof(string->string);
    destroyString(string);

    return fl;

}





/** This function will scan the input as long,
 * then it will return the long of the input.
 * @return it will return the long of the input
 */

long scanLong() {

    String *string = stringInitialization(10);
    stringScanInput(string);

    if (!isInteger(string->string, stringGetLength(string))) {
        fprintf(stderr, SOMETHING_WENT_WRONG_MESSAGE, "load the long", "scan long function");
        exit(SOMETHING_WENT_WRONG);
    }

    long l = (long ) atol(string->string);
    destroyString(string);

    return l;

}





/** This function will scan the input as long long,
 * then it will return the long long of the input.
 * @return it will return the long long of the input
 */

long long scanLongLong() {

    String *string = stringInitialization(10);
    stringScanInput(string);

    if (!isInteger(string->string, stringGetLength(string))) {
        fprintf(stderr, SOMETHING_WENT_WRONG_MESSAGE, "load the long long", "scan long long function");
        exit(SOMETHING_WENT_WRONG);
    }

    long long ll = (long long) atoll(string->string);
    destroyString(string);

    return ll;

}






/** This function will scan the input as short,
 * then it will return the short of the input.
 * @return it will return the short of the input
 */

short scanShort() {

    String *string = stringInitialization(10);
    stringScanInput(string);

    if (!isInteger(string->string, stringGetLength(string))) {
        fprintf(stderr, SOMETHING_WENT_WRONG_MESSAGE, "load the short", "scan short function");
        exit(SOMETHING_WENT_WRONG);
    }

    short sh = (short) atoi(string->string);
    destroyString(string);

    return sh;

}
