#include "../../third_party/unity/src/unity.h"
#include "../slist.h"

void setUp(void)
{
    /* Called before each test. */
}

void tearDown(void)
{
    /* Called after each test. */
}

/*!
 * @brief Test case 1: create list.
 */
void test_slist_create_should_return_not_null(void)
{
    slist_t *p_list = slist_create();
    TEST_ASSERT_NOT_NULL(p_list);
    slist_destroy(p_list);
}