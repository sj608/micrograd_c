#include "grad.h"

Value* mul_value(Value *a, Value *b, char label)
{
    Value *res = new_value(a->value * b->value, (Value*[]){a, b}, 2, '*', label);
    return res;
}

Value* add_value(Value *a, Value *b, char label)
{
    Value *res = new_value(a->value + b->value, (Value*[]){a, b}, 2, '+', label);
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
    printf("|Value: %.2f | Grad: %.2f | Op: %c | Label: %c |", head->value, head->grad, head->op, head->label);
}


#endif