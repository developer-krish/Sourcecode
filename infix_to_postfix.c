#include <stdio.h>
#include <stdlib.h>
#include <string.h>
struct stack
{
    int Top;
    int size;
    char *arr;
};
int isEmpty(struct stack *ptr)
{
    if (ptr->Top == -1)
    {
        return 1;
    }
    else
    {
        return 0;
    }
}
int isFull(struct stack *ptr)
{
    if (ptr->Top == ptr->size - 1)
    {
        return 1;
    }
    else
    {
        return 0;
    }
}
void push(struct stack *ptr, char x)
{
    if (isFull(ptr))
    {
        printf("Stack is full\n");
    }
    else
    {
        ptr->Top++;
        ptr->arr[ptr->Top] = x;
    }
}
char pop(struct stack *ptr)
{
    if (isEmpty(ptr))
    {
        printf("Stack is empty\n");
        return '\0';
    }
    else
    {
        char x = ptr->arr[ptr->Top];
        ptr->Top--;
        return x;
    }
}
char stack_top(struct stack *ptr)
{
    if (!isEmpty(ptr))
    {
        return ptr->arr[ptr->Top];
    }
    return '\0';
}

int isOperator(char ch)
{
    if ((ch == '+' || ch == '-' || ch == '*' || ch == '/' || ch == '^'))
    {
        return 1;
    }
    else
    {
        return 0;
    }
}
int precedence(char ch)
{
    if (ch == '+' || ch == '-')
    {
        return 1;
    }
    else if (ch == '/' || ch == '*')
    {
        return 2;
    }
    else if (ch == '^')
    {
        return 3;
    }
    return 0;
}
char *infix_to_postfix(char *infix)
{
    struct stack *sp = (struct stack *)malloc(sizeof(struct stack));
    sp->size = 25;
    sp->Top = -1;
    sp->arr = (char *)malloc(sp->size * sizeof(char));

    char *postfix = (char *)malloc((strlen(infix) + 1) * sizeof(char));

    int i = 0; // Track infix expression
    int j = 0; // Track postfix addition

    while (infix[i] != '\0')
    {
        if (infix[i] >= 'a' && infix[i] <= 'z') // If the character is an operand
        {
            postfix[j] = infix[i];
            j++;
        }
        else if (infix[i] == '(') // Push '(' to the stack
        {
            push(sp, infix[i]);
        }
        else if (infix[i] == ')') // Pop and add to postfix until '(' is found
        {
            while (!isEmpty(sp) && stack_top(sp) != '(')
            {
                postfix[j] = pop(sp);
                j++;
            }
            pop(sp); // Pop the '(' from the stack
        }
        else if (isOperator(infix[i])) // If the character is an operator
        {
            while (!isEmpty(sp) && precedence(infix[i]) <= precedence(stack_top(sp)))
            {
                postfix[j] = pop(sp);
                j++;
            }
            push(sp, infix[i]);
        }
        i++;
    }

    while (!isEmpty(sp))
    {
        postfix[j] = pop(sp);
        j++;
    }
    postfix[j] = '\0';
    free(sp->arr);
    free(sp);
    return postfix;
}

int main()
{
    char *infix = "(a*b)-(c+d)/e^f";
    char *postfix = infix_to_postfix(infix);
    printf("Postfix is %s ", postfix);
    free(postfix);
}
