#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#ifndef DEBUG
#define DEBUG(...) printf(__VA_ARGS__)
#endif

#define SIZE 8

typedef struct {
    int top;
    int *array;
} Stack;

int push(Stack *stack, int val) {
    if(stack->top == SIZE-1)
        return -1;
    stack->array[stack->top+1] = val;
    (stack->top)++;
    return 0;
}

int pop(Stack *stack) {
    if(stack->top == -1)
        return -1;
    (stack->top)--;
    return 0;
}

int print(Stack *stack) {
    int i;

    if(stack->top==-1) return -1;

    for(i=0; i<=stack->top; i++) {
        printf("%d ", stack->array[i]);
    }
    printf("\n");
    return 0;
}

int main() {
    int val, ret_val, menu_choice;
    Stack *stack;
    char c;

    setbuf(stdout, NULL);
    stack = (Stack *)malloc(sizeof(Stack));
    stack->top = -1;
    stack->array = (int *)malloc(sizeof(int)*SIZE);
    do {
        menu_choice = 0;
        DEBUG("\n1 push\n2 pop\n3 ispis\n4 izlaz\n");
        scanf("%d", &menu_choice);
        switch (menu_choice) {
            case 1:
                scanf("%d", &val);
                ret_val = push(stack, val);
                if(ret_val==-1) printf("Stog je pun.\n");
                break;
            case 2:
                ret_val = pop(stack);
                if(ret_val==-1) printf("Stog je prazan.\n");
                break;
            case 3:
                ret_val = print(stack);
                if(ret_val==-1) printf("Stog je prazan.\n");
                break;
            case 4:
                break;
            default:
                while((c = getchar()) != '\n' && c != EOF);
        }
    } while(menu_choice!=4);

    free(stack->array);
    free(stack);
    return 0;
}
