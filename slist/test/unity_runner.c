#include "../../third_party/unity/src/unity.h"

/* Test functions (extern) ---------------------------------------------------*/

extern void test_slist_create_should_return_not_null(void);

/* Main ----------------------------------------------------------------------*/

int main(void)
{
    UNITY_BEGIN();

    RUN_TEST(test_slist_create_should_return_not_null);

    return UNITY_END();
}