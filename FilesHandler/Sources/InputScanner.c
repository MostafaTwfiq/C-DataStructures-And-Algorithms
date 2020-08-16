#include "../Headers/InputScanner.h"
#include "../../DataStructure/Strings/Headers/String.h"
#include "../../Algorithms/ArraysAlg/Headers/CharArrayAlg.h"
#include "../../System/Utils.h"
#include "../../Unit Test/CuTest/CuTest.h"


/** This function will scan the input as string,
 * then it will return the char array of the string.
 *
 * @param dir the file pointer that the function will scan the input from it
 * @return it will return the char array of the input
 */

String *scanStrS(FILE *dir) {

    if (dir == NULL) {
#ifdef C_DATASTRUCTURES_ERRORSTESTSTRUCT_H
        ERROR_TEST->errorCode = INVALID_ARG;
        return NULL;
#else
        fprintf(stderr, INVALID_ARG_MESSAGE, "file pointer", "input scanner");
        exit(INVALID_ARG);
#endif

    }

    String *string = stringInitialization(10);
    stringScanInput(string, dir);

    return string;

}


/** This function will scan the input as string,
 * then it will return the string pointer of the input.
 *
 * @param dir the file pointer that the function will scan the input from it
 * @return it will return the string pointer of the input
 */

char *scanStrC(FILE *dir) {

    if (dir == NULL) {
#ifdef C_DATASTRUCTURES_ERRORSTESTSTRUCT_H
        ERROR_TEST->errorCode = INVALID_ARG;
        return NULL;
#else
        fprintf(stderr, INVALID_ARG_MESSAGE, "file pointer", "input scanner");
        exit(INVALID_ARG);
#endif

    }

    String *string = stringInitialization(10);
    stringScanInput(string, dir);

    char *charArr = stringToCharArray(string);

    destroyString(string);
    return charArr;

}


/** This function will scan the input as character,
 * then it will return the character value.
 *
 * @param dir the file pointer that the function will scan the input from it
 * @return it will return the scanned character
 */

char scanChar(FILE *dir) {

    if (dir == NULL) {
#ifdef C_DATASTRUCTURES_ERRORSTESTSTRUCT_H
        ERROR_TEST->errorCode = INVALID_ARG;
        return '\0';
#else
        fprintf(stderr, INVALID_ARG_MESSAGE, "file pointer", "input scanner");
        exit(INVALID_ARG);
#endif

    }

    return fgetc(dir);

}


/** This function will scan the input as integer,
 * then it will return the integer of the input.
 *
 * @param dir the file pointer that the function will scan the input from it
 * @return it will return the integer of the input
 */

int scanInt(FILE *dir) {

    if (dir == NULL) {
#ifdef C_DATASTRUCTURES_ERRORSTESTSTRUCT_H
        ERROR_TEST->errorCode = INVALID_ARG;
        return -1;
#else
        fprintf(stderr, INVALID_ARG_MESSAGE, "file pointer", "input scanner");
        exit(INVALID_ARG);
#endif

    }

    String *string = stringInitialization(10);
    stringScanInput(string, dir);

    if (!isInteger(string->string)) {
#ifdef C_DATASTRUCTURES_ERRORSTESTSTRUCT_H
        ERROR_TEST->errorCode = SOMETHING_WENT_WRONG;
        return -1;
#else
        fprintf(stderr, SOMETHING_WENT_WRONG_MESSAGE, "load the int", "scan int function");
        exit(SOMETHING_WENT_WRONG);
#endif
    }

    int integer = atoi(string->string);
    destroyString(string);

    return integer;

}


/** This function will scan the input as double,
 * then it will return the double of the input.
 *
 * @param dir the file pointer that the function will scan the input from it
 * @return it will return the double of the input
 */

double scanDouble(FILE *dir) {

    if (dir == NULL) {
#ifdef C_DATASTRUCTURES_ERRORSTESTSTRUCT_H
        ERROR_TEST->errorCode = INVALID_ARG;
        return -1;
#else
        fprintf(stderr, INVALID_ARG_MESSAGE, "file pointer", "input scanner");
        exit(INVALID_ARG);
#endif

    }

    String *string = stringInitialization(10);
    stringScanInput(string, dir);

    if (!isFloatingPointNum(string->string)) {
#ifdef C_DATASTRUCTURES_ERRORSTESTSTRUCT_H
        ERROR_TEST->errorCode = SOMETHING_WENT_WRONG;
        return -1;
#else
        fprintf(stderr, SOMETHING_WENT_WRONG_MESSAGE, "load the double", "scan double function");
        exit(SOMETHING_WENT_WRONG);
#endif
    }

    double dl = atof(string->string);
    destroyString(string);

    return dl;

}


/** This function will scan the input as float,
 * then it will return the float of the input.
 *
 * @param dir the file pointer that the function will scan the input from it
 * @return it will return the float of the input
 */

float scanFloat(FILE *dir) {

    if (dir == NULL) {
#ifdef C_DATASTRUCTURES_ERRORSTESTSTRUCT_H
        ERROR_TEST->errorCode = INVALID_ARG;
        return -1;
#else
        fprintf(stderr, INVALID_ARG_MESSAGE, "file pointer", "input scanner");
        exit(INVALID_ARG);
#endif

    }

    String *string = stringInitialization(10);
    stringScanInput(string, dir);

    if (!isFloatingPointNum(string->string)) {
#ifdef C_DATASTRUCTURES_ERRORSTESTSTRUCT_H
        ERROR_TEST->errorCode = SOMETHING_WENT_WRONG;
        return -1;
#else
        fprintf(stderr, SOMETHING_WENT_WRONG_MESSAGE, "load the float", "scan float function");
        exit(SOMETHING_WENT_WRONG);
#endif
    }

    float fl = (float) atof(string->string);
    destroyString(string);

    return fl;

}


/** This function will scan the input as long,
 * then it will return the long of the input.
 *
 * @param dir the file pointer that the function will scan the input from it
 * @return it will return the long of the input
 */

long scanLong(FILE *dir) {

    if (dir == NULL) {
#ifdef C_DATASTRUCTURES_ERRORSTESTSTRUCT_H
        ERROR_TEST->errorCode = INVALID_ARG;
        return -1;
#else
        fprintf(stderr, INVALID_ARG_MESSAGE, "file pointer", "input scanner");
        exit(INVALID_ARG);
#endif

    }

    String *string = stringInitialization(10);
    stringScanInput(string, dir);

    if (!isInteger(string->string)) {
#ifdef C_DATASTRUCTURES_ERRORSTESTSTRUCT_H
        ERROR_TEST->errorCode = SOMETHING_WENT_WRONG;
        return -1;
#else
        fprintf(stderr, SOMETHING_WENT_WRONG_MESSAGE, "load the long", "scan long function");
        exit(SOMETHING_WENT_WRONG);
#endif
    }

    long l = (long) atol(string->string);
    destroyString(string);

    return l;

}


/** This function will scan the input as long long,
 * then it will return the long long of the input.
 *
 * @param dir the file pointer that the function will scan the input from it
 * @return it will return the long long of the input
 */

long long scanLongLong(FILE *dir) {

    if (dir == NULL) {
#ifdef C_DATASTRUCTURES_ERRORSTESTSTRUCT_H
        ERROR_TEST->errorCode = INVALID_ARG;
        return -1;
#else
        fprintf(stderr, INVALID_ARG_MESSAGE, "file pointer", "input scanner");
        exit(INVALID_ARG);
#endif

    }

    String *string = stringInitialization(10);
    stringScanInput(string, dir);

    if (!isInteger(string->string)) {
#ifdef C_DATASTRUCTURES_ERRORSTESTSTRUCT_H
        ERROR_TEST->errorCode = SOMETHING_WENT_WRONG;
        return -1;
#else
        fprintf(stderr, SOMETHING_WENT_WRONG_MESSAGE, "load the long long", "scan long long function");
        exit(SOMETHING_WENT_WRONG);
#endif
    }

    long long ll = (long long) atoll(string->string);
    destroyString(string);

    return ll;

}


/** This function will scan the input as short,
 * then it will return the short of the input.
 *
 * @param dir the file pointer that the function will scan the input from it
 * @return it will return the short of the input
 */

short scanShort(FILE *dir) {

    if (dir == NULL) {
#ifdef C_DATASTRUCTURES_ERRORSTESTSTRUCT_H
        ERROR_TEST->errorCode = INVALID_ARG;
        return -1;
#else
        fprintf(stderr, INVALID_ARG_MESSAGE, "file pointer", "input scanner");
        exit(INVALID_ARG);
#endif

    }

    String *string = stringInitialization(10);
    stringScanInput(string, dir);

    if (!isInteger(string->string)) {
#ifdef C_DATASTRUCTURES_ERRORSTESTSTRUCT_H
        ERROR_TEST->errorCode = SOMETHING_WENT_WRONG;
        return -1;
#else
        fprintf(stderr, SOMETHING_WENT_WRONG_MESSAGE, "load the short", "scan short function");
        exit(SOMETHING_WENT_WRONG);
#endif
    }

    short sh = (short) atoi(string->string);
    destroyString(string);

    return sh;

}
