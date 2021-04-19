#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include<sys/types.h>
#include "my_header.h"



node * pop(stack * sp){
    node * ret;
    if(0 == sp->len){
        ret = NULL;
        printf("NULL is being returned\n");
    }
    else{
        ret = sp->top;
        sp->top = sp->top->next;
        sp->len--;
    }
    return ret;
}

node * peek(stack * sp){
    node * ret;
    if(0 == sp->len){
        ret = NULL;
    }
    else{
        ret = sp->top;
    }
    return ret;
}

int push(stack * sp, type t, int value){
    node * temp = (node *)malloc(sizeof(node));
    temp->t = t;
    temp->val = value;
    temp->next = sp->top;
    sp->top = temp;
    sp->len++;
    return 1; 
}

void print_stack(const stack * sp){
    node * run = sp->top;
    for(int i=0;i<sp->len;i++){
        if(run->t==0)
            printf("[TOP %dth] -> %d\n",i+1,run->val);
        else
            printf("[TOP %dth] -> %c\n",i+1,run->val);
        run=run->next;
    }
}


void clean_stdin(void)
{
    int c;
    do {
        c = getchar();
    } while (c != '\n' && c != EOF);
}

int operate(int a, int b, char op){
    int ret;
    switch(op){
        case '+' :  ret = a+b;
                    break;
        case '-'  : ret = a-b;
                    break;
        case '*'  : ret = a*b;
                    break;
        case '/'  : ret = a/b;
                    break;
        default: ret = -69;
            }
    return ret;
}