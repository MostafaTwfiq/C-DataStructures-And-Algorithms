

#include "../../../DataStructure/Lists/Headers/Vector.h"
#include "../../../System/Utils.h"
#include "../../CuTest/CuTest.h"

typedef struct TestStruct{
    int errorCode;
}TestStruct;

TestStruct *DUMMY_TEST_DATASTRUCTURE;
Vector *vector;



void testInitialization(CuTest *cuTest) {
    vector = vectorInitialization(-1, free, strcmp);
    CuAssertIntEquals(cuTest, DUMMY_TEST_DATASTRUCTURE->errorCode, INVALID_ARG);

    vector = vectorInitialization(-1, NULL, strcmp);
    CuAssertIntEquals(cuTest, DUMMY_TEST_DATASTRUCTURE, INVALID_ARG);

    vector = vectorInitialization(-1, free, strcmp);
    CuAssertIntEquals(cuTest, DUMMY_TEST_DATASTRUCTURE, INVALID_ARG);

}
void testAddition(CuTest *cuTest) {


}

int main(void ){

    DUMMY_TEST_DATASTRUCTURE =  (TestStruct*) malloc(sizeof(TestStruct));
    return 0;
}



