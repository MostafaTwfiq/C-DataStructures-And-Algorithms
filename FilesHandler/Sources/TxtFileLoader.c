#include "../Headers/TxtFileLoader.h"
#include "../../DataStructure/Strings/Headers/String.h"
#include "../../DataStructure/Lists/Headers/Vector.h"
#include "../../System/Utils.h"
#include "../../Unit Test/CuTest/CuTest.h"


/** This function will allocate a new txt file loader then the memory,
 * and setup it's fields, and finally return the initialized txt file loader pointer.
 *
 * @param fileDir the direction of the text file
 * @return it will return the initialized txt file loader pointer.
 */

TxtFileLoader *txtFileLoaderInitialization(char *fileDir) {

    if (fileDir == NULL) {
#ifdef C_DATASTRUCTURES_ERRORSTESTSTRUCT_H
        ERROR_TEST->errorCode = INVALID_ARG;
        return NULL;
#else
        fprintf(stderr, INVALID_ARG_MESSAGE, "file direction", "text file loader");
        exit(INVALID_ARG);
#endif
    }

    TxtFileLoader *loader = (TxtFileLoader *) malloc(sizeof(TxtFileLoader));
    if (loader == NULL) {
#ifdef C_DATASTRUCTURES_ERRORSTESTSTRUCT_H
        ERROR_TEST->errorCode = FAILED_ALLOCATION;
        return NULL;
#else
        fprintf(stderr, FAILED_ALLOCATION_MESSAGE, "loader", "text file loader");
        exit(FAILED_ALLOCATION);
#endif
    }

    loader->dir = (char *) malloc(sizeof(char) * (strlen(fileDir) + 1));
    if (loader->dir == NULL) {
#ifdef C_DATASTRUCTURES_ERRORSTESTSTRUCT_H
        ERROR_TEST->errorCode = FAILED_ALLOCATION;
        return NULL;
#else
        fprintf(stderr, FAILED_ALLOCATION_MESSAGE, "file direction", "text file loader");
        exit(FAILED_ALLOCATION);
#endif
    }

    loader->dir = strcpy(loader->dir, fileDir);
    if (loader->dir == NULL) {
#ifdef C_DATASTRUCTURES_ERRORSTESTSTRUCT_H
        ERROR_TEST->errorCode = FAILED_COPY;
        return NULL;
#else
        fprintf(stderr, FAILED_COPY_MESSAGE, "file direction", "text file loader");
        exit(FAILED_COPY);
#endif
    }

    return loader;

}


/** This function will open the file.
 *
 * @param txtFileLoader the text file loader pointer
 * */

void txtLoaderOpenFile(TxtFileLoader *txtFileLoader, char *openType) {

    if (txtFileLoader == NULL) {
#ifdef C_DATASTRUCTURES_ERRORSTESTSTRUCT_H
        ERROR_TEST->errorCode = NULL_POINTER;
        return;
#else
        fprintf(stderr, NULL_POINTER_MESSAGE, "loader", "text file loader");
        exit(NULL_POINTER);
#endif
    }

    txtFileLoader->fileP = fopen(txtFileLoader->dir, openType);
    if (txtFileLoader->fileP == NULL) {
        fprintf(stderr, SOMETHING_WENT_WRONG_MESSAGE, "open the file", "text file loader");
        exit(SOMETHING_WENT_WRONG);
    }

}


/** This function will load the file into a string,
 * then it will return the string pointer.
 *
 * @param txtFileLoader the text file loader pointer
 * @return it will return the loaded string pointer
 */

String *txtLoaderReadFileS(TxtFileLoader *txtFileLoader) {

    if (txtFileLoader == NULL) {
#ifdef C_DATASTRUCTURES_ERRORSTESTSTRUCT_H
        ERROR_TEST->errorCode = NULL_POINTER;
        return NULL;
#else
        fprintf(stderr, NULL_POINTER_MESSAGE, "loader", "text file loader");
        exit(NULL_POINTER);
#endif
    }

    txtLoaderOpenFile(txtFileLoader, "r");

    String *fString = stringInitialization(10);
    char c;
    while ((c = (char) fgetc(txtFileLoader->fileP)) != EOF)
        stringAppendChar(fString, c);

    fseek(txtFileLoader->fileP, 0, SEEK_SET);

    fclose(txtFileLoader->fileP);

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

char *txtLoaderReadFileC(TxtFileLoader *txtFileLoader) {

    if (txtFileLoader == NULL) {
#ifdef C_DATASTRUCTURES_ERRORSTESTSTRUCT_H
        ERROR_TEST->errorCode = NULL_POINTER;
        return NULL;
#else
        fprintf(stderr, NULL_POINTER_MESSAGE, "loader", "text file loader");
        exit(NULL_POINTER);
#endif
    }

    txtLoaderOpenFile(txtFileLoader, "r");

    String *fString = stringInitialization(10);
    char c;
    while ((c = (char) fgetc(txtFileLoader->fileP)) != EOF)
        stringAppendChar(fString, c);

    fseek(txtFileLoader->fileP, 0, SEEK_SET);

    char *fileCharArr = stringToCharArray(fString);
    destroyString(fString);

    fclose(txtFileLoader->fileP);
    return fileCharArr;

}


/** This function will load the file lines into strings,
 * and it will but the lines strings into a vector,
 * and finally return the vector pointer.
 *
 * @param txtFileLoader the text file loader pointer
 * @return it will return the lines vector
 */

Vector *txtLoaderReadFileLines(TxtFileLoader *txtFileLoader) {

    if (txtFileLoader == NULL) {
#ifdef C_DATASTRUCTURES_ERRORSTESTSTRUCT_H
        ERROR_TEST->errorCode = NULL_POINTER;
        return NULL;
#else
        fprintf(stderr, NULL_POINTER_MESSAGE, "loader", "text file loader");
        exit(NULL_POINTER);
#endif
    }

    txtLoaderOpenFile(txtFileLoader, "r");

    Vector *linesVector = vectorInitialization(10, destroyString, stringCompareS);
    vectorAdd(linesVector, stringInitialization(10));
    int stringIndex = 0;
    char c;
    while ((c = (char) fgetc(txtFileLoader->fileP)) != EOF) {

        if (c == '\n') {
            stringIndex++;
            vectorAdd(linesVector, stringInitialization(10));
            continue;
        }

        stringAppendChar(vectorGet(linesVector, stringIndex), c);

    }


    fseek(txtFileLoader->fileP, 0, SEEK_SET);

    fclose(txtFileLoader->fileP);
    return linesVector;

}


int charArrContainsTxtFileLoader(char *arr, char c) {

    while (*arr != '\0') {

        if (*arr++ == c)
            return 1;

    }

    return 0;

}


/** This function will load the file lines into strings,
 * and it will but the lines strings into a vector,
 * and finally return the vector pointer.
 *
 * Ex for a delimiter: ( ",\n" ) the string will split at ',' and '\n' characters.
 *
 * @param txtFileLoader the text file loader pointer
 * @param delimiter the characters that the string will split at.
 * @return it will return the lines vector
 */

Vector *txtLoaderReadFileWthDelimiter(TxtFileLoader *txtFileLoader, char *delimiter) {

    if (txtFileLoader == NULL) {
#ifdef C_DATASTRUCTURES_ERRORSTESTSTRUCT_H
        ERROR_TEST->errorCode = NULL_POINTER;
        return NULL;
#else
        fprintf(stderr, NULL_POINTER_MESSAGE, "loader", "text file loader");
        exit(NULL_POINTER);
#endif
    } else if (delimiter == NULL) {
#ifdef C_DATASTRUCTURES_ERRORSTESTSTRUCT_H
        ERROR_TEST->errorCode = INVALID_ARG;
        return NULL;
#else
        fprintf(stderr, INVALID_ARG_MESSAGE, "delimiter pointer", "text file loader");
        exit(INVALID_ARG);
#endif
    }

    txtLoaderOpenFile(txtFileLoader, "r");

    Vector *linesVector = vectorInitialization(10, destroyString, stringCompareS);
    vectorAdd(linesVector, stringInitialization(10));
    int stringIndex = 0;
    char c;
    while ((c = (char) fgetc(txtFileLoader->fileP)) != EOF) {

        if (charArrContainsTxtFileLoader(delimiter, c)) {
            stringIndex++;
            vectorAdd(linesVector, stringInitialization(10));
            continue;
        }

        stringAppendChar(vectorGet(linesVector, stringIndex), c);

    }


    fseek(txtFileLoader->fileP, 0, SEEK_SET);

    fclose(txtFileLoader->fileP);
    return linesVector;

}


/** This function will count the file lines, then return it.
 *
 * @param txtFileLoader the text file loader pointer
 * @return it will return the lines vector
 */

int txtLoaderCountLines(TxtFileLoader *txtFileLoader) {

    if (txtFileLoader == NULL) {
#ifdef C_DATASTRUCTURES_ERRORSTESTSTRUCT_H
        ERROR_TEST->errorCode = NULL_POINTER;
        return -1;
#else
        fprintf(stderr, NULL_POINTER_MESSAGE, "loader", "text file loader");
        exit(NULL_POINTER);
#endif
    }

    txtLoaderOpenFile(txtFileLoader, "r");

    int counter = 1;
    char c = (char) fgetc(txtFileLoader->fileP);
    if (c == EOF)
        counter = 0;

    while ((c = (char) fgetc(txtFileLoader->fileP)) != EOF) {

        if (c == '\n')
            counter++;

    }


    fseek(txtFileLoader->fileP, 0, SEEK_SET);

    fclose(txtFileLoader->fileP);

    return counter;

}


/** This function will read the provided line index form the file,
 * then it will return the line as a string.
 *
 * Note: if the function didn't found the line with the provided index it will return NULL.
 *
 * @param txtFileLoader the text file loader pointer
 * @param lineIndex the line index
 * @return it will return the line string pointer if found, other wise it will return NULL
 */

String *txtLoaderReadLineS(TxtFileLoader *txtFileLoader, int lineIndex) {

    if (txtFileLoader == NULL) {
#ifdef C_DATASTRUCTURES_ERRORSTESTSTRUCT_H
        ERROR_TEST->errorCode = NULL_POINTER;
        return NULL;
#else
        fprintf(stderr, NULL_POINTER_MESSAGE, "loader", "text file loader");
        exit(NULL_POINTER);
#endif
    }

    txtLoaderOpenFile(txtFileLoader, "r");

    char c;
    int currentIndex = 0;

    while (currentIndex != lineIndex && (c = (char) fgetc(txtFileLoader->fileP)) != EOF) {

        if (c == '\n')
            currentIndex++;

    }


    if (currentIndex != lineIndex && c == EOF) {
        fclose(txtFileLoader->fileP);
        return NULL;
    }

    String *lineString = stringInitialization(5);
    while ((c = (char) fgetc(txtFileLoader->fileP)) != EOF && c != '\n')
        stringAppendChar(lineString, c);


    fclose(txtFileLoader->fileP);
    return lineString;

}


/** This function will read the provided line index form the file,
 * then it will return the line as a char array.
 *
 * Note: if the function didn't found the line with the provided index it will return NULL.
 *
 * @param txtFileLoader the text file loader pointer
 * @param lineIndex the line index
 * @return it will return the line char array pointer if found, other wise it will return NULL
 */

char *txtLoaderReadLineC(TxtFileLoader *txtFileLoader, int lineIndex) {

    if (txtFileLoader == NULL) {
#ifdef C_DATASTRUCTURES_ERRORSTESTSTRUCT_H
        ERROR_TEST->errorCode = NULL_POINTER;
        return NULL;
#else
        fprintf(stderr, NULL_POINTER_MESSAGE, "loader", "text file loader");
        exit(NULL_POINTER);
#endif
    }

    txtLoaderOpenFile(txtFileLoader, "r");

    char c;
    int currentIndex = 0;

    while (currentIndex != lineIndex && (c = (char) fgetc(txtFileLoader->fileP)) != EOF) {

        if (c == '\n')
            currentIndex++;

    }


    if (currentIndex != lineIndex && c == EOF) {
        fclose(txtFileLoader->fileP);
        return NULL;
    }

    String *lineString = stringInitialization(5);
    while ((c = (char) fgetc(txtFileLoader->fileP)) != EOF && c != '\n')
        stringAppendChar(lineString, c);

    char *charLine = stringToCharArray(lineString);
    destroyString(lineString);


    fclose(txtFileLoader->fileP);
    return charLine;

}


/** This function will take a char array,
 * then it will write the char array to the file.
 *
 * Note: the file will be cleared before writing the new data.
 *
 * @param txtFileLoader the text file loader pointer
 * @param data the char array pointer
 */

void txtLoaderWriteC(TxtFileLoader *txtFileLoader, char *data) {

    if (txtFileLoader == NULL) {
#ifdef C_DATASTRUCTURES_ERRORSTESTSTRUCT_H
        ERROR_TEST->errorCode = NULL_POINTER;
        return;
#else
        fprintf(stderr, NULL_POINTER_MESSAGE, "loader", "text file loader");
        exit(NULL_POINTER);
#endif
    } else if (data == NULL) {
#ifdef C_DATASTRUCTURES_ERRORSTESTSTRUCT_H
        ERROR_TEST->errorCode = INVALID_ARG;
        return;
#else
        fprintf(stderr, INVALID_ARG_MESSAGE, "data char array", "text file loader");
        exit(INVALID_ARG);
#endif
    }


    txtLoaderOpenFile(txtFileLoader, "w");

    fprintf(txtFileLoader->fileP, "%s", data);

    fclose(txtFileLoader->fileP);

}


/** This function will take a string,
 * then it will write the string to the file.
 *
 * Note: the file will be cleared before writing the new data.
 *
 * @param txtFileLoader
 * @param data
 */

void txtLoaderWriteS(TxtFileLoader *txtFileLoader, String *data) {

    if (txtFileLoader == NULL) {
#ifdef C_DATASTRUCTURES_ERRORSTESTSTRUCT_H
        ERROR_TEST->errorCode = NULL_POINTER;
        return;
#else
        fprintf(stderr, NULL_POINTER_MESSAGE, "loader", "text file loader");
        exit(NULL_POINTER);
#endif
    } else if (data == NULL) {
#ifdef C_DATASTRUCTURES_ERRORSTESTSTRUCT_H
        ERROR_TEST->errorCode = INVALID_ARG;
        return;
#else
        fprintf(stderr, INVALID_ARG_MESSAGE, "data string", "text file loader");
        exit(INVALID_ARG);
#endif
    }

    txtLoaderOpenFile(txtFileLoader, "w");

    fprintf(txtFileLoader->fileP, "%s", data->string);

    fclose(txtFileLoader->fileP);

}


/** This function will take a char array,
 * then it will append the char array at the end of the file.
 *
 * @param txtFileLoader the text file loader pointer
 * @param data the char array pointer
 */

void txtLoaderAppendC(TxtFileLoader *txtFileLoader, char *data) {

    if (txtFileLoader == NULL) {
#ifdef C_DATASTRUCTURES_ERRORSTESTSTRUCT_H
        ERROR_TEST->errorCode = NULL_POINTER;
        return;
#else
        fprintf(stderr, NULL_POINTER_MESSAGE, "loader", "text file loader");
        exit(NULL_POINTER);
#endif
    } else if (data == NULL) {
#ifdef C_DATASTRUCTURES_ERRORSTESTSTRUCT_H
        ERROR_TEST->errorCode = INVALID_ARG;
        return;
#else
        fprintf(stderr, INVALID_ARG_MESSAGE, "data char array", "text file loader");
        exit(INVALID_ARG);
#endif
    }

    txtLoaderOpenFile(txtFileLoader, "a");

    fprintf(txtFileLoader->fileP, "%s", data);

    fclose(txtFileLoader->fileP);

}


/** This function will take a string,
 * then it will append the string at the end of the file.
 *
 * @param txtFileLoader
 * @param data
 */

void txtLoaderAppendS(TxtFileLoader *txtFileLoader, String *data) {

    if (txtFileLoader == NULL) {
#ifdef C_DATASTRUCTURES_ERRORSTESTSTRUCT_H
        ERROR_TEST->errorCode = NULL_POINTER;
        return;
#else
        fprintf(stderr, NULL_POINTER_MESSAGE, "loader", "text file loader");
        exit(NULL_POINTER);
#endif
    } else if (data == NULL) {
#ifdef C_DATASTRUCTURES_ERRORSTESTSTRUCT_H
        ERROR_TEST->errorCode = INVALID_ARG;
        return;
#else
        fprintf(stderr, INVALID_ARG_MESSAGE, "data string", "text file loader");
        exit(INVALID_ARG);
#endif
    }

    txtLoaderOpenFile(txtFileLoader, "a");
    fprintf(txtFileLoader->fileP, "%s", data->string);

    fclose(txtFileLoader->fileP);

}


/** This function will take a vector of char arrays,
 * then it will append the char arrays at the end of the file.
 *
 * @param txtFileLoader the text file loader pointer
 * @param newLines the new lines vector pointer
 */

void txtLoaderAppendAllC(TxtFileLoader *txtFileLoader, Vector *newLines) {

    if (txtFileLoader == NULL) {
#ifdef C_DATASTRUCTURES_ERRORSTESTSTRUCT_H
        ERROR_TEST->errorCode = NULL_POINTER;
        return;
#else
        fprintf(stderr, NULL_POINTER_MESSAGE, "loader", "text file loader");
        exit(NULL_POINTER);
#endif
    } else if (newLines == NULL) {
#ifdef C_DATASTRUCTURES_ERRORSTESTSTRUCT_H
        ERROR_TEST->errorCode = INVALID_ARG;
        return;
#else
        fprintf(stderr, INVALID_ARG_MESSAGE, "new lines vector", "text file loader");
        exit(INVALID_ARG);
#endif
    }

    txtLoaderOpenFile(txtFileLoader, "a");
    for (int i = 0; i < vectorGetLength(newLines); i++)
        fprintf(txtFileLoader->fileP, "%s\n", (char *) vectorGet(newLines, i));


    fclose(txtFileLoader->fileP);

}


/** This function will take a vector of strings,
 * then it will append the strings at the end of the file.
 *
 * @param txtFileLoader the text file loader pointer
 * @param newLines the new lines vector pointer
 */

void txtLoaderAppendAllS(TxtFileLoader *txtFileLoader, Vector *newLines) {

    if (txtFileLoader == NULL) {
#ifdef C_DATASTRUCTURES_ERRORSTESTSTRUCT_H
        ERROR_TEST->errorCode = NULL_POINTER;
        return;
#else
        fprintf(stderr, NULL_POINTER_MESSAGE, "loader", "text file loader");
        exit(NULL_POINTER);
#endif
    } else if (newLines == NULL) {
#ifdef C_DATASTRUCTURES_ERRORSTESTSTRUCT_H
        ERROR_TEST->errorCode = INVALID_ARG;
        return;
#else
        fprintf(stderr, INVALID_ARG_MESSAGE, "new lines vector", "text file loader");
        exit(INVALID_ARG);
#endif
    }

    txtLoaderOpenFile(txtFileLoader, "a");
    for (int i = 0; i < vectorGetLength(newLines); i++)
        fprintf(txtFileLoader->fileP, "%s\n", ((String *) vectorGet(newLines, i))->string);


    fclose(txtFileLoader->fileP);

}


/** This function will take a char array and an index,
 * then it will append the passed char array at the end of the line at the provided index.
 *
 * @param txtFileLoader the text file loader pointer
 * @param lineToAppend the char array pointer of the line to be appended
 * @param index the index of the file that the char array will be appended to
 */

void txtLoaderAppendToLineC(TxtFileLoader *txtFileLoader, char *lineToAppend, int index) {

    if (txtFileLoader == NULL) {
#ifdef C_DATASTRUCTURES_ERRORSTESTSTRUCT_H
        ERROR_TEST->errorCode = NULL_POINTER;
        return;
#else
        fprintf(stderr, NULL_POINTER_MESSAGE, "loader", "text file loader");
        exit(NULL_POINTER);
#endif
    } else if (lineToAppend == NULL) {
#ifdef C_DATASTRUCTURES_ERRORSTESTSTRUCT_H
        ERROR_TEST->errorCode = INVALID_ARG;
        return;
#else
        fprintf(stderr, INVALID_ARG_MESSAGE, "new line to append char array", "text file loader");
        exit(INVALID_ARG);
#endif
    }

    Vector *linesVector = txtLoaderReadFileLines(txtFileLoader);
    if (index < 0 || index >= vectorGetLength(linesVector)) {
        destroyVector(linesVector);
#ifdef C_DATASTRUCTURES_ERRORSTESTSTRUCT_H
        ERROR_TEST->errorCode = INVALID_ARG;
        return;
#else
        fprintf(stderr, INVALID_ARG_MESSAGE, "new line to append index", "text file loader");
        exit(INVALID_ARG);
#endif
    }

    stringAppendC(vectorGet(linesVector, index), lineToAppend);

    txtLoaderOpenFile(txtFileLoader, "w");

    for (int i = 0; i < vectorGetLength(linesVector); i++)
        fprintf(txtFileLoader->fileP, "%s%c", ((String *) vectorGet(linesVector, i))->string,
                i != vectorGetLength(linesVector) - 1 ? '\n' : '\0');


    destroyVector(linesVector);

    fclose(txtFileLoader->fileP);

}


/** This function will take a string and an index,
 * then it will append the passed string at the end of the line at the provided index.
 *
 * @param txtFileLoader the text file loader pointer
 * @param stringToAppend the string pointer of the line to be appended
 * @param index the index of the file that the string will be appended to
 */

void txtLoaderAppendToLineS(TxtFileLoader *txtFileLoader, String *stringToAppend, int index) {

    if (txtFileLoader == NULL) {
#ifdef C_DATASTRUCTURES_ERRORSTESTSTRUCT_H
        ERROR_TEST->errorCode = NULL_POINTER;
        return;
#else
        fprintf(stderr, NULL_POINTER_MESSAGE, "loader", "text file loader");
        exit(NULL_POINTER);
#endif
    } else if (stringToAppend == NULL) {
#ifdef C_DATASTRUCTURES_ERRORSTESTSTRUCT_H
        ERROR_TEST->errorCode = INVALID_ARG;
        return;
#else
        fprintf(stderr, INVALID_ARG_MESSAGE, "new string to append", "text file loader");
        exit(INVALID_ARG);
#endif
    }

    Vector *linesVector = txtLoaderReadFileLines(txtFileLoader);
    if (index < 0 || index >= vectorGetLength(linesVector)) {
        destroyVector(linesVector);
#ifdef C_DATASTRUCTURES_ERRORSTESTSTRUCT_H
        ERROR_TEST->errorCode = INVALID_ARG;
        return;
#else
        fprintf(stderr, INVALID_ARG_MESSAGE, "new string to append index", "text file loader");
        exit(INVALID_ARG);
#endif
    }

    stringAppendS(vectorGet(linesVector, index), stringToAppend);

    txtLoaderOpenFile(txtFileLoader, "w");

    for (int i = 0; i < vectorGetLength(linesVector); i++)
        fprintf(txtFileLoader->fileP, "%s%c", ((String *) vectorGet(linesVector, i))->string,
                i != vectorGetLength(linesVector) - 1 ? '\n' : '\0');


    destroyVector(linesVector);

    fclose(txtFileLoader->fileP);

}


/** This function will take a char array and index,
 * then it will insert the passed char array at the provided index.
 *
 * @param txtFileLoader the text file loader pointer
 * @param line the char array pointer of the new line
 * @param index the index that the new line will be insert to
 */

void txtLoaderAddLineC(TxtFileLoader *txtFileLoader, char *line, int index) {

    if (txtFileLoader == NULL) {
#ifdef C_DATASTRUCTURES_ERRORSTESTSTRUCT_H
        ERROR_TEST->errorCode = NULL_POINTER;
        return;
#else
        fprintf(stderr, NULL_POINTER_MESSAGE, "loader", "text file loader");
        exit(NULL_POINTER);
#endif
    } else if (line == NULL) {
#ifdef C_DATASTRUCTURES_ERRORSTESTSTRUCT_H
        ERROR_TEST->errorCode = INVALID_ARG;
        return;
#else
        fprintf(stderr, INVALID_ARG_MESSAGE, "new line char array", "text file loader");
        exit(INVALID_ARG);
#endif
    }

    Vector *linesVector = txtLoaderReadFileLines(txtFileLoader);
    if (index < 0 || index >= vectorGetLength(linesVector)) {
        destroyVector(linesVector);
#ifdef C_DATASTRUCTURES_ERRORSTESTSTRUCT_H
        ERROR_TEST->errorCode = INVALID_ARG;
        return;
#else
        fprintf(stderr, INVALID_ARG_MESSAGE, "new line index", "text file loader");
        exit(INVALID_ARG);
#endif
    }

    String *newLineString = stringInitialization(10);
    stringChangeStringC(newLineString, line);

    vectorAddAtIndex(linesVector, newLineString, index);

    txtLoaderOpenFile(txtFileLoader, "w");

    for (int i = 0; i < vectorGetLength(linesVector); i++)
        fprintf(txtFileLoader->fileP, "%s\n", ((String *) vectorGet(linesVector, i))->string);


    destroyVector(linesVector);

    fclose(txtFileLoader->fileP);

}


/** This function will take a string and index,
 * then it will insert the passed string at the provided index.
 *
 * @param txtFileLoader the text file loader pointer
 * @param line the string pointer of the new line
 * @param index the index that the new line will be insert to
 */


void txtLoaderAddLineS(TxtFileLoader *txtFileLoader, String *line, int index) {

    if (txtFileLoader == NULL) {
#ifdef C_DATASTRUCTURES_ERRORSTESTSTRUCT_H
        ERROR_TEST->errorCode = NULL_POINTER;
        return;
#else
        fprintf(stderr, NULL_POINTER_MESSAGE, "loader", "text file loader");
        exit(NULL_POINTER);
#endif
    } else if (line == NULL) {
#ifdef C_DATASTRUCTURES_ERRORSTESTSTRUCT_H
        ERROR_TEST->errorCode = INVALID_ARG;
        return;
#else
        fprintf(stderr, INVALID_ARG_MESSAGE, "new string", "text file loader");
        exit(INVALID_ARG);
#endif
    }

    Vector *linesVector = txtLoaderReadFileLines(txtFileLoader);
    if (index < 0 || index >= vectorGetLength(linesVector)) {
        destroyVector(linesVector);
#ifdef C_DATASTRUCTURES_ERRORSTESTSTRUCT_H
        ERROR_TEST->errorCode = INVALID_ARG;
        return;
#else
        fprintf(stderr, INVALID_ARG_MESSAGE, "new line index", "text file loader");
        exit(INVALID_ARG);
#endif
    }

    vectorAddAtIndex(linesVector, line, index);

    txtLoaderOpenFile(txtFileLoader, "w");

    for (int i = 0; i < vectorGetLength(linesVector); i++)
        fprintf(txtFileLoader->fileP, "%s\n", ((String *) vectorGet(linesVector, i))->string);


    vectorRemoveAtIndexWtFr(linesVector, index);
    destroyVector(linesVector);

    fclose(txtFileLoader->fileP);

}


/** This function will take a vector of char arrays and index,
 * then it will insert the passed vector at the provided index.
 *
 * @param txtFileLoader the text file loader pointer
 * @param newLines the new lines vector pointer
 * @param index the index that the new lines will be inserted in
 */

void txtLoaderAddAllC(TxtFileLoader *txtFileLoader, Vector *newLines, int index) {

    if (txtFileLoader == NULL) {
#ifdef C_DATASTRUCTURES_ERRORSTESTSTRUCT_H
        ERROR_TEST->errorCode = NULL_POINTER;
        return;
#else
        fprintf(stderr, NULL_POINTER_MESSAGE, "loader", "text file loader");
        exit(NULL_POINTER);
#endif
    } else if (newLines == NULL) {
#ifdef C_DATASTRUCTURES_ERRORSTESTSTRUCT_H
        ERROR_TEST->errorCode = INVALID_ARG;
        return;
#else
        fprintf(stderr, INVALID_ARG_MESSAGE, "new lines vector", "text file loader");
        exit(INVALID_ARG);
#endif
    }

    Vector *linesVector = txtLoaderReadFileLines(txtFileLoader);
    if (index < 0 || index >= vectorGetLength(linesVector)) {
        destroyVector(linesVector);
#ifdef C_DATASTRUCTURES_ERRORSTESTSTRUCT_H
        ERROR_TEST->errorCode = INVALID_ARG;
        return;
#else
        fprintf(stderr, INVALID_ARG_MESSAGE, "new lines index", "text file loader");
        exit(INVALID_ARG);
#endif
    }

    for (int i = vectorGetLength(newLines) - 1; i >= 0; i--) {

        String *tempLineString = stringInitialization(10);
        stringChangeStringC(tempLineString, vectorGet(newLines, i));
        vectorAddAtIndex(linesVector, tempLineString, index);

    }

    txtLoaderOpenFile(txtFileLoader, "w");

    for (int i = 0; i < vectorGetLength(linesVector); i++) {

        fprintf(txtFileLoader->fileP, "%s%c", ((String *) vectorGet(linesVector, i))->string,
                i != vectorGetLength(linesVector) - 1 ? '\n' : '\0');

    }


    destroyVector(linesVector);

    fclose(txtFileLoader->fileP);

}


/** This function will take a vector of strings and index,
 * then it will insert the passed vector at the provided index.
 *
 * @param txtFileLoader the text file loader pointer
 * @param newLines the new lines vector pointer
 * @param index the index that the new lines will be inserted in
 */

void txtLoaderAddAllS(TxtFileLoader *txtFileLoader, Vector *newLines, int index) {

    if (txtFileLoader == NULL) {
#ifdef C_DATASTRUCTURES_ERRORSTESTSTRUCT_H
        ERROR_TEST->errorCode = NULL_POINTER;
        return;
#else
        fprintf(stderr, NULL_POINTER_MESSAGE, "loader", "text file loader");
        exit(NULL_POINTER);
#endif
    } else if (newLines == NULL) {
#ifdef C_DATASTRUCTURES_ERRORSTESTSTRUCT_H
        ERROR_TEST->errorCode = INVALID_ARG;
        return;
#else
        fprintf(stderr, INVALID_ARG_MESSAGE, "new lines vector", "text file loader");
        exit(INVALID_ARG);
#endif
    }

    Vector *linesVector = txtLoaderReadFileLines(txtFileLoader);
    if (index < 0 || index >= vectorGetLength(linesVector)) {
        destroyVector(linesVector);
#ifdef C_DATASTRUCTURES_ERRORSTESTSTRUCT_H
        ERROR_TEST->errorCode = INVALID_ARG;
        return;
#else
        fprintf(stderr, INVALID_ARG_MESSAGE, "new lines index", "text file loader");
        exit(INVALID_ARG);
#endif
    }

    for (int i = vectorGetLength(newLines) - 1; i >= 0; i--)
        vectorAddAtIndex(linesVector, vectorGet(newLines, i), index);

    txtLoaderOpenFile(txtFileLoader, "w");

    for (int i = 0; i < vectorGetLength(linesVector); i++) {

        fprintf(txtFileLoader->fileP, "%s%c", ((String *) vectorGet(linesVector, i))->string,
                i != vectorGetLength(linesVector) - 1 ? '\n' : '\0');


    }


    for (int i = 0; i < vectorGetLength(newLines); i++)
        vectorRemoveAtIndexWtFr(linesVector, index);

    destroyVector(linesVector);

    fclose(txtFileLoader->fileP);

}


/** This function will take a char array and an index,
 * then it will update the line in the provided index with the passed char array.
 *
 * @param txtFileLoader the text file loader pointer
 * @param line the new line char array
 * @param index the index of the line that will be updated
 */

void txtLoaderUpdateLineC(TxtFileLoader *txtFileLoader, char *line, int index) {

    if (txtFileLoader == NULL) {
#ifdef C_DATASTRUCTURES_ERRORSTESTSTRUCT_H
        ERROR_TEST->errorCode = NULL_POINTER;
        return;
#else
        fprintf(stderr, NULL_POINTER_MESSAGE, "loader", "text file loader");
        exit(NULL_POINTER);
#endif
    } else if (line == NULL) {
#ifdef C_DATASTRUCTURES_ERRORSTESTSTRUCT_H
        ERROR_TEST->errorCode = INVALID_ARG;
        return;
#else
        fprintf(stderr, INVALID_ARG_MESSAGE, "new line char array", "text file loader");
        exit(INVALID_ARG);
#endif
    }

    Vector *linesVector = txtLoaderReadFileLines(txtFileLoader);
    if (index < 0 || index >= vectorGetLength(linesVector)) {
        destroyVector(linesVector);
#ifdef C_DATASTRUCTURES_ERRORSTESTSTRUCT_H
        ERROR_TEST->errorCode = INVALID_ARG;
        return;
#else
        fprintf(stderr, INVALID_ARG_MESSAGE, "new line index", "text file loader");
        exit(INVALID_ARG);
#endif
    }

    stringChangeStringC(vectorGet(linesVector, index), line);

    txtLoaderOpenFile(txtFileLoader, "w");

    for (int i = 0; i < vectorGetLength(linesVector); i++)
        fprintf(txtFileLoader->fileP, "%s%c", ((String *) vectorGet(linesVector, i))->string,
                i != vectorGetLength(linesVector) - 1 ? '\n' : '\0');


    destroyVector(linesVector);

    fclose(txtFileLoader->fileP);

}


/** This function will take a string and an index,
 * then it will update the line in the provided index with the passed string.
 *
 * @param txtFileLoader the text file loader pointer
 * @param line the new line string
 * @param index the index of the line that will be updated
 */

void txtLoaderUpdateLineS(TxtFileLoader *txtFileLoader, String *line, int index) {

    if (txtFileLoader == NULL) {
#ifdef C_DATASTRUCTURES_ERRORSTESTSTRUCT_H
        ERROR_TEST->errorCode = NULL_POINTER;
        return;
#else
        fprintf(stderr, NULL_POINTER_MESSAGE, "loader", "text file loader");
        exit(NULL_POINTER);
#endif
    } else if (line == NULL) {
#ifdef C_DATASTRUCTURES_ERRORSTESTSTRUCT_H
        ERROR_TEST->errorCode = INVALID_ARG;
        return;
#else
        fprintf(stderr, INVALID_ARG_MESSAGE, "new string", "text file loader");
        exit(INVALID_ARG);
#endif
    }

    Vector *linesVector = txtLoaderReadFileLines(txtFileLoader);
    if (index < 0 || index >= vectorGetLength(linesVector)) {
        destroyVector(linesVector);
#ifdef C_DATASTRUCTURES_ERRORSTESTSTRUCT_H
        ERROR_TEST->errorCode = INVALID_ARG;
        return;
#else
        fprintf(stderr, INVALID_ARG_MESSAGE, "new line index", "text file loader");
        exit(INVALID_ARG);
#endif
    }

    stringChangeStringS(vectorGet(linesVector, index), line);

    txtLoaderOpenFile(txtFileLoader, "w");

    for (int i = 0; i < vectorGetLength(linesVector); i++)
        fprintf(txtFileLoader->fileP, "%s%c", ((String *) vectorGet(linesVector, i))->string,
                i != vectorGetLength(linesVector) - 1 ? '\n' : '\0');


    destroyVector(linesVector);

    fclose(txtFileLoader->fileP);

}


/** This function will take an index,
 * then it will remove the line at the provided index.
 *
 * @param txtFileLoader the text file loader pointer
 * @param index the index of the line that will be removed
 */

void txtLoaderRemoveLine(TxtFileLoader *txtFileLoader, int index) {

    if (txtFileLoader == NULL) {
#ifdef C_DATASTRUCTURES_ERRORSTESTSTRUCT_H
        ERROR_TEST->errorCode = NULL_POINTER;
        return;
#else
        fprintf(stderr, NULL_POINTER_MESSAGE, "loader", "text file loader");
        exit(NULL_POINTER);
#endif
    }

    Vector *linesVector = txtLoaderReadFileLines(txtFileLoader);
    if (index < 0 || index >= vectorGetLength(linesVector)) {
        destroyVector(linesVector);
#ifdef C_DATASTRUCTURES_ERRORSTESTSTRUCT_H
        ERROR_TEST->errorCode = INVALID_ARG;
        return;
#else
        fprintf(stderr, INVALID_ARG_MESSAGE, "new line index", "text file loader");
        exit(INVALID_ARG);
#endif
    }

    vectorRemoveAtIndex(linesVector, index);

    txtLoaderOpenFile(txtFileLoader, "w");

    for (int i = 0; i < vectorGetLength(linesVector); i++)
        fprintf(txtFileLoader->fileP, "%s%c", ((String *) vectorGet(linesVector, i))->string,
                i != vectorGetLength(linesVector) - 1 ? '\n' : '\0');


    destroyVector(linesVector);

    fclose(txtFileLoader->fileP);

}


/** This function will clear the text file.
 *
 * @param txtFileLoader the text file loader pointer
 */

void txtLoaderClearFile(TxtFileLoader *txtFileLoader) {

    if (txtFileLoader == NULL) {
#ifdef C_DATASTRUCTURES_ERRORSTESTSTRUCT_H
        ERROR_TEST->errorCode = NULL_POINTER;
        return;
#else
        fprintf(stderr, NULL_POINTER_MESSAGE, "loader", "text file loader");
        exit(NULL_POINTER);
#endif
    }


    txtLoaderOpenFile(txtFileLoader, "w");

    fflush(txtFileLoader->fileP);

    fclose(txtFileLoader->fileP);

}


/** This function will change the file direction of text file loader.
 *
 * @param txtFileLoader the text file loader pointer
 * @param newFileDir the new direction char array pointer
 */

void txtLoaderChangeFile(TxtFileLoader *txtFileLoader, char *newFileDir) {

    free(txtFileLoader->dir);

    txtFileLoader->dir = (char *) malloc(sizeof(char) * (strlen(newFileDir) + 1));
    if (txtFileLoader->dir == NULL) {
#ifdef C_DATASTRUCTURES_ERRORSTESTSTRUCT_H
        ERROR_TEST->errorCode = FAILED_ALLOCATION;
        return;
#else
        fprintf(stderr, FAILED_ALLOCATION_MESSAGE, "file direction", "text file loader");
        exit(FAILED_ALLOCATION);
#endif
    }

    txtFileLoader->dir = strcpy(txtFileLoader->dir, newFileDir);
    if (txtFileLoader->dir == NULL) {
#ifdef C_DATASTRUCTURES_ERRORSTESTSTRUCT_H
        ERROR_TEST->errorCode = FAILED_COPY;
        return;
#else
        fprintf(stderr, FAILED_COPY_MESSAGE, "file direction", "text file loader");
        exit(FAILED_COPY);
#endif
    }

}


/** This function will destroy and free the passed text file loader.
 *
 * @param txtFileLoader the text file loader pointer
 */

void destroyTxtFileLoader(void *txtFileLoader) {

    if (txtFileLoader == NULL) {
#ifdef C_DATASTRUCTURES_ERRORSTESTSTRUCT_H
        ERROR_TEST->errorCode = NULL_POINTER;
        return;
#else
        fprintf(stderr, NULL_POINTER_MESSAGE, "loader", "text file loader");
        exit(NULL_POINTER);
#endif
    }

    free( ((TxtFileLoader *) txtFileLoader)->dir );
    free(txtFileLoader);

}