#include <stdio.h>
#include <stdlib.h>

#ifndef DEBUG
#define DEBUG(...) printf(__VA_ARGS__)
#endif

#define SIZE 8

typedef struct {
    int head;
    int tail;
    int *array;
} Queue;

int enqueue(Queue *queue, int val) {
    if((queue->tail+1)%SIZE == queue->head)
        return -1;
    queue->array[queue->tail] = val;
    (queue->tail) = (queue->tail+1)%SIZE;
    return 0;
}

int dequeue(Queue *queue) {
    if(queue->tail == queue->head)
        return -1;
    (queue->head) = (queue->head + 1) % SIZE;
    return 0;
}

int print(Queue *queue) {
    int i;

    if (queue->tail==queue->head) return -1;

    for (i=queue->head; i!=queue->tail; i=(i+1)%SIZE) {
        printf("%d ", queue->array[i]);
    }
    printf("\n");
    return 0;
}


int main() {
    int val, ret_val, menu_choice;
    char c;
    Queue *queue;

    queue = (Queue *)malloc(sizeof(Queue));
    queue->head = 0;
    queue->tail = 0;
    queue->array = (int *)malloc(sizeof(int)*SIZE);

    setbuf(stdout, NULL);
    do {
        menu_choice = 0;
        DEBUG("\n1 enqueue\n2 dequeue\n3 ispis (print)\n4 izlaz\n");
        scanf("%d", &menu_choice);
        switch (menu_choice) {
            case 1:
                scanf("%d", &val);
                ret_val = enqueue(queue, val);
                if(ret_val==-1) printf("Red je pun.\n");
                break;
            case 2:
                ret_val = dequeue(queue);
                if(ret_val==-1) printf("Red je prazan.\n");
                break;
            case 3:
                ret_val = print(queue);
                if(ret_val==-1) printf("Red je prazan.\n");
                break;
            case 4:
                break;
            default:
                while((c = getchar()) != '\n' && c != EOF);
        }
    } while(menu_choice!=4);

    free(queue->array);
    free(queue);
    return 0;
}
