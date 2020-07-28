#include "TxtFileLoader.h"
#include "../DataStructure/Strings/Headers/String.h"
#include "../DataStructure/Lists/Headers/Vector.h"






/** This function will allocate a new txt file loader then the memory,
 * and setup it's fields, and finally return the initialized txt file loader pointer.
 *
 * @param fileDir the direction of the text file
 * @return it will return the initialized txt file loader pointer.
 */

TxtFileLoader *txtFileLoaderInitialization(char *fileDir) {

    TxtFileLoader *loader = (TxtFileLoader *) malloc(sizeof(TxtFileLoader));

    loader->dir = fopen(fileDir, "r");

    return loader;

}







/** This function will load the file into a string,
 * then it will return the string pointer.
 * @param txtFileLoader the text file loader pointer
 * @return it will return the loaded string pointer
 */

String *txtLoaderReadFileString(TxtFileLoader *txtFileLoader) {

    String *fString = stringInitialization(10);
    char c;
    while ((c = (char) fgetc(txtFileLoader->dir)) != EOF)
        stringAddCharAtLast(fString, c);

    fseek(txtFileLoader->dir, 0, SEEK_SET);

    return fString;

}









/** This function will load the file into a char array,
 * then it will return the string pointer.
 *
 * Note: this function will load the file into a string first,
 * then it will convert the string to char array.
 *
 * @param txtFileLoader the text file loader pointer
 * @return it will return the loaded char array pointer
 */

char *txtLoaderReadFileCharArr(TxtFileLoader *txtFileLoader) {

    String *fString = stringInitialization(10);
    char c;
    while ((c = (char) fgetc(txtFileLoader->dir)) != EOF)
        stringAddCharAtLast(fString, c);

    fseek(txtFileLoader->dir, 0, SEEK_SET);

    char *fileCharArr = stringToArrayOfCharacters(fString);
    destroyString(fString);

    return fileCharArr;

}





/** This function will load the file lines into strings,
 * and it will but the lines strings into a vector,
 * and finally return the vector pointer.
 * @param txtFileLoader the text file loader pointer
 * @return it will return the lines vector
 */

Vector *txtLoaderReadFileLines(TxtFileLoader *txtFileLoader) {

    Vector *linesVector = vectorInitialization(10, destroyString, stringIsEqualsToMyString);
    vectorAdd(linesVector, stringInitialization(10));
    int stringIndex = 0;
    char c;
    while ((c = (char) fgetc(txtFileLoader->dir)) != EOF) {

        if ( c == '\n' ) {
            stringIndex++;
            vectorAdd(linesVector, stringInitialization(10));
            continue;
        }

        stringAddCharAtLast(vectorGet(linesVector, stringIndex), c);

    }


    fseek(txtFileLoader->dir, 0, SEEK_SET);

    return linesVector;

}