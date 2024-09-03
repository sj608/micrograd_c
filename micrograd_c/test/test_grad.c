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
    // print_node(value_a);
    // print_node(value_b);
    // print_node(value_c);
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
    // print_node(value_c);
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
    // print_node(value_c);
}

void test_case_1(void)
{
    // (A+B) = E
    // (C+D) = F
    // E*F = G
    Value *val_a, *val_b, *val_c, *val_d, *val_e, *val_f, *val_g;
    val_a = new_value(2.0, NULL, 0, '\0', 'A');
    val_b = new_value(3.0, NULL, 0, '\0', 'B');
    val_c = new_value(2.0, NULL, 0, '\0', 'C');
    val_d = new_value(3.0, NULL, 0, '\0', 'D');
    val_e = add_value(val_a, val_b, 'E');
    val_f = add_value(val_c, val_d, 'F');
    val_g = mul_value(val_e, val_f, 'G');
    print_node(val_g);
    printf("\n\n");
    print_node(val_f);
    print_node(val_e);
    printf("\n\n");

    val_g->grad = 1.0;
    val_g->backward(val_g);
    val_e->backward(val_e);
    val_f->backward(val_f);
    print_node(val_g);
    printf("\n\n");
    print_node(val_f);
    print_node(val_e);
}

#endif // TEST
