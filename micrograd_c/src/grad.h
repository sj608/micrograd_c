#ifndef GRAD_H
#define GRAD_H

#include <stdlib.h>
#include <stdio.h>

#define NULL_PTR_ERR 1

typedef struct Value{
    float value;
    float grad;
    char op;
    char label;
    struct Value **prev;
    int prev_count;
    void (*backward)(struct Value *);
} Value;



Value* mul_value(Value *a, Value *b, char label);
Value* add_value(Value *a, Value *b, char label);
Value* new_value(float _value, Value **childern, int children_len, char _op, char _label);
void free_value(Value *_v);


#ifdef TEST
void print_node(Value* head);
#endif

#endif // GRAD_H
