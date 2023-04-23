#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_SIZE 100

char stack[MAX_SIZE];
int top = -1;

void push(char item) {
    if (top >= MAX_SIZE - 1) {
        printf("\nStack Overflow.");
        exit(1);
    }
    stack[++top] = item;
}

char pop() {
    if (top == -1) {
        printf("\nStack Underflow.");
        exit(1);
    }
    return stack[top--];
}

int is_operator(char symbol) {
    if (symbol == '+' || symbol == '-' || symbol == '*' || symbol == '/') {
        return 1;
    } else {
        return 0;
    }
}

int priority(char symbol) {
    if (symbol == '*' || symbol == '/') {
        return 2;
    } else if (symbol == '+' || symbol == '-') {
        return 1;
    } else {
        return 0;
    }
}

void infix_to_postfix(char infix[], char postfix[]) {
    int i, j;
    char item;
    char x;

    push('(');
    strcat(infix, ")");
    i = 0;
    j = 0;
    item = infix[i];

    while (item != '\0') {
        if (item == '(') {
            push(item);
        } else if (isdigit(item) || isalpha(item)) {
            postfix[j] = item;
            j++;
        } else if (is_operator(item) == 1) {
            x = pop();
            while (is_operator(x) == 1 && priority(x) >= priority(item)) {
                postfix[j] = x;
                j++;
                x = pop();
            }
            push(x);
            push(item);
        } else if (item == ')') {
            x = pop();
            while (x != '(') {
                postfix[j] = x;
                j++;
                x = pop();
            }
        } else {
            printf("\nInvalid infix expression.");
            exit(1);
        }
        i++;
        item = infix[i];
    }
    if (top > 0) {
        printf("\nInvalid infix expression.");
        exit(1);
    }
    postfix[j] = '\0';
}

void generate_three_address_code(char postfix[]) {
    int i, j = 0, k = 1, op1, op2, res;
    char ch, op;
    char t[3];

    for (i = 0; postfix[i] != '\0'; i++) {
        ch = postfix[i];

        if (ch == '+' || ch == '-' || ch == '*' || ch == '/') {
            op2 = pop() - '0';
            op1 = pop() - '0';

            sprintf(t, "t%d", k++);
            printf("%c %d %d %s\n", op, op1, op2, t);
            push(t[1]);
        } else {
            push(ch);
        }
    }

    res = pop() - '0';
    printf("= %d", res);
}

int main() {
    char infix[MAX_SIZE], postfix[MAX_SIZE];

    printf("Enter infix expression: ");
    gets(infix);

    infix_to_postfix(infix, postfix);

    printf("Postfix expression: %s", postfix);

    generate_three_address_code(postfix);

    return 0;
}
