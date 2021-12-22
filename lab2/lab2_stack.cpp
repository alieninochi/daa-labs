// П.І.Б: Голубкова Зоя Сергіївна
// Група: ТР-з01
// Предмет: Проетування та аналіз алгоритмів
// Лабораторна робота №2

#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <time.h>
#define INIT_STACK_SIZE 0
#define MAX_STACK_SIZE 20
#define STACK_UNDERFLOW -100
#define STACK_OVERFLOW -101

typedef struct 
{
    int data[MAX_STACK_SIZE];
    size_t size;
} stack_t;

void push(stack_t *stack, int value)
{
    if (stack->size >= MAX_STACK_SIZE)
    {
        exit(STACK_OVERFLOW);
    }

    stack->data[stack->size] = value;
    stack->size++;
}

int pop(stack_t* stack)
{
    if (stack->size == 0)
    {
        exit(STACK_UNDERFLOW);
    }
    
    stack->size--;
    return stack->data[stack->size];
}

// return element from top
int peek(stack_t* stack)
{
    if (stack->size <= 0)
    {
        exit(STACK_UNDERFLOW);
    }

    return stack->data[stack->size - 1];
}

stack_t createRandomStack()
{
    stack_t stack;
    stack.size = INIT_STACK_SIZE;

    for (int i = 0; i < MAX_STACK_SIZE; i++)
    {
        push(&stack, rand() % 100);
    }

    return stack;
}

void printStack(stack_t* stack) {
    int length = stack->size;

    for (int i = 0; i < length; i++)
    {
        printf("%d ", stack->data[i]);
    }
    printf("\n");
}

int main()
{
    srand(time(NULL));

    stack_t numbersStack = createRandomStack();
    
    printf("Created stack: \n");
    printStack(&numbersStack);

    int minElement = peek(&numbersStack), maxElement = peek(&numbersStack);
    int minIndex = numbersStack.size, maxIndex = numbersStack.size;

    stack_t stackReversedCopy;
    stackReversedCopy.size = INIT_STACK_SIZE;

    while (numbersStack.size != 0)
    {
        int tmpElement = peek(&numbersStack), tmpIndex = numbersStack.size;
        if (minElement > tmpElement)
        {
            minElement = tmpElement;
            minIndex = numbersStack.size;
        }

        if (maxElement < tmpElement)
        {
            maxElement = tmpElement;
            maxIndex = numbersStack.size;
        }

        pop(&numbersStack);
        push(&stackReversedCopy, tmpElement);
    }

    numbersStack = stackReversedCopy;

    printf("Min element: %d, its index: %d\n", minElement, minIndex);
    printf("Max element: %d, its index: %d\n", maxElement, maxIndex);
}