#ifndef STACK_H_
#define STACK_H_

#include "tree.h"

typedef struct StackElement {
    Node* value;
    struct StackElement *prev;
} StackElement;

typedef struct Stack {
    StackElement *top;
} Stack;

StackElement* create_stack_element(Node* node);
Stack* create_stack();
bool is_empty(Stack *stack);
void stack_push(Stack *stack, Node* node);
StackElement* stack_pop(Stack *stack);
void stack_print(Stack* stack);

#endif // STACK_H_
