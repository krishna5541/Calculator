#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include<sys/types.h>
#include "my_header.h"
#define MAX 500

char map[TOTAL_OPERATOR] = {'+','-','*','/','(',')'};                       //Mapping of operator with whole number
reletion prec_table[TOTAL_OPERATOR][TOTAL_OPERATOR]={
    {Takes,Takes,Yields,Yields,Yields,Takes},
    {Yields,Takes,Yields,Yields,Yields,Takes},
    {Takes,Takes,Takes,Yields,Yields,Takes},
    {Takes,Takes,Takes,Takes,Yields,Takes},
    {Yields,Yields,Yields,Yields,Yields,Equals},
    {Takes,Takes,Takes,Takes,Error,Takes}
                                                    };


    int find_index(const char ch){
        int ret = -1;
        for(int i=0;i<TOTAL_OPERATOR;i++)
            if(map[i] == ch)
                ret = i;
        return ret;
    }


int main(){
    char  exp[MAX];
    stack my_st = {0,NULL};
    int last_op, flag = 0, temp = 0, brack=0;
    printf("Enter an Arithmetical expression(Without Whitespace): ");
    scanf("%[^\n]",exp);
    printf("You typed: %s\n",exp);

    for(int i=0;i<strlen(exp);i++){
        if(i < (strlen(exp)-1) && exp[i] >= '0' && exp[i] <= '9'){
                temp = temp*10 + (exp[i] - 48);
            }
        else if(flag && (exp[i] == '+' || exp[i] == '-' || exp[i] == '*' ||exp[i] == '/')){
            push(&my_st, Number, temp);
            temp = 0;
            int curr = find_index(exp[i]);

            while(prec_table[last_op][curr] == Takes){
                print_stack(&my_st);
                printf("\n\n");
                int b = pop(&my_st)->val;
                char op = pop(&my_st)->val;
                int a = pop(&my_st)->val;
                int acc = operate(a,b,op);
                node * n_temp = peek(&my_st);
                if(n_temp==NULL){
                    push(&my_st,Number,acc);
                    break;
                }

                else{
                    last_op = find_index(n_temp->val);
                    push(&my_st,Number,acc);
                }
            }
            push(&my_st,Oper,exp[i]);
            last_op = find_index(exp[i]);

        }

        else if((i==(strlen(exp)-1))&& exp[i]!=')'){
            int acc;
            temp=temp*10+(exp[i]-48);
            push(&my_st,Number,temp);
            printf("Inside strlen-1\n");
            while(my_st.len > 1){
                print_stack(&my_st);
                printf("\n\n");
                int b = pop(&my_st)->val;
                char op = pop(&my_st)->val;
                if(op!='+' && op!='-' && op!='*' && op!='/'){
                    printf("SYNTEX ERROR IN GIVEN EXPRESSION!!!\n");
                    exit(EXIT_FAILURE);
                }
                int a = pop(&my_st)->val;
                acc = operate(a,b,op);
                push(&my_st,Number,acc);

            }
                
        }
    else if(exp[i]=='('){
        push(&my_st,Oper,exp[i]);
        flag=1;
        last_op = find_index(exp[i]);
        brack++;
    }

    else if(exp[i]==')'){
        if(brack == 0){
            printf("BRACKET UNBALANCED ERROR\n");
            exit(EXIT_FAILURE);
        }
        brack--;
        push(&my_st,Number,temp);
        temp=0;
        int acc, t_flag=1;

        while(t_flag){
            int b = pop(&my_st)->val;
            char op = pop(&my_st)->val;
            if(op=='('){
                t_flag=0;
                temp = b;
                node * check = peek(&my_st);
                if(check==NULL)
                    flag=0;
                else
                    last_op = find_index(check->val);
                continue;
            }
            int a = pop(&my_st)->val;
            acc = operate(a,b,op);
            push(&my_st,Number,acc);

        }
        if(strlen(exp)-1 == i){
            push(&my_st,Number,temp);

        }
    }

    
    else if (flag == 0){
        push(&my_st,Number,temp);
        temp=0;
        flag=1;
        last_op = find_index(exp[i]);
        push(&my_st,Oper,exp[i]);
    }
    else{
        printf("UNKNOWN ERROR!!!\t exp[i] = %c\n",exp[i]);
        print_stack(&my_st);
        break;

    }

    }
    printf(">>>>  Final Result is: %d\n\n",peek(&my_st)->val);
    
    return 0;


}
