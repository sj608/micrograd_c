#ifndef GRAD_H
#define GRAD_H

#include <stdlib.h>
#include <stdio.h>
#include <math.h>

#define NULL_PTR_ERR 1

/*
Data structure for Gradient decsent.
-> value
-> gradient
-> previous value

Formulat ->:
    (val_a * val_b) + (val_c * val_d)  = val_g
    val_e = (val_a * val_b)
    val_f = (val_c * val_d)
    val_g = val_e + val_f
                                                    val_g
                                            val_e           val_f
                                        val_a   val_b   val_c   val_d
*/

typedef struct Value{
    float value;
    float grad;
    char op;
    char label;
    struct Value **prev;
    int prev_count;
    void (*backward)(struct Value *);
} Value;


Value* tanh_value(Value *a, Value *b, char label);
Value* exp_value(Value *a, Value *b, char label);
Value* relu_value(Value *a, char label);
Value* pow_value(Value *a, double *b, char label);
void mul_value_backward(Value *_v);
Value* mul_value(Value *a, Value *b, char label);
void add_value_backward(Value *_v);
Value* add_value(Value *a, Value *b, char label);
Value* new_value(float _value, Value **childern, int children_len, char _op, char _label);
void free_value(Value *_v);


#ifdef TEST
void print_node(Value* head);
#endif

#endif // GRAD_H
