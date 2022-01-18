#include "simple_vector.h"

// Tests
#include "tests.h"

int main() {
	TestReserveConstructor();
	TestReserveMethod();

	Test1();
	Test2();

    TestTemporaryObjConstructor();
    TestTemporaryObjOperator();
    TestNamedMoveConstructor();
    TestNamedMoveOperator();
   // TestNoncopiableMoveConstructor();
   // TestNoncopiablePushBack();
   // TestNoncopiableInsert();
   // TestNoncopiableErase();
    return 0;

	return 0;
}
