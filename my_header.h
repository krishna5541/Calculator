#ifndef GUARD_BIT

#define GUARD_BIT 1

#include <stdio.h>
#include <stdlib.h>

#define TOTAL_OPERATOR 6
typedef enum reletion reletion;
typedef enum type type;
typedef struct node node;
typedef struct stack stack;


enum reletion{Yields,Takes,Equals,Error};
enum type{Number,Oper};

extern char map[TOTAL_OPERATOR];
extern reletion prec_table[TOTAL_OPERATOR][TOTAL_OPERATOR];

struct node{
    type t;
    int val;
    node * next;
};

struct stack{
    int len;
    node * top;

};

node * pop(stack * sp);

node * peek(stack * sp);

int push(stack * sp, type t, int value);

void print_stack(const stack * sp);

void clean_stdin(void);

int operate(int a, int b, char op);










#endif