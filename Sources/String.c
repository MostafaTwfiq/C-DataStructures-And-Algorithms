#include "../Headers/String.h"





/** This function will take the initial length of the string as a parameter,
    then it will initialize a new String pointer and return it.
 * @param initialLength
 * @return
 */

String *stringInitialization(int initialLength) {
    String *myString = (String *) malloc(sizeof(String));
    myString->string = (char *) malloc(sizeof(char) * (initialLength + 1) );
    myString->string[0] = '\0';
    myString->count = 0;
    myString->length = initialLength;

    return myString;
}




/** This function will take the string address, and the new character as a parameter,
    then it will put the new character in the end of the string.
 * @param myString
 * @param c
 */

void stringAddCharAtLast(String *myString, char c) {
    if (myString == NULL) {
        printf("Illegal argument, the string is NULL.");
        exit(-2);
    }

    if (myString->count == myString->length) {
        myString->length *= 2;
        myString->string = realloc(myString->string, sizeof(char) * (myString->length + 1));
    }

    myString->string[myString->count++] = c;
    myString->string[myString->count] = '\0';
}




/** This function will take the string address, index, and the new character as a parameters,
    then it will put the new character in the given index.
 * If the index is out of the string range the program will terminate.
 * @param myString
 * @param index
 * @param c
 */

void stringAddCharAtIndex(String *myString, int index, char c) {
    if (myString == NULL) {
        printf("Illegal argument, the string is NULL.");
        exit(-2);
    } else if (myString->count <= index || index < 0) {
        printf("index is out of the string range.");
        exit(-2);
    }

    myString->string[index] = c;

}




/** This function will take the string address, and the index as a parameter,
    then it will remove the character in the given index.
 * If the index is out of the string range the program will terminate.
 * @param myString
 * @param index
 */

void stringRemoveCharAtIndex(String *myString, int index) {
    if (myString == NULL) {
        printf("Illegal argument, the string is NULL.");
        exit(-2);
    } else if (myString->count <= index || index < 0) {
        printf("index is out of the string range.");
        exit(-2);
    }

    for (int i = index; i < myString->count; i++)
        myString->string[i] = myString->string[i + 1];

    myString->count--;
}




/** This function will take the string address, and the new char pointer array as a parameters,
    then it will add the new array of characters in the end of the string.
 * @param myString
 * @param newString
 */

void stringAddStringAtLast(String *myString, char *newString) {
    if (myString == NULL || newString == NULL) {
        printf("Illegal argument, the string is NULL.");
        exit(-2);
    }

    char *currentChar = newString;
    while (*currentChar != '\0') {
        stringAddCharAtLast(myString, *currentChar);
        currentChar++;
    }

}




/** This function will take the string address, and the new char pointer array as a parameters,
    then it will change the string to the new char pointer array.
 * @param string
 * @param newString
 */

void stringChangeStringByCharArray(String *string, char *newString) {
    if (string == NULL || newString == NULL) {
        printf("Illegal argument, the string is NULL.");
        exit(-2);
    }

    string->count = 0;

    while (*newString != '\0')
        stringAddCharAtLast(string, *newString++);

}



/** This function will take string address, and the the new string address as a parameters,
    then it will change the first string to the second string.
 * @param string
 * @param newString
 */

void stringChangeStringByString(String *string, String *newString) {
    if (string == NULL || newString == NULL) {
        printf("Illegal argument, the string is NULL.");
        exit(-2);
    }

    string->count = 0;
    string->string[string->count] = '\0';

    for (int i = 0; i < stringGetLength(newString); i++)
        stringAddCharAtLast(string, stringGetCharAtIndex(newString, i));


}




/** This function will take the string address, and the character as a parameters,
    then it will return the first occur of this character in the string and will return it's index,
    other wise it will return minus one (-1).
 * @param myString
 * @param c
 * @return
 */

int stringFindCharIndex(String *myString, char c) {
    if (myString == NULL) {
        printf("Illegal argument, the string is NULL.");
        exit(-2);
    }

    for (int i = 0; i < myString->count; i++) {
        if (myString->string[i] == c)
            return i;

    }

    return -1;
}




/** This function will take the string address, and the index as a parameters,
    then it will return the character at the given index.
 * If the index is out of the string range the program will terminate.
 * @param myString
 * @param index
 * @return
 */

char stringGetCharAtIndex(String *myString, int index) {
    if (myString == NULL) {
        printf("Illegal argument, the string is NULL.");
        exit(-2);
    } else if (myString->count <= index || index < 0) {
        printf("index is out of the string range.");
        exit(-2);
    }

    return myString->string[index];
}




/** This function will take the string address, and a char pointer array as a parameters,
    then it will return one (1) if the second char array is a substring of the first string,
    other wise it will return zero (0).
 * @param myString
 * @param string
 * @return
 */

int stringSubString(String *myString, char *string) {
    if (myString == NULL || string == NULL) {
        printf("Illegal argument, the string is NULL.");
        exit(-2);
    }

    int stringLength = strlen(string);

    if (string == NULL || stringLength > myString->count)
        return 0;

    for (int i = 0; i <= myString->count - stringLength; i++) {
        for (int j = 0; j < stringLength; j++) {
            if (myString->string[i + j] != string[j])
                break;

            else if (j == stringLength - 1)
                return 1;

        }
    }

    return 0;
}




/** This function will take the string address as a parameter,
 * then it will convert it to a char pointer array, and return it.
 * @param myString
 * @return
 */

char *stringToArrayOfCharacters(String *myString) {
    if (myString == NULL) {
        printf("Illegal argument, the string is NULL.");
        exit(-2);
    }

    char *arrayOfCharacters = (char *) malloc(sizeof(char) * (myString->count + 1) );

    for (int i = 0; i <= myString->count; i++)
        arrayOfCharacters[i] = myString->string[i];

    return arrayOfCharacters;
}




/** This method will take the string address, start index, and end index as a parameters,
    then it will convert the string from the start index to the end index to a char pointer array,
    then return it.
 * @param myString
 * @param startIndex
 * @param endIndex
 * @return
 */

char *stringGetStringBetweenTwoIndices(String *myString, int startIndex, int endIndex) {
    if (myString == NULL) {
        printf("Illegal argument, the string is NULL.");
        exit(-2);
    }

    if (startIndex > endIndex
        || startIndex < 0 || startIndex >= myString->count
        || endIndex < 0 || endIndex >= myString->count) {

        return NULL;
    }

    char *string = (char *) malloc(sizeof(char) * (endIndex - startIndex + 2) );
    string[endIndex - startIndex + 1] = '\0';
    for (int i = 0; i <= endIndex - startIndex; i++)
        string[i] = myString->string[startIndex + i];

    return string;

}




/** This function will take the string address as a parameter,
    then it will return the string length.
 * @param myString
 * @return
 */

int stringGetLength(String *myString) {
    if (myString == NULL) {
        printf("Illegal argument, the string is NULL.");
        exit(-2);
    }

    return myString->count;
}




/** This function will take the string address, and a char pointer array as a parameters,
    then it will return one (1) if the string is equal to the char array,
    other wise it will return zero (0).
 * @param myString
 * @param string
 * @return
 */

int stringIsEqualsToCharArray(String *myString, char *string) {
    if (myString == NULL) {
        printf("Illegal argument, the string is NULL.");
        exit(-2);
    }

    int stringLength = strlen(string);
    if (myString->count != stringLength)
        return 0;

    for (int i = 0; i < myString->count; i++) {

        if (myString->string[i] != string[i])
            return 0;

    }

    return 1;
}




/** This function will take the string address, and second string address as a parameters,
    then it will return one (1) if the first string is equal to the second string,
    other wise it will return zero (0).
 * @param myString
 * @param string
 * @return
 */

int stringIsEqualsToMyString(String *myString, String *string) {
    if (myString == NULL || string == NULL) {
        printf("Illegal argument, the string is NULL.");
        exit(-2);
    }

    int stringLength = stringGetLength(string);
    if (string == NULL || myString->count != stringLength)
        return 0;

    for (int i = 0; i < stringLength; i++) {

        if (myString->string[i] != string->string[i])
            return 0;

    }

    return 1;
}




/** This function will take the string address as a paramter,
    then it will trim this string (remove spaces and tabs).
 * @param myString
 */

void stringTrim(String *myString) {
    if (myString == NULL)
        return;

    while (1) {
        if (*myString->string == ' ' || *myString->string == '\t') {

            for (int i = 0; i < stringGetLength(myString); i++)
                myString->string[i] = myString->string[i + 1];

            myString->count--;

        }

        else
            break;

    }

    for (int i = stringGetLength(myString) - 1; i >= 0; i--) {

        if (myString->string[i] == ' ' || *myString->string == '\t') {
            myString->string[i] = '\0';
            myString->count--;
        }
        else
            break;

    }
}




/** This function will take the string address as a parameter,
 * then it will read the input from the stdin file and put it in the string.
 * @param myString
 */

void stringFGetS(String *myString) {
    if (myString == NULL) {
        printf("Illegal argument, the string is NULL.");
        exit(-2);
    }


    char c;

    while (1) {
        c = fgetc(stdin);

        if (c == '\n')
            break;

        stringAddCharAtLast(myString, c);
    }

    fseek(stdin, 0, SEEK_END);
}




/** This function will take the string address as a parameter,
 * then it will destroy and free the string from the memory.
 * @param myString
 */

void destroyString(String *myString) {
    if (myString == NULL) {
        printf("Illegal argument, the string is NULL.");
        exit(-2);
    }

    free(myString->string);
    free(myString);
}