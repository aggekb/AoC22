#include "../test/D10P1.h"
#include "../unity/src/unity.h"

void setUp(void) {
}

void tearDown(void) {
}

void test_loadinput(void) {
    char testInstructions[MAX_INSTRUCTIONS][LINE_WIDTH];
    loadinput(testInstructions);
    /* Add assertions to verify the loaded instructions */
    TEST_ASSERT_EQUAL_STRING("noop", testInstructions[0]);
    TEST_ASSERT_EQUAL_STRING("addx 7", testInstructions[1]);
}

void test_main_execution(void) {
    int result = getsignalsum();
    /* Assertions to verify the result */
    TEST_ASSERT_EQUAL_INT(14860, result);
}

int main(void) {
    UNITY_BEGIN();
    /* Run tests */
    RUN_TEST(test_loadinput);
    RUN_TEST(test_main_execution);
    return UNITY_END();
}
