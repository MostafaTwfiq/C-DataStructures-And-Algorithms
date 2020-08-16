#include "CharArrayAlgTest.h"
#include "../../../CuTest/CuTest.h"
#include "../../../../System/Utils.h"
#include "../../../../Algorithms/ArraysAlg/Headers/CharArrayAlg.h"
#include "../../../../DataStructure/Lists/Headers/Vector.h"
#include "../../../../DataStructure/Strings/Headers/String.h"


void testCharArrayAlgIsSubString(CuTest *cuTest) {

    isSubString(NULL, 0, NULL, 0);
    CuAssertIntEquals(cuTest, NULL_POINTER, ERROR_TEST->errorCode);

    isSubString("", 0, NULL, 0);
    CuAssertIntEquals(cuTest, NULL_POINTER, ERROR_TEST->errorCode);

    isSubString("", -1, "", -1);
    CuAssertIntEquals(cuTest, INVALID_ARG, ERROR_TEST->errorCode);


    char *sentence = "what a nice day to program";
    int sentenceLength = strlen(sentence);

    CuAssertIntEquals(cuTest, 1, isSubString(sentence, sentenceLength, "what", strlen("what")));
    CuAssertIntEquals(cuTest, 1, isSubString(sentence, sentenceLength, "a", strlen("a")));
    CuAssertIntEquals(cuTest, 1, isSubString(sentence, sentenceLength, " a ", strlen(" a ")));
    CuAssertIntEquals(cuTest, 1, isSubString(sentence, sentenceLength, "nice", strlen("nice")));
    CuAssertIntEquals(cuTest, 1, isSubString(sentence, sentenceLength, " day ", strlen(" day ")));
    CuAssertIntEquals(cuTest, 1, isSubString(sentence, sentenceLength, "to", strlen("to")));
    CuAssertIntEquals(cuTest, 1, isSubString(sentence, sentenceLength, "program", strlen("program")));
    CuAssertIntEquals(cuTest, 1, isSubString(sentence, sentenceLength, "a nice day", strlen("a nice day")));
    CuAssertIntEquals(cuTest, 1, isSubString(sentence, sentenceLength, sentence, sentenceLength));
    CuAssertIntEquals(cuTest, 1, isSubString(sentence, sentenceLength, "", strlen("")));
    CuAssertIntEquals(cuTest, 0, isSubString(sentence, sentenceLength, "what a nice day to program.",
                                             strlen("what a nice day to program.")));
    CuAssertIntEquals(cuTest, 0, isSubString(sentence, sentenceLength, "z", strlen("z")));
    CuAssertIntEquals(cuTest, 0, isSubString(sentence, sentenceLength, "what a good day", strlen("what a good day")));

}


void testCharArrayReverseWords(CuTest *cuTest) {

    charArrayReverseWords(NULL);
    CuAssertIntEquals(cuTest, NULL_POINTER, ERROR_TEST->errorCode);


    char sentence1[] = "one two three";
    char sentence2[] = "   one two three     four      five         six    ";
    char sentence3[] = "";
    char sentence4[] = "one";
    char sentence5[] = "   one    ";


    charArrayReverseWords(sentence1);
    CuAssertStrEquals(cuTest, "three two one", sentence1);

    charArrayReverseWords(sentence2);
    CuAssertStrEquals(cuTest, "six five four three two one", sentence2);

    charArrayReverseWords(sentence3);
    CuAssertStrEquals(cuTest, "", sentence3);

    charArrayReverseWords(sentence4);
    CuAssertStrEquals(cuTest, "one", sentence4);

    charArrayReverseWords(sentence5);
    CuAssertStrEquals(cuTest, "one", sentence5);


}


void testCharArrTrimStartC(CuTest *cuTest) {

    charArrTrimStartC(NULL, NULL);
    CuAssertIntEquals(cuTest, NULL_POINTER, ERROR_TEST->errorCode);

    charArrTrimStartC("", NULL);
    CuAssertIntEquals(cuTest, INVALID_ARG, ERROR_TEST->errorCode);


    char sentence1[] = "   \t \t \n\n   %% $$ # word";
    char sentence2[] = "  word";
    char sentence3[] = "   \t \t \n\n   %% $$ # word    \t \t \n\n   %% $$ # ";
    char sentence4[] = " $$ word $$ ";


    charArrTrimStartC(sentence1, " \t\nn%$#");
    CuAssertStrEquals(cuTest, "word", sentence1);

    charArrTrimStartC(sentence2, " ");
    CuAssertStrEquals(cuTest, "word", sentence2);

    charArrTrimStartC(sentence3, "\t \n %$#");
    CuAssertStrEquals(cuTest, "word    \t \t \n\n   %% $$ # ", sentence3);

    charArrTrimStartC(sentence4, " ");
    CuAssertStrEquals(cuTest, "$$ word $$ ", sentence4);


}


void testCharArrTrimStart(CuTest *cuTest) {

    charArrTrimStart(NULL);
    CuAssertIntEquals(cuTest, NULL_POINTER, ERROR_TEST->errorCode);


    char sentence1[] = "   \t \t \n\n   %% $$ # word";
    char sentence2[] = "  word";
    char sentence3[] = "   \t \t \n\n   %% $$ # word    \t \t \n\n   %% $$ # ";
    char sentence4[] = " $$ word $$ ";


    charArrTrimStart(sentence1);
    CuAssertStrEquals(cuTest, "%% $$ # word", sentence1);

    charArrTrimStart(sentence2);
    CuAssertStrEquals(cuTest, "word", sentence2);

    charArrTrimStart(sentence3);
    CuAssertStrEquals(cuTest, "%% $$ # word    \t \t \n\n   %% $$ # ", sentence3);

    charArrTrimStart(sentence4);
    CuAssertStrEquals(cuTest, "$$ word $$ ", sentence4);


}


void testCharArrTrimEndC(CuTest *cuTest) {

    charArrTrimEndC(NULL, NULL);
    CuAssertIntEquals(cuTest, NULL_POINTER, ERROR_TEST->errorCode);

    charArrTrimEndC("", NULL);
    CuAssertIntEquals(cuTest, INVALID_ARG, ERROR_TEST->errorCode);


    char sentence1[] = "word    \t \t \n\n   %% $$ # ";
    char sentence2[] = "word ";
    char sentence3[] = "   \t \t \n\n   %% $$ # word    \t \t \n\n   %% $$ # ";
    char sentence4[] = " $$ word $$ ";


    charArrTrimEndC(sentence1, " \t\nn%$#");
    CuAssertStrEquals(cuTest, "word", sentence1);

    charArrTrimEndC(sentence2, " ");
    CuAssertStrEquals(cuTest, "word", sentence2);

    charArrTrimEndC(sentence3, "\t \n %$#");
    CuAssertStrEquals(cuTest, "   \t \t \n\n   %% $$ # word", sentence3);

    charArrTrimEndC(sentence4, " ");
    CuAssertStrEquals(cuTest, " $$ word $$", sentence4);


}


void testCharArrTrimEnd(CuTest *cuTest) {

    charArrTrimEnd(NULL);
    CuAssertIntEquals(cuTest, NULL_POINTER, ERROR_TEST->errorCode);


    char sentence1[] = "word  %% $$ #   \t \t \n\n  ";
    char sentence2[] = "word  ";
    char sentence3[] = "   %% $$ # word    \t \t \n\n   %% $$ # \t \t \n\n ";
    char sentence4[] = " $$ word $$ ";


    charArrTrimEnd(sentence1);
    CuAssertStrEquals(cuTest, "word  %% $$ #", sentence1);

    charArrTrimEnd(sentence2);
    CuAssertStrEquals(cuTest, "word", sentence2);

    charArrTrimEnd(sentence3);
    CuAssertStrEquals(cuTest, "   %% $$ # word    \t \t \n\n   %% $$ #", sentence3);

    charArrTrimEnd(sentence4);
    CuAssertStrEquals(cuTest, " $$ word $$", sentence4);


}


void testCharArrTrimC(CuTest *cuTest) {

    charArrTrimC(NULL, NULL);
    CuAssertIntEquals(cuTest, NULL_POINTER, ERROR_TEST->errorCode);

    charArrTrimC("", NULL);
    CuAssertIntEquals(cuTest, INVALID_ARG, ERROR_TEST->errorCode);


    char sentence1[] = "    \t \t \n\n   %% $$ #  word    \t \t \n\n   %% $$ # ";
    char sentence2[] = "   word    ";
    char sentence3[] = "   \t \t \n\n   %% $$ # word    \t \t \n\n   %% $$ # ";
    char sentence4[] = " $$ word $$ ";


    charArrTrimC(sentence1, " \t\nn%$#");
    CuAssertStrEquals(cuTest, "word", sentence1);

    charArrTrimC(sentence2, " ");
    CuAssertStrEquals(cuTest, "word", sentence2);

    charArrTrimC(sentence3, "\t \n %$#");
    CuAssertStrEquals(cuTest, "word", sentence3);

    charArrTrimC(sentence4, " ");
    CuAssertStrEquals(cuTest, "$$ word $$", sentence4);


}


void testCharArrTrim(CuTest *cuTest) {

    charArrTrim(NULL);
    CuAssertIntEquals(cuTest, NULL_POINTER, ERROR_TEST->errorCode);

    char sentence1[] = "    \t \t \n\n   %% $$ #  word    \t \t \n\n   %% $$ #   \t\n ";
    char sentence2[] = "   word    ";
    char sentence3[] = "   \t \t \n\n   %% $$ # word    \t \t \n\n   %% $$ #   ";
    char sentence4[] = " $$ word $$ ";


    charArrTrim(sentence1);
    CuAssertStrEquals(cuTest, "%% $$ #  word    \t \t \n\n   %% $$ #", sentence1);

    charArrTrim(sentence2);
    CuAssertStrEquals(cuTest, "word", sentence2);

    charArrTrim(sentence3);
    CuAssertStrEquals(cuTest, "%% $$ # word    \t \t \n\n   %% $$ #", sentence3);

    charArrTrim(sentence4);
    CuAssertStrEquals(cuTest, "$$ word $$", sentence4);


}


void testCharArrContainsChar(CuTest *cuTest) {

    charArrContainsChar(NULL, '\0');
    CuAssertIntEquals(cuTest, NULL_POINTER, ERROR_TEST->errorCode);


    char sentence[] = "i love programming";
    char *tempPointer = sentence;
    while (*tempPointer != '\0')
        CuAssertIntEquals(cuTest, 1, charArrContainsChar(sentence, *tempPointer++));


    char sentence2[] = "bcdfhjkxz";
    char *tempPointer2 = sentence2;
    while (*tempPointer2 != '\0')
        CuAssertIntEquals(cuTest, 0, charArrContainsChar(sentence, *tempPointer2++));


}


void testCharArrRemoveCharacters(CuTest *cuTest) {

    charArrRemoveCharacters(NULL, NULL);
    CuAssertIntEquals(cuTest, NULL_POINTER, ERROR_TEST->errorCode);

    charArrRemoveCharacters("", NULL);
    CuAssertIntEquals(cuTest, INVALID_ARG, ERROR_TEST->errorCode);

    char sentence[] = "iff lovezz programmingddtt";
    charArrRemoveCharacters(sentence, "fzdt");

    CuAssertStrEquals(cuTest, "i love programming", sentence);


}


void testCharArrIsInteger(CuTest *cuTest) {

    isInteger(NULL);
    CuAssertIntEquals(cuTest, NULL_POINTER, ERROR_TEST->errorCode);


    CuAssertIntEquals(cuTest, 1, isInteger("123"));
    CuAssertIntEquals(cuTest, 1, isInteger("0000"));
    CuAssertIntEquals(cuTest, 1, isInteger("0"));
    CuAssertIntEquals(cuTest, 1, isInteger("-1233"));
    CuAssertIntEquals(cuTest, 1, isInteger("-0"));
    CuAssertIntEquals(cuTest, 1, isInteger("+123"));

    CuAssertIntEquals(cuTest, 0, isInteger("123.43"));
    CuAssertIntEquals(cuTest, 0, isInteger("--1234"));
    CuAssertIntEquals(cuTest, 0, isInteger("++123"));
    CuAssertIntEquals(cuTest, 0, isInteger("123ljkj1123"));
    CuAssertIntEquals(cuTest, 0, isInteger(";lk;lk"));
    CuAssertIntEquals(cuTest, 0, isInteger(""));

}


void testCharArrayIsFloatingPointNum(CuTest *cuTest) {

    isFloatingPointNum(NULL);
    CuAssertIntEquals(cuTest, NULL_POINTER, ERROR_TEST->errorCode);


    CuAssertIntEquals(cuTest, 1, isFloatingPointNum("123"));
    CuAssertIntEquals(cuTest, 1, isFloatingPointNum("0000"));
    CuAssertIntEquals(cuTest, 1, isFloatingPointNum("0"));
    CuAssertIntEquals(cuTest, 1, isFloatingPointNum("-1233"));
    CuAssertIntEquals(cuTest, 1, isFloatingPointNum("-0"));
    CuAssertIntEquals(cuTest, 1, isFloatingPointNum("+123"));
    CuAssertIntEquals(cuTest, 1, isFloatingPointNum("0.345435345"));
    CuAssertIntEquals(cuTest, 1, isFloatingPointNum(".34543535"));
    CuAssertIntEquals(cuTest, 1, isFloatingPointNum("+.4345435"));
    CuAssertIntEquals(cuTest, 1, isFloatingPointNum("+1231.123213"));

    CuAssertIntEquals(cuTest, 0, isFloatingPointNum("--1234"));
    CuAssertIntEquals(cuTest, 0, isFloatingPointNum("++123"));
    CuAssertIntEquals(cuTest, 0, isFloatingPointNum("123ljkj1123"));
    CuAssertIntEquals(cuTest, 0, isFloatingPointNum(";lk;lk"));
    CuAssertIntEquals(cuTest, 0, isFloatingPointNum(""));

}


void testCharArrSumASCII(CuTest *cuTest) {

    charArrSumASCII(NULL);
    CuAssertIntEquals(cuTest, NULL_POINTER, ERROR_TEST->errorCode);

    char words[5][20] = {"i love programming", "data structure", "algorithms", "", "test"};

    for (int i = 0; i < 5; i++) {
        int counter = 0;
        int length = strlen(words[i]);
        for (int j = 0; j < length; j++)
            counter += words[i][j];

        CuAssertIntEquals(cuTest, counter, charArrSumASCII(words[i]));

    }

}


void testCharArrHashFun(CuTest *cuTest) {

    charArrHashFun(NULL);
    CuAssertIntEquals(cuTest, NULL_POINTER, ERROR_TEST->errorCode);

    char words[5][20] = {"i love programming", "data structure", "algorithms", "", "test"};

    for (int i = 0; i < 5; i++) {
        int counter = 0;
        int length = strlen(words[i]);
        for (int j = 0; j < length; j++)
            counter += words[i][j];

        CuAssertIntEquals(cuTest, counter, charArrHashFun(words[i]));

    }

}


void testGenerateCharPointerP(CuTest *cuTest) {

    generateCharPointerP(NULL, 0);
    CuAssertIntEquals(cuTest, NULL_POINTER, ERROR_TEST->errorCode);

    generateCharPointerP("", -1);
    CuAssertIntEquals(cuTest, INVALID_ARG, ERROR_TEST->errorCode);

    char words[5][20] = {"i love programming", "data structure", "algorithms", "", "test"};

    for (int i = 0; i < 5; i++) {
        char *generatedArr = generateCharPointerP(words[i], strlen(words[i]));

        CuAssertStrEquals(cuTest, generatedArr, words[i]);

        free(generatedArr);
    }

}


void testGenerateCharPointerC(CuTest *cuTest) {

    char sentence[] = "i love programming.";

    int length = strlen(sentence);
    for (int i = 0; i < length; i++) {
        char *generatedChar = generateCharPointerC(sentence[i]);

        CuAssertIntEquals(cuTest, (int) *generatedChar, (int) sentence[i]);

        free(generatedChar);
    }

}


void testCharIsAlphabetC(CuTest *cuTest) {

    char letters[] = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ";

    char notLetters[] = "!@#@#$^%$&*(((*))_+\t\n  ""::{}][';/.|";

    int length = strlen(letters);
    for (int i = 0; i < length; i++)
        CuAssertIntEquals(cuTest, 1, isAlphabetC(letters[i]));


    int notLetterLength = strlen(notLetters);
    for (int i = 0; i < notLetterLength; i++)
        CuAssertIntEquals(cuTest, 0, isAlphabetC(notLetters[i]));

}


void testCharIsAlphabetP(CuTest *cuTest) {

    isAlphabetP(NULL);
    CuAssertIntEquals(cuTest, NULL_POINTER, ERROR_TEST->errorCode);


    char letters[] = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ";

    char notLetters[] = "!@#@#$^%$&*(((*))_+\t\n  ""::{}][';/.|";

    int length = strlen(letters);
    for (int i = 0; i < length; i++)
        CuAssertIntEquals(cuTest, 1, isAlphabetP(letters + i));


    int notLetterLength = strlen(notLetters);
    for (int i = 0; i < notLetterLength; i++)
        CuAssertIntEquals(cuTest, 0, isAlphabetP(notLetters + i));

}


void testCharComparator(CuTest *cuTest) {


    CuAssertIntEquals(cuTest, 0, charComparator('a', 'a'));

    CuAssertIntEquals(cuTest, -1, charComparator('a', 'b') < 0 ? -1 : 1);

    CuAssertIntEquals(cuTest, 1, charComparator('z', 'b') < 0 ? -1 : 1);

    CuAssertIntEquals(cuTest, -1, charComparator('1', '2') < 0 ? -1 : 1);

    CuAssertIntEquals(cuTest, 1, charComparator('4', '3') < 0 ? -1 : 1);


}


void testCharComparatorP(CuTest *cuTest) {


    int c1, c2;

    c1 = 'a', c2 = 'a';
    CuAssertIntEquals(cuTest, 0, charComparatorP(&c1, &c2));

    c1 = 'a', c2 = 'b';
    CuAssertIntEquals(cuTest, -1, charComparatorP(&c1, &c2) < 0 ? -1 : 1);

    c1 = 'z', c2 = 'b';
    CuAssertIntEquals(cuTest, 1, charComparatorP(&c1, &c2) < 0 ? -1 : 1);

    c1 = '1', c2 = '2';
    CuAssertIntEquals(cuTest, -1, charComparatorP(&c1, &c2) < 0 ? -1 : 1);


    c1 = '4', c2 = '3';
    CuAssertIntEquals(cuTest, 1, charComparatorP(&c1, &c2) < 0 ? -1 : 1);

}


void testMostRepeatedCharacter(CuTest *cuTest) {


    mostRepeatedCharacter(NULL);
    CuAssertIntEquals(cuTest, NULL_POINTER, ERROR_TEST->errorCode);


    CuAssertIntEquals(cuTest, (int) 'd', (int) mostRepeatedCharacter("aabbcccddddee"));

    CuAssertIntEquals(cuTest, (int) 'a', (int) mostRepeatedCharacter("a"));

    CuAssertIntEquals(cuTest, (int) 'b', (int) mostRepeatedCharacter("aabb"));

    CuAssertIntEquals(cuTest, (int) 'k', (int) mostRepeatedCharacter("kkkk"));

    CuAssertIntEquals(cuTest, (int) '\0', (int) mostRepeatedCharacter(""));


}


void testCharArrSplitC(CuTest *cuTest) {


    charArrSplitC(NULL, NULL);
    CuAssertIntEquals(cuTest, NULL_POINTER, ERROR_TEST->errorCode);

    charArrSplitC("", NULL);
    CuAssertIntEquals(cuTest, INVALID_ARG, ERROR_TEST->errorCode);


    char sentence[] = "   i   \n \t  % love  %%%% programming ## $ % ! \n \t  so much\n<3%%.$$";
    char words[7][12] = {"i", "love", "programming", "so", "much", "<3", "."};


    Vector *wordsVector = charArrSplitC(sentence, " \n\t%#!$");
    CuAssertIntEquals(cuTest, 7, vectorGetLength(wordsVector));

    for (int i = 0; i < vectorGetLength(wordsVector); i++)
        CuAssertStrEquals(cuTest, words[i], vectorGet(wordsVector, i));


    destroyVector(wordsVector);

}


void testCharArrSplitS(CuTest *cuTest) {


    charArrSplitS(NULL, NULL);
    CuAssertIntEquals(cuTest, NULL_POINTER, ERROR_TEST->errorCode);

    charArrSplitS("", NULL);
    CuAssertIntEquals(cuTest, INVALID_ARG, ERROR_TEST->errorCode);


    char sentence[] = "   i   \n \t  % love  %%%% programming ## $ % ! \n \t  so much\n<3%%.$$";
    char words[7][12] = {"i", "love", "programming", "so", "much", "<3", "."};


    Vector *wordsVector = charArrSplitS(sentence, " \n\t%#!$");
    CuAssertIntEquals(cuTest, 7, vectorGetLength(wordsVector));

    for (int i = 0; i < vectorGetLength(wordsVector); i++)
        CuAssertStrEquals(cuTest, words[i], ((String *) vectorGet(wordsVector, i))->string);


    destroyVector(wordsVector);

}


CuSuite *createCharArrayAlgTestsSuite(void) {

    CuSuite *suite = CuSuiteNew();

    SUITE_ADD_TEST(suite, testCharArrayAlgIsSubString);
    SUITE_ADD_TEST(suite, testCharArrayReverseWords);
    SUITE_ADD_TEST(suite, testCharArrTrimStartC);
    SUITE_ADD_TEST(suite, testCharArrTrimStart);
    SUITE_ADD_TEST(suite, testCharArrTrimEndC);
    SUITE_ADD_TEST(suite, testCharArrTrimEnd);
    SUITE_ADD_TEST(suite, testCharArrTrimC);
    SUITE_ADD_TEST(suite, testCharArrTrim);
    SUITE_ADD_TEST(suite, testCharArrContainsChar);
    SUITE_ADD_TEST(suite, testCharArrRemoveCharacters);
    SUITE_ADD_TEST(suite, testCharArrIsInteger);
    SUITE_ADD_TEST(suite, testCharArrayIsFloatingPointNum);
    SUITE_ADD_TEST(suite, testCharArrSumASCII);
    SUITE_ADD_TEST(suite, testCharArrHashFun);
    SUITE_ADD_TEST(suite, testGenerateCharPointerP);
    SUITE_ADD_TEST(suite, testGenerateCharPointerC);
    SUITE_ADD_TEST(suite, testCharIsAlphabetC);
    SUITE_ADD_TEST(suite, testCharIsAlphabetP);
    SUITE_ADD_TEST(suite, testCharComparator);
    SUITE_ADD_TEST(suite, testCharComparatorP);
    SUITE_ADD_TEST(suite, testMostRepeatedCharacter);
    SUITE_ADD_TEST(suite, testCharArrSplitC);
    SUITE_ADD_TEST(suite, testCharArrSplitS);

    return suite;

}


void charArrayAlgUnitTest(void) {

    ERROR_TEST = (ErrorTestStruct *) malloc(sizeof(ErrorTestStruct));

    CuString *output = CuStringNew();
    CuStringAppend(output, "**Char Array Algorithms Test**\n");

    CuSuite *suite = createCharArrayAlgTestsSuite();

    CuSuiteRun(suite);
    CuSuiteSummary(suite, output);
    CuSuiteDetails(suite, output);
    printf("%s\n", output->buffer);

    free(ERROR_TEST);

}