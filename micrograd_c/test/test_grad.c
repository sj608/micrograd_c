#ifdef TEST

#include "unity.h"

#include "grad.h"

void setUp(void)
{
}

void tearDown(void)
{
}

void test_new_value(void)
{
    Value *value_a, *value_b, *value_c;
    value_a = new_value(0.24, NULL, 0, '\0', 'A');
    value_b = new_value(1.24, NULL, 0, '\0', 'B');
    value_c = new_value(2.24, NULL, 0, '\0', 'C');
    TEST_ASSERT_EQUAL(NULL, value_a->backward);
    TEST_ASSERT_EQUAL(NULL, value_a->prev);
    TEST_ASSERT_EQUAL(NULL, value_b->backward);
    TEST_ASSERT_EQUAL(NULL, value_b->prev);
    TEST_ASSERT_EQUAL(NULL, value_c->backward);
    TEST_ASSERT_EQUAL(NULL, value_c->prev);
    print_node(value_a);
    printf("\n");
    print_node(value_b);
    printf("\n");
    print_node(value_c);
    printf("\n");
}

void test_add_value(void)
{
    Value *value_a, *value_b, *value_c;
    value_a = new_value(0.24, NULL, 0, '\0', 'A');
    value_b = new_value(1.24, NULL, 0, '\0', 'B');
    value_c = add_value(value_a, value_b, 'C');
    TEST_ASSERT_EQUAL('A', value_c->prev[0]->label);
    TEST_ASSERT_EQUAL('B', value_c->prev[1]->label);
    TEST_ASSERT_EQUAL(0.24, value_c->prev[0]->value);
    TEST_ASSERT_EQUAL(1.24, value_c->prev[1]->value);
    TEST_ASSERT_EQUAL(1.48, value_c->value);
    print_node(value_c);
    printf("\n");
}

void test_mul_value(void)
{
    Value *value_a, *value_b, *value_c;
    value_a = new_value(2.0, NULL, 0, '\0', 'A');
    value_b = new_value(3.0, NULL, 0, '\0', 'B');
    value_c = mul_value(value_a, value_b, 'C');
    TEST_ASSERT_EQUAL('A', value_c->prev[0]->label);
    TEST_ASSERT_EQUAL('B', value_c->prev[1]->label);
    TEST_ASSERT_EQUAL(2.0, value_c->prev[0]->value);
    TEST_ASSERT_EQUAL(3.0, value_c->prev[1]->value);
    TEST_ASSERT_EQUAL(6.0, value_c->value);
    print_node(value_c);
    printf("\n");
}

#endif // TEST
