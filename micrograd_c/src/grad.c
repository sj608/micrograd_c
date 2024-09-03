#include "grad.h"

Value* tanh_value(Value *a, char label)
{
    Value *res = value_new(tanh(a->value);, (Value *[]){a}, 1, "tanh");
    return res;
}

Value* exp_value(Value *a, Value *b, char label)
{
    Value *res = new_value(exp(a->value),(Value *[]){a}, 1, 'e', label);
    return res;
}

Value* relu_value(Value *a, char label)
{
    Value *res = new_value( a->value > 0 ? a->value : 0, (Value *[]){a}, 1, 'r', label);
    return res;
}

Value* pow_value(Value *a, double b, char label)
{
    Value *b_val = new_value(b, NULL,0, "p",  label);
    Value *res = new_value(pow(a->value, b), (Value*[]){a, b_val}, 2, 'p', label);
    return res;
}

void mul_value_backward(Value *_v)
{
    _v->prev[0]->grad += _v->grad * _v->prev[1]->value;
    _v->prev[1]->grad += _v->grad * _v->prev[0]->value;
}

Value* mul_value(Value *a, Value *b, char label)
{
    Value *res = new_value(a->value * b->value, (Value*[]){a, b}, 2, '*', label);
    res->backward = mul_value_backward;
    return res;
}

void add_value_backward(Value *_v)
{
    _v->prev[0]->grad += _v->grad;
    _v->prev[1]->grad += _v->grad;
}

Value* add_value(Value *a, Value *b, char label)
{
    Value *res = new_value(a->value + b->value, (Value*[]){a, b}, 2, '+', label);
    res->backward = add_value_backward;
    return res;
}

Value* new_value(float _value, Value **children, int children_len, char _op, char _label)
{
    Value* value_struct = (Value*)malloc(sizeof(Value));
    if(value_struct == NULL){
        return NULL;
    }
    value_struct->value = _value;
    value_struct->grad = 0.0;
    if(children_len){
        value_struct->prev = (Value**)malloc(sizeof(Value*)*children_len);
        for(int i = 0; i < children_len; i++){
            value_struct->prev[i] = children[i];
        }
    }else{
        value_struct->prev = NULL;
    }
    value_struct->prev_count = children_len;
    value_struct->op = _op;
    value_struct->label = _label;
    value_struct->backward = NULL;
    return value_struct;
}

void free_value(Value *_v)
{
    if(!_v) return;
    if(_v->prev_count){
        free(_v->prev);
    }
    free(_v);
}

#ifdef TEST

void print_node(Value* head)
{
    printf("|Value: %.2f | Grad: %.2f | Op: %c | Label: %c |\n", head->value, head->grad, head->op, head->label);
    for(int i = 0; i<head->prev_count; i++){
        printf("|Value: %.2f | Grad: %.2f | Op: %c | Label: %c |\n", head->prev[i]->value, head->prev[i]->grad, head->prev[i]->op, head->prev[i]->label);
    }
}


#endif